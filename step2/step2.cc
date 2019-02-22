#define step2_cxx
#include "step2.h"
//#include "GeneralFunctions.h"
#include <TH2.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <fstream>
#include <iostream>	// std::cout
#include <algorithm>	// std::sort
#include <TRandom.h>
#include <TRandom3.h>
#include <sstream>
#include <string>
#include <vector>
#include "TMath.h"
#include <cmath>

#include "Davismt2.h"

using namespace std;

const double MTOP  = 173.5;
const double MW    = 80.4; 

float mt2( const TLorentzVector visa,  const TLorentzVector visb,  const TLorentzVector metVec,  const double mn)
{

    Davismt2 davismt2;

    // Format: M, px, py
    double visaVector[3] = { visa.M() , visa.Px(), visa.Py() };
    double visbVector[3] = { visb.M(), visb.Px(), visb.Py() };
    double metVector[3] = { mn, metVec.Px(), metVec.Py() };

    davismt2.set_momenta(visaVector,visbVector,metVector);
    davismt2.set_mn(mn);

    return davismt2.get_mt2();

}



void step2::Loop()
{
   if (inputTree == 0) return;
   inputTree->SetBranchStatus("*",1);
   outputFile->cd();
   TTree *outputTree = inputTree->CloneTree(0); //Copy of Input Tree
   outputTree->Branch("isTraining",&isTraining,"isTraining/I");
   outputTree->Branch("deltaR_minBB",&deltaR_minBB,"deltaR_minBB/F");
   outputTree->Branch("aveBBdr",&aveBBdr,"aveBBdr/F");
   outputTree->Branch("deltaEta_maxBB",&deltaEta_maxBB,"deltaEta_maxBB/F");  
   outputTree->Branch("FW_momentum_2",&FW_momentum_2,"FW_momentum_2/F");
   outputTree->Branch("centrality",&centrality,"centrality/F");
   outputTree->Branch("aveCSVpt",&aveCSVpt,"aveCSVpt/F");
   outputTree->Branch("mass_maxJJJpt",&mass_maxJJJpt,"mass_maxJJJpt/F");
   outputTree->Branch("lepDR_minBBdr",&lepDR_minBBdr,"lepDR_minBBdr/F");  
      
   Long64_t nentries = inputTree->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TLorentzVector bjet1, bjet2, jet1, jet2, jet3, lep;   
   
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = inputTree->GetEntry(jentry);   nbytes += nb;
     if (Cut(ientry) != 1) continue;
     if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;      
      
     TRandom3 myseed;
     myseed.SetSeed(static_cast<int>(leptonPhi_singleLepCalc*1e5));
     double coin = myseed.Rndm();
     if(coin<1./3.) isTraining = 1;                          // BDT TRAINING
     else if((coin>=1./3.) && (coin<2./3.))isTraining =2;    // BDT TESTING
     else if((coin>=2./3.) && (coin<1))isTraining =3;        // BDT APPLICATION
     minBBdr = 1e9;     
     aveCSVpt = -1;      
     deltaR_minBB = 1e9;
     aveBBdr = -1;      
     deltaEta_maxBB = 1e9;                  
     lepDR_minBBdr = -1;
     mass_maxJJJpt = -1;      
     FW_momentum_2=0;      
     centrality = -1;      

     int njetscsv = 0;      
     double maxBBdeta = 0;
     double totalJetPt = 0; //this is mainly HT
     double totalJetE  = 0; 
     double npairs = 0;     
     double maxJJJpt = 0;
//////////////////////////////////////////
// build BB PAIR variables and aveCSVpt //
//////////////////////////////////////////
     for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		if(njetscsv<=10 && theJetCSVb_JetSubCalc_PtOrdered->at(ijet)>=0 && theJetCSVbb_JetSubCalc_PtOrdered->at(ijet)>=0){
		   njetscsv+=1;
		   aveCSVpt += (theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet))*theJetPt_JetSubCalc_PtOrdered->at(ijet);
		}
		totalJetPt+=theJetPt_JetSubCalc_PtOrdered->at(ijet);
		totalJetE+=theJetEnergy_JetSubCalc_PtOrdered->at(ijet);		
		if(!(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs
		bjet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));	

		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  if(!(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs	  
		  bjet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));		  
		  npairs += 1.0;
		  double pairdr = (bjet1).DeltaR(bjet2);
		  double pairdeta = bjet1.Eta() - bjet2.Eta();
		  aveBBdr += (bjet1).DeltaR(bjet2);
		  if(pairdr < minBBdr){
			minBBdr = pairdr;
			lepDR_minBBdr = (bjet1+bjet2).DeltaR(lep);
			deltaR_minBB = pairdr;
		  }
		  if(fabs(pairdeta) > maxBBdeta){
			maxBBdeta = fabs(pairdeta);
			deltaEta_maxBB = pairdeta;
		  }
		}
	  }

//////////////////////////////////////////
// build centrality //
//////////////////////////////////////////
      if(totalJetE!=0) {centrality = totalJetPt/totalJetE;}	  
	  
/////////////////////////
// build JJJ variables //
/////////////////////////
	  for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		jet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));
		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  jet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));
		  for(unsigned int kjet = jjet + 1; kjet < theJetPt_JetSubCalc_PtOrdered->size(); kjet++){
			if(kjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;	  
			jet3.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(kjet),theJetEta_JetSubCalc_PtOrdered->at(kjet),theJetPhi_JetSubCalc_PtOrdered->at(kjet),theJetEnergy_JetSubCalc_PtOrdered->at(kjet));
			double trippt = (jet1+jet2+jet3).Pt();
			if(trippt > maxJJJpt){
			  maxJJJpt = trippt;
			  mass_maxJJJpt = (jet1+jet2+jet3).M();
			}
		  }
		}
	  }	  
	  
/////////////////////////
// Fox-Wolfram moments //
/////////////////////////      
      TLorentzVector jetI, jetJ;
      double HT_alljets = 0;
      for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		jetI.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));
		HT_alljets += jetI.Et();
	  }
	  for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		jetI.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));
		for(unsigned int jjet = 0; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  jetJ.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));
		  double ET_ij_over_ETSum2 = jetI.Et()*jetJ.Et()/pow(HT_alljets,2);
		  double cosTheta_ij = (jetI.Px()*jetJ.Px() + jetI.Py()*jetJ.Py() + jetI.Pz()*jetJ.Pz())/(jetI.Rho()*jetJ.Rho());
		  FW_momentum_2 += ET_ij_over_ETSum2 * 0.5   * (  3*std::pow(cosTheta_ij,2)- 1);
		}
	  }
   outputTree->Fill();      
   }
outputTree->Write();   
}
