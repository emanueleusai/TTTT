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
   outputFile->cd();
   TTree *outputTree = inputTree->CloneTree(); //Copy of Input Tree
//    TTree *outputTree = new TTree("ljmet","ljmet"); //No Copy of Input Tree   
   TBranch *b_isTraining            = outputTree->Branch("isTraining",&isTraining,"isTraining/I");
   TBranch *b_deltaR_minBB          = outputTree->Branch("deltaR_minBB",&deltaR_minBB,"deltaR_minBB/F");
   TBranch *b_aveBBdr               = outputTree->Branch("aveBBdr",&aveBBdr,"aveBBdr/F");
   TBranch *b_deltaEta_maxBB        = outputTree->Branch("deltaEta_maxBB",&deltaEta_maxBB,"deltaEta_maxBB/F");  
   TBranch *b_FW_momentum_2         = outputTree->Branch("FW_momentum_2",&FW_momentum_2,"FW_momentum_2/F");
   TBranch *b_centrality            = outputTree->Branch("centrality",&centrality,"centrality/F");
   TBranch *b_aveCSVpt              = outputTree->Branch("aveCSVpt",&aveCSVpt,"aveCSVpt/F");
   TBranch *b_mass_maxJJJpt         = outputTree->Branch("mass_maxJJJpt",&mass_maxJJJpt,"mass_maxJJJpt/F");
   TBranch *b_lepDR_minBBdr         = outputTree->Branch("lepDR_minBBdr",&lepDR_minBBdr,"lepDR_minBBdr/F");  
   TBranch *b_HT_bjets              = outputTree->Branch("HT_bjets",&HT_bjets,"HT_bjets/F");     
   TBranch *b_HT_ratio              = outputTree->Branch("HT_ratio",&HT_ratio,"HT_ratio/F");        
   TBranch *b_HT_2m                 = outputTree->Branch("HT_2m",&HT_2m,"HT_2m/F");        
   TBranch *b_thirdcsvb_bb          = outputTree->Branch("thirdcsvb_bb",&thirdcsvb_bb,"thirdcsvb_bb");        
   TBranch *b_fourthcsvb_bb         = outputTree->Branch("fourthcsvb_bb",&fourthcsvb_bb,"fourthcsvb_bb/F");           

   TBranch *b_mass_lepJets0         = outputTree->Branch("mass_lepJets0",&mass_lepJets0,"mass_lepJets0/F");
   TBranch *b_mass_lepJets1         = outputTree->Branch("mass_lepJets1",&mass_lepJets1,"mass_lepJets1/F");
   TBranch *b_mass_lepJets2         = outputTree->Branch("mass_lepJets2",&mass_lepJets2,"mass_lepJets2/F");      
   TBranch *b_mass_minBBdr          = outputTree->Branch("mass_minBBdr",&mass_minBBdr,"mass_minBBdr/F");
   TBranch *b_mass_minLLdr          = outputTree->Branch("mass_minLLdr",&mass_minLLdr,"mass_minLLdr/F");
   TBranch *b_mass_maxBBpt          = outputTree->Branch("mass_maxBBpt",&mass_maxBBpt,"mass_maxBBpt/F");
   TBranch *b_mass_maxBBmass        = outputTree->Branch("mass_maxBBmass",&mass_maxBBmass,"mass_maxBBmass/F");
   TBranch *b_theJetLeadPt          = outputTree->Branch("theJetLeadPt",&theJetLeadPt,"theJetLeadPt/F");
   TBranch *b_deltaR_lepBJets0      = outputTree->Branch("deltaR_lepBJets0",&deltaR_lepBJets0,"deltaR_lepBJets0/F");
   TBranch *b_deltaR_lepBJets1      = outputTree->Branch("deltaR_lepBJets1",&deltaR_lepBJets1,"deltaR_lepBJets1/F");   
   TBranch *b_minDR_lepBJet         = outputTree->Branch("minDR_lepBJet",&minDR_lepBJet,"minDR_lepBJet/F");
   TBranch *b_minBBdr               = outputTree->Branch("minBBdr",&minBBdr,"minBBdr/F");
   TBranch *b_mass_lepBJet0         = outputTree->Branch("mass_lepBJet0",&mass_lepBJet0,"mass_lepBJet0/F");
   TBranch *b_mass_lepBB_minBBdr    = outputTree->Branch("mass_lepBB_minBBdr",&mass_lepBB_minBBdr,"mass_lepBB_minBBdr/F");
   TBranch *b_mass_lepJJ_minJJdr    = outputTree->Branch("mass_lepJJ_minJJdr",&mass_lepJJ_minJJdr,"mass_lepJJ_minJJdr/F");
   TBranch *b_mass_lepBJet_mindr    = outputTree->Branch("mass_lepBJet_mindr",&mass_lepBJet_mindr,"mass_lepBJet_mindr/F");
   TBranch *b_deltaR_lepBJet_maxpt  = outputTree->Branch("deltaR_lepBJet_maxpt",&deltaR_lepBJet_maxpt,"deltaR_lepBJet_maxpt/F");
   TBranch *b_deltaPhi_maxBB        = outputTree->Branch("deltaPhi_maxBB",&deltaPhi_maxBB,"deltaPhi_maxBB/F");
   TBranch *b_hemiout               = outputTree->Branch("hemiout",&hemiout,"hemiout/F");
   TBranch *b_corr_met              = outputTree->Branch("corr_met",&corr_met,"corr_met/F");
   TBranch *b_deltaPhi_lepMET       = outputTree->Branch("deltaPhi_lepMET",&deltaPhi_lepMET,"deltaPhi_lepMET/F");
   TBranch *b_min_deltaPhi_METjets  = outputTree->Branch("min_deltaPhi_METjets",&min_deltaPhi_METjets,"min_deltaPhi_METjets/F");
   TBranch *b_deltaPhi_METjets      = outputTree->Branch("deltaPhi_METjets",&deltaPhi_METjets);
   TBranch *b_aveCSV                = outputTree->Branch("aveCSV",&aveCSV,"aveCSV/F");
   TBranch *b_deltaPhi_j1j2         = outputTree->Branch("deltaPhi_j1j2",&deltaPhi_j1j2,"deltaPhi_j1j2/F");
   TBranch *b_alphaT                = outputTree->Branch("alphaT",&alphaT,"alphaT/F");
   TBranch *b_PtFifthJet            = outputTree->Branch("PtFifthJet",&PtFifthJet,"PtFifthJet/F");
   TBranch *b_FW_momentum_0         = outputTree->Branch("FW_momentum_0",&FW_momentum_0,"FW_momentum_0/F");
   TBranch *b_FW_momentum_1         = outputTree->Branch("FW_momentum_1",&FW_momentum_1,"FW_momentum_1/F");
   TBranch *b_FW_momentum_3         = outputTree->Branch("FW_momentum_3",&FW_momentum_3,"FW_momentum_3/F");
   TBranch *b_FW_momentum_4         = outputTree->Branch("FW_momentum_4",&FW_momentum_4,"FW_momentum_4/F");
   TBranch *b_FW_momentum_5         = outputTree->Branch("FW_momentum_5",&FW_momentum_5,"FW_momentum_5/F");
   TBranch *b_FW_momentum_6         = outputTree->Branch("FW_momentum_6",&FW_momentum_6,"FW_momentum_6/F");

   Long64_t nentries = inputTree->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TLorentzVector bjet1, bjet2, jet1, jet2, jet3, lep, met;   
   
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
     aveCSVpt = 0;      
     deltaR_minBB = 1e9;
     aveBBdr = -1;      
     deltaEta_maxBB = 1e9;                  
     lepDR_minBBdr = -1;
     mass_maxJJJpt = -1;      
     FW_momentum_0=0; FW_momentum_1=0; FW_momentum_2=0; FW_momentum_3=0; FW_momentum_4=0; FW_momentum_5=0; FW_momentum_6=0;
     centrality = -1;      
     HT_bjets = 0;
     HT_ratio = 0; //for ratio of HT(j1,2,3,4)/HT(other jets)     
     HT_2m = -1000;
     theJetLeadPt = -1000; 
     mass_lepJets0 = -1;             
     mass_lepJets1 = -1;                          
     mass_lepJets2 = -1;                                    
     int njetscsv = 0;      
     double maxBBdeta = 0;
     double totalJetPt = 0; //this is mainly HT
     double totalJetE  = 0; 

     double HT_4jets = 0; //for ratio of HT(j1,2,3,4)/HT(other jets)     
     double HT_other = 0; //for ratio of HT(j1,2,3,4)/HT(other jets)          
     double npairs = 0;     
     double maxJJJpt = 0;
     double BjetSecondPt = 0;

/////////////////////////////////////////////////////////////////
// build BB PAIR variables, aveCSVpt, HT_bjets, HT_ratio, HT_2m//
/////////////////////////////////////////////////////////////////

     HT_4jets = theJetPt_JetSubCalc_PtOrdered->at(0)+theJetPt_JetSubCalc_PtOrdered->at(1)+theJetPt_JetSubCalc_PtOrdered->at(2)+theJetPt_JetSubCalc_PtOrdered->at(3);
     for(unsigned int ijet = 4; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
         HT_other += theJetPt_JetSubCalc_PtOrdered->at(ijet);
     }
     if (NJets_JetSubCalc > 4){
         HT_ratio = HT_4jets/HT_other;
     }
//      std::cout<<"deltaR_lepJets->at(0) : "<<deltaR_lepJets->at(0)<<std::endl;
     corr_met = (float) corr_met_singleLepCalc;
     theJetLeadPt = theJetPt_JetSubCalc_PtOrdered->at(0);
     
     double maxBBdphi = 0;
     double maxBBpt = 0; 
     double maxLBpt = 0; 
     double maxBBmass = 0;
     double minLLdr = 1e9;

     bjet1.SetPtEtaPhiE(0,0,0,0);
     bjet2.SetPtEtaPhiE(0,0,0,0);
     jet1.SetPtEtaPhiE(0,0,0,0);
     jet2.SetPtEtaPhiE(0,0,0,0);
     jet3.SetPtEtaPhiE(0,0,0,0);

     double lepM;
     double metM=0;
     if(isMuon) lepM = 0.105658367;
     else lepM = 0.00051099891;
     lep.SetPtEtaPhiM(leptonPt_singleLepCalc,leptonEta_singleLepCalc,leptonPhi_singleLepCalc,lepM);
     met.SetPtEtaPhiM(corr_met_singleLepCalc,0,corr_met_phi_singleLepCalc,metM);
     mass_minBBdr = -1;
     mass_minLLdr = -1;
     mass_maxBBpt = -1;
     mass_maxBBmass = -1;
     minDR_lepBJet = 1e9;
     mass_lepBB_minBBdr = -1;
     mass_lepJJ_minJJdr = -1;
     mass_lepBJet0 = -1;
     deltaR_lepBJets0 = -1;
     deltaR_lepBJets1 = -1;     
     minMleppBjet = 1e9;
     mass_lepBJet_mindr = -1;
     deltaR_lepBJet_maxpt = -1;
     deltaPhi_maxBB = 1e9;
     hemiout = -1;
     deltaPhi_METjets.clear();
     min_deltaPhi_METjets = 1e9;
     aveCSV = -1;
     float totalPtCSV = 0;
     double deltaPhifromMET_ = TVector2::Phi_mpi_pi(leptonPhi_singleLepCalc - corr_met_phi_singleLepCalc);
     deltaPhi_lepMET = deltaPhifromMET_;
     if(abs(deltaPhifromMET_)>TMath::Pi()/2){hemiout+=leptonPt_singleLepCalc;}
     std::vector<float> v_CSVb_bb;

     
     for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
// 		if(njetscsv<=10 && theJetCSVb_JetSubCalc_PtOrdered->at(ijet)>=0 && theJetCSVbb_JetSubCalc_PtOrdered->at(ijet)>=0){ 
//      njetscsv cut <10 applied for the charged higgs analysis. remove this for 4 tops analysis
		if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 0){
		   njetscsv+=1;
		   totalPtCSV += theJetPt_JetSubCalc_PtOrdered->at(ijet);
		   aveCSVpt += (theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet))*theJetPt_JetSubCalc_PtOrdered->at(ijet);
		}
		totalJetPt+=theJetPt_JetSubCalc_PtOrdered->at(ijet);
		totalJetE+=theJetEnergy_JetSubCalc_PtOrdered->at(ijet);
		deltaPhifromMET_ = TVector2::Phi_mpi_pi(theJetPhi_JetSubCalc_PtOrdered->at(ijet) - corr_met_phi_singleLepCalc);
		deltaPhi_METjets.push_back(deltaPhifromMET_);
		if(min_deltaPhi_METjets>fabs(deltaPhifromMET_)){min_deltaPhi_METjets=fabs(deltaPhifromMET_);}
		if(abs(deltaPhifromMET_)>TMath::Pi()/2){hemiout+=theJetPt_JetSubCalc_PtOrdered->at(ijet);}				
		v_CSVb_bb.push_back(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet));
		
		if(!(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs
		
		bjet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));	
		HT_bjets+=theJetPt_JetSubCalc_PtOrdered->at(ijet);
		if (theJetPt_JetSubCalc_PtOrdered->at(ijet) < BJetLeadPt-0.001 && theJetPt_JetSubCalc_PtOrdered->at(ijet) >= BjetSecondPt) BjetSecondPt = theJetPt_JetSubCalc_PtOrdered->at(ijet);
		//different float precision between theJetPt_JetSubCalc_PtOrdered->at(ijet) and BJetLeadPt
		//require at least 0.001 between them to avoid double counting the leading bjet pt

		double lbdr_ = (bjet1).DeltaR(lep);
		double masslb = (lep+bjet1).M();
		double ptlb = (lep+bjet1).Pt();
		if(lbdr_<minDR_lepBJet){
			minDR_lepBJet=lbdr_;
			mass_lepBJet_mindr=masslb;
			}
		if(mass_lepBJet0<0){
			mass_lepBJet0 = masslb;
			deltaR_lepBJets0 = lbdr_;
			BJetLeadPt = theJetPt_JetSubCalc_PtOrdered->at(ijet);
		}
		if(masslb<minMleppBjet){minMleppBjet=masslb;}
		if(ptlb>maxLBpt){
			maxLBpt = ptlb;
			deltaR_lepBJet_maxpt = lbdr_;
			}
		        
		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  if(!(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs	  
		  bjet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));		  
          deltaR_lepBJets1 = (bjet1).DeltaR(lep);		  
		  npairs += 1.0;
		  double pairmass = (bjet1+bjet2).M();
		  double pairmasslep = (lep+bjet1+bjet2).M();
		  double pairdr = (bjet1).DeltaR(bjet2);
		  double pairdphi = (bjet1).DeltaPhi(bjet2);
		  double pairdeta = bjet1.Eta() - bjet2.Eta();
		  double pairpt = (bjet1+bjet2).Pt();
		  aveBBdr += (bjet1).DeltaR(bjet2);
		  if(pairmass > maxBBmass){
			maxBBmass = pairmass;	    
			mass_maxBBmass = pairmass;
		  }
		  if(pairdr < minBBdr){
			minBBdr = pairdr;
			mass_minBBdr = pairmass;
			lepDR_minBBdr = (bjet1+bjet2).DeltaR(lep);
			mass_lepBB_minBBdr = pairmasslep;
			deltaR_minBB = pairdr;
		  }
		  if(fabs(pairdphi) > maxBBdphi){
			maxBBdphi = fabs(pairdphi);
			deltaPhi_maxBB = pairdphi;
		  }		  
		  if(fabs(pairdeta) > maxBBdeta){
			maxBBdeta = fabs(pairdeta);
			deltaEta_maxBB = pairdeta;
		  }
		  if(pairpt > maxBBpt){
			maxBBpt = pairpt;
			mass_maxBBpt = pairmass;
		  }		  
		}
	  }
     std::sort(v_CSVb_bb.rbegin(), v_CSVb_bb.rend());
//      for (auto csvb_bb = v_CSVb_bb.begin(); csvb_bb != v_CSVb_bb.end(); ++csvb_bb){
//         std::cout << *csvb_bb << std::endl;     
//      }
     thirdcsvb_bb = v_CSVb_bb.at(2);
     fourthcsvb_bb = v_CSVb_bb.at(3);
     if (BJetLeadPt>0) HT_2m = AK4HT - (BJetLeadPt+BjetSecondPt);
     else{HT_2m=-100;}
//////////////////////////////////////////
// build centrality //
//////////////////////////////////////////
      if(npairs!=0){aveBBdr = (aveBBdr+1)/npairs;}
      if(njetscsv!=0){
      	aveCSV = (aveCSV+1)/njetscsv;
      	aveCSVpt = (aveCSVpt+1)/totalPtCSV;
      	}
      else{aveCSV = coin; aveCSVpt = coin;}
      
      if(totalJetE!=0) {centrality = totalJetPt/totalJetE;}	  

      // FIND LIGHT PAIRS
	  for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		if((theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs

		jet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));

		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  if((theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs
	  
		  jet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));

		  double pairdr = (jet1).DeltaR(jet2);
		  double pairmass = (jet1+jet2).M();
		  double pairmasslep = (lep+jet1+jet2).M();
		  if(pairdr < minLLdr){
			minLLdr = pairdr;
			mass_minLLdr = pairmass;
			mass_lepJJ_minJJdr = pairmasslep;
		  }
		}
	  }

	  jet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(0),theJetEta_JetSubCalc_PtOrdered->at(0),theJetPhi_JetSubCalc_PtOrdered->at(0),theJetEnergy_JetSubCalc_PtOrdered->at(0));
	  jet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(1),theJetEta_JetSubCalc_PtOrdered->at(1),theJetPhi_JetSubCalc_PtOrdered->at(1),theJetEnergy_JetSubCalc_PtOrdered->at(1));
	  jet3.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(2),theJetEta_JetSubCalc_PtOrdered->at(2),theJetPhi_JetSubCalc_PtOrdered->at(2),theJetEnergy_JetSubCalc_PtOrdered->at(2));	  
      deltaPhi_j1j2 = (jet1).DeltaPhi(jet2);
      alphaT = TMath::Sqrt( (theJetPt_JetSubCalc_PtOrdered->at(1)/theJetPt_JetSubCalc_PtOrdered->at(0)) / (2.0*(1.0-TMath::Cos(deltaPhi_j1j2))) );
      mass_lepJets0 = (lep+jet1).M();
      mass_lepJets1 = (lep+jet2).M();
      mass_lepJets2 = (lep+jet3).M();
	  
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


      PtFifthJet = -1;
      int fifthJetInd = 0;
      for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
      	if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 1){
      		fifthJetInd+=1;
      		if(fifthJetInd==5){PtFifthJet=theJetPt_JetSubCalc_PtOrdered->at(ijet);}
      		if(fifthJetInd>=5) break;
      		}
      	}
      if(fifthJetInd<5){
		for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		   if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 0){
			 fifthJetInd+=1;
			 if(fifthJetInd==5){PtFifthJet=theJetPt_JetSubCalc_PtOrdered->at(ijet);}
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
		  FW_momentum_0 += ET_ij_over_ETSum2;
		  FW_momentum_1 += ET_ij_over_ETSum2 * cosTheta_ij;
		  FW_momentum_2 += ET_ij_over_ETSum2 * 0.5   * (  3*std::pow(cosTheta_ij,2)- 1);
		  FW_momentum_3 += ET_ij_over_ETSum2 * 0.5   * (  5*std::pow(cosTheta_ij,3)-  3*cosTheta_ij);
		  FW_momentum_4 += ET_ij_over_ETSum2 * 0.125 * ( 35*std::pow(cosTheta_ij,4)- 30*std::pow(cosTheta_ij,2)+3);
		  FW_momentum_5 += ET_ij_over_ETSum2 * 0.125 * ( 63*std::pow(cosTheta_ij,5)- 70*std::pow(cosTheta_ij,3)+15*cosTheta_ij);
		  FW_momentum_6 += ET_ij_over_ETSum2 * 0.0625* (231*std::pow(cosTheta_ij,6)-315*std::pow(cosTheta_ij,4)+105*std::pow(cosTheta_ij,2)-5);
		}
	  }
	  b_isTraining->Fill();
	  b_deltaR_minBB->Fill();
	  b_aveBBdr->Fill();
	  b_deltaEta_maxBB->Fill();
	  b_FW_momentum_2->Fill();
	  b_centrality->Fill();
	  b_aveCSVpt->Fill();
	  b_mass_maxJJJpt->Fill();
	  b_lepDR_minBBdr->Fill();
	  b_HT_bjets->Fill();
	  b_HT_ratio->Fill();
	  b_HT_2m->Fill();
	  b_thirdcsvb_bb->Fill();
	  b_fourthcsvb_bb->Fill();
	  b_PtFifthJet->Fill();

	  b_mass_lepJets0->Fill();
	  b_mass_lepJets1->Fill();
	  b_mass_lepJets2->Fill();	  	  
	  b_mass_minBBdr->Fill();
	  b_mass_minLLdr->Fill();
	  b_mass_maxBBpt->Fill();
	  b_mass_maxBBmass->Fill();
	  b_theJetLeadPt->Fill();
	  b_deltaR_lepBJets0->Fill();
	  b_deltaR_lepBJets1->Fill();	  
	  b_minDR_lepBJet->Fill();
	  b_minBBdr->Fill();
	  b_mass_lepBJet0->Fill();
	  b_mass_lepBB_minBBdr->Fill();
	  b_mass_lepJJ_minJJdr->Fill();
	  b_mass_lepBJet_mindr->Fill();
	  b_deltaR_lepBJet_maxpt->Fill();
	  b_deltaPhi_maxBB->Fill();
	  b_hemiout->Fill();
	  b_corr_met->Fill();
	  b_deltaPhi_lepMET->Fill();
	  b_min_deltaPhi_METjets->Fill();
	  b_deltaPhi_METjets->Fill();
	  b_aveCSV->Fill();
	  b_deltaPhi_j1j2->Fill();
	  b_alphaT->Fill();
	  b_FW_momentum_0->Fill();
	  b_FW_momentum_1->Fill();
	  b_FW_momentum_3->Fill();
	  b_FW_momentum_4->Fill();
	  b_FW_momentum_5->Fill();
	  b_FW_momentum_6->Fill();
   }
std::cout<<"DONE "<<nentries<<std::endl;   
outputFile->Write();
delete outputFile;
delete inputFile;
}
