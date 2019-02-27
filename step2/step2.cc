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

float mt2( const TLorentzVector visa,  const TLorentzVector visb,  const TLorentzVector metVec)
{

    Davismt2 davismt2;
    const double mn = 0.; // neutrino mass
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
   TBranch *b_csvJet3               = outputTree->Branch("csvJet3",&csvJet3,"csvJet3/F");
   TBranch *b_csvJet4               = outputTree->Branch("csvJet4",&csvJet4,"csvJet4/F");


   TBranch *b_MHRE                  = outputTree->Branch("MHRE",&MHRE,"MHRE/F");              
   TBranch *b_HTx                   = outputTree->Branch("HTx",&HTx,"HTx/F");                 
   
   TBranch *b_GD_DCSV_jetNotdijet   = outputTree->Branch("GD_DCSV_jetNotdijet",&GD_DCSV_jetNotdijet,"GD_DCSV_jetNotdijet/F");
   TBranch *b_BD_DCSV_jetNotdijet   = outputTree->Branch("BD_DCSV_jetNotdijet",&BD_DCSV_jetNotdijet);
   TBranch *b_GD_DR_Tridijet        = outputTree->Branch("GD_DR_Tridijet",&GD_DR_Tridijet,"GD_DR_Tridijet/F");
   TBranch *b_BD_DR_Tridijet        = outputTree->Branch("BD_DR_Tridijet",&BD_DR_Tridijet);      
   TBranch *b_GD_Ttrijet_TopMass    = outputTree->Branch("GD_Ttrijet_TopMass",&GD_Ttrijet_TopMass,"GD_Ttrijet_TopMass/F");
   TBranch *b_BD_Ttrijet_TopMass    = outputTree->Branch("BD_Ttrijet_TopMass",&BD_Ttrijet_TopMass);   
   TBranch *b_GD_Mass_minDR_dijet   = outputTree->Branch("GD_Mass_minDR_dijet",&GD_Mass_minDR_dijet,"GD_Mass_minDR_dijet/F");      
   TBranch *b_BD_Mass_minDR_dijet   = outputTree->Branch("BD_Mass_minDR_dijet",&BD_Mass_minDR_dijet);         
   TBranch *b_minMleppJet           = outputTree->Branch("minMleppJet",&minMleppJet,"minMleppJet/F");   
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
   TBranch *b_MT2bb                 = outputTree->Branch("MT2bb",&MT2bb,"MT2bb/F");
   TBranch *b_GD_pTrat              = outputTree->Branch("GD_pTrat",&GD_pTrat,"GD_pTrat/F");
   TBranch *b_BD_pTrat              = outputTree->Branch("BD_pTrat",&BD_pTrat);


   TBranch *b_GD_DR_Trijet_jetNotdijet       = outputTree->Branch("GD_DR_Trijet_jetNotdijet",&GD_DR_Trijet_jetNotdijet,"GD_DR_Trijet_jetNotdijet/F");
   TBranch *b_BD_DR_Trijet_jetNotdijet       = outputTree->Branch("BD_DR_Trijet_jetNotdijet",&BD_DR_Trijet_jetNotdijet);

   TBranch *b_deltaR_lepJetInMinMljet        = outputTree->Branch("deltaR_lepJetInMinMljet",&deltaR_lepJetInMinMljet,"deltaR_lepJetInMinMljet/F");
   TBranch *b_deltaPhi_lepJetInMinMljet      = outputTree->Branch("deltaPhi_lepJetInMinMljet",&deltaPhi_lepJetInMinMljet,"deltaPhi_lepJetInMinMljet/F");
   TBranch *b_deltaR_lepbJetInMinMlb         = outputTree->Branch("deltaR_lepbJetInMinMlb",&deltaR_lepbJetInMinMlb,"deltaR_lepbJetInMinMlb/F");
   TBranch *b_deltaPhi_lepbJetInMinMlb       = outputTree->Branch("deltaPhi_lepbJetInMinMlb",&deltaPhi_lepbJetInMinMlb,"deltaPhi_lepbJetInMinMlb/F");

   Long64_t nentries = inputTree->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TLorentzVector bjet1, bjet2, jet1, jet2, jet3, lep, met, jetTmp, BestTOPjet1, BestTOPjet2, BestTOPjet3, BADTOPjet1, BADTOPjet2, BADTOPjet3;   
   
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
     minMleppJet = 1e9;     
     tmp_minMleppBjet = 1e9;          
     aveCSVpt = 0;
     MT2bb = 0;      
     deltaR_minBB = 1e9;
     aveBBdr = -1;      
     deltaEta_maxBB = 1e9;                  
     lepDR_minBBdr = -1;
     mass_maxJJJpt = -1;      
     FW_momentum_0=0; FW_momentum_1=0; FW_momentum_2=0; FW_momentum_3=0; FW_momentum_4=0; FW_momentum_5=0; FW_momentum_6=0;
     centrality = -1;      
     HT_bjets = -10;
     HT_ratio = -1; //for ratio of HT(j1,2,3,4)/HT(other jets)     
     HT_2m = -10;
     theJetLeadPt = -1000; 
     mass_lepJets0 = -1;             
     mass_lepJets1 = -1;                          
     mass_lepJets2 = -1;  
     MHRE = -100;     
     HTx = 0;                             
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
     mass_lepBJet_mindr = -1;
     deltaR_lepBJet_maxpt = -1;
     deltaR_lepJetInMinMljet = -99;
     deltaPhi_lepJetInMinMljet = -99;
     deltaR_lepbJetInMinMlb = -99;
     deltaPhi_lepbJetInMinMlb = -99;
     deltaPhi_maxBB = 1e9;
     hemiout = -1;
     deltaPhi_METjets.clear();
     min_deltaPhi_METjets = 1e9;
     aveCSV = -1;
     csvJet3 = 0;
     csvJet4 = 0;
     float totalPtCSV = 0;
     double deltaPhifromMET_ = TVector2::Phi_mpi_pi(leptonPhi_singleLepCalc - corr_met_phi_singleLepCalc);
     deltaPhi_lepMET = deltaPhifromMET_;
     if(abs(deltaPhifromMET_)>TMath::Pi()/2){hemiout+=leptonPt_singleLepCalc;}

     std::vector<float> v_CSVb_bb;
     std::vector<TLorentzVector> v_allJets;
     std::vector<TLorentzVector> v_trijet;
     std::vector<double> v_DCSV_allJets;          
     std::vector<double> v_DCSV_trijet;     
     std::vector<TLorentzVector> v_BADtrijet;  
     v_trijet.clear();   
     v_BADtrijet.clear();        

     GD_DR_Tridijet = 1e9;
     BD_DR_Tridijet.clear();

     GD_Mass_minDR_dijet = 1e9;
     BD_Mass_minDR_dijet.clear();

     GD_Ttrijet_TopMass = 1e9;
     BD_Ttrijet_TopMass.clear();

     GD_DR_Trijet_jetNotdijet = 1e9;     
     BD_DR_Trijet_jetNotdijet.clear();
          
     for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
// 		if(njetscsv<=10 && theJetCSVb_JetSubCalc_PtOrdered->at(ijet)>=0 && theJetCSVbb_JetSubCalc_PtOrdered->at(ijet)>=0){ 
//      njetscsv cut <10 applied for the charged higgs analysis. remove this for 4 tops analysis
// 		if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 0){
		if(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) < 0.4941){
		   njetscsv+=1;
		   totalPtCSV += theJetPt_JetSubCalc_PtOrdered->at(ijet);
		   aveCSVpt += (theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet))*theJetPt_JetSubCalc_PtOrdered->at(ijet);
		}
		
        TLorentzVector jetTmp;   		
		jetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));	

        if((lep + jetTmp).M() < minMleppJet) {
          minMleppJet = fabs((lep + jetTmp).M());
          deltaR_lepJetInMinMljet  = jetTmp.DeltaR(lep);
          deltaPhi_lepJetInMinMljet = jetTmp.DeltaPhi(lep);
        }		

//         if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 1){
		if(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941){        
          if((lep + jetTmp).M() < tmp_minMleppBjet) {
            tmp_minMleppBjet = fabs((lep + jetTmp).M() );
            deltaR_lepbJetInMinMlb = jetTmp.DeltaR(lep);
            deltaPhi_lepbJetInMinMlb = jetTmp.DeltaPhi(lep);
          }        
        
        }
        
	    v_allJets.push_back(jetTmp);
        v_DCSV_allJets.push_back(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet));
	    csvJet3 = theJetCSVb_JetSubCalc_PtOrdered->at(2)+theJetCSVbb_JetSubCalc_PtOrdered->at(2);
	    csvJet4 = theJetCSVb_JetSubCalc_PtOrdered->at(3)+theJetCSVbb_JetSubCalc_PtOrdered->at(3);	    
        	    
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
		if(ptlb>maxLBpt){
			maxLBpt = ptlb;
			deltaR_lepBJet_maxpt = lbdr_;
			}
		        
		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  if(!(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs	  
		  bjet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));		  
          MT2bb = mt2(bjet1,bjet2,met);
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

////////////////////////////////
/////// trijet selection ///////
////////////////////////////////

     std::string bitmask(3,1);
     bitmask.resize(v_allJets.size(),0);
     double tempTtrijetMass = 0;
     double diff_TopMass = 1e9;
     double Mag_Trijet = 1e9;         
     double ScalarSumpT_Trijet = 1e9;
     double DCSV_BestTOPjet1 = 0;
     double DCSV_BestTOPjet2 = 0;
     double DCSV_BestTOPjet3 = 0;    
     GD_DCSV_jetNotdijet=0;           
     GD_pTrat = 1e9;              

     do {
            v_trijet.clear();
            v_DCSV_trijet.clear();
            for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
                if(bitmask[njet]) {
                    v_trijet.push_back(v_allJets[njet]);
                    v_DCSV_trijet.push_back(v_DCSV_allJets[njet]);
                }
            }
            tempTtrijetMass = (v_trijet[0]+v_trijet[1]+v_trijet[2]).M();
            if (fabs(tempTtrijetMass-MTOP)< diff_TopMass){
                diff_TopMass    = fabs(tempTtrijetMass-MTOP);
                BestTOPjet1     = v_trijet[0];
                BestTOPjet2     = v_trijet[1];                
                BestTOPjet3     = v_trijet[2];
                DCSV_BestTOPjet1     = v_DCSV_trijet[0];
                DCSV_BestTOPjet2     = v_DCSV_trijet[1];                
                DCSV_BestTOPjet3     = v_DCSV_trijet[2];
                Mag_Trijet = (BestTOPjet1+BestTOPjet2+BestTOPjet3).Mag();
                ScalarSumpT_Trijet = (BestTOPjet1.Pt()+BestTOPjet2.Pt()+BestTOPjet3.Pt());

            }            
     } while(std::prev_permutation(bitmask.begin(), bitmask.end()));          

     if (diff_TopMass>30){
        GD_pTrat = -10;  
        GD_Ttrijet_TopMass = -10;
        GD_DCSV_jetNotdijet = -10;
        GD_Mass_minDR_dijet = -10;
        GD_DR_Tridijet = -10;
        GD_DR_Trijet_jetNotdijet = -10;
        MHRE = -100;
        HTx = -100;
     }
     else{
         GD_pTrat = Mag_Trijet/ScalarSumpT_Trijet;                                            
         GD_Ttrijet_TopMass = (BestTOPjet1+BestTOPjet2+BestTOPjet3).M();
         double v_dr[3];
         TLorentzVector dijet, jetNotdijet;     
         v_dr[0] = BestTOPjet1.DeltaR(BestTOPjet2);
         v_dr[1] = BestTOPjet1.DeltaR(BestTOPjet3);
         v_dr[2] = BestTOPjet2.DeltaR(BestTOPjet3); 
         int idx_minDR_jetCombo = std::min_element(v_dr, v_dr+3) - v_dr;
         if(idx_minDR_jetCombo==0){
             dijet = BestTOPjet1+BestTOPjet2;
             jetNotdijet = BestTOPjet3;
             GD_DCSV_jetNotdijet = DCSV_BestTOPjet3;
         }
         else if (idx_minDR_jetCombo==1){                                     
             dijet = BestTOPjet1+BestTOPjet3;
             jetNotdijet = BestTOPjet2;
             GD_DCSV_jetNotdijet = DCSV_BestTOPjet2;         
         }
         else if (idx_minDR_jetCombo==2){
             dijet = BestTOPjet2+BestTOPjet3;     
             jetNotdijet = BestTOPjet1;
             GD_DCSV_jetNotdijet = DCSV_BestTOPjet1;         
         }
         GD_Mass_minDR_dijet = dijet.M();
         GD_DR_Tridijet = (BestTOPjet1+BestTOPjet2+BestTOPjet3).DeltaR(dijet);
         GD_DR_Trijet_jetNotdijet = (BestTOPjet1+BestTOPjet2+BestTOPjet3).DeltaR(jetNotdijet);
         TLorentzVector totalSumJetVect, totalSumJetVect_noTrijet;
         for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
            totalSumJetVect += v_allJets[njet];
         }
         totalSumJetVect_noTrijet = totalSumJetVect-BestTOPjet1-BestTOPjet2-BestTOPjet3;
         MHRE = totalSumJetVect_noTrijet.M();
         HTx = AK4HT-BestTOPjet1.Pt()-BestTOPjet2.Pt()-BestTOPjet3.Pt();
     }
     double DCSV_BADTOPjet1=0;
     double DCSV_BADTOPjet2=0;
     double DCSV_BADTOPjet3=0;     
     BD_pTrat.clear();
     BD_DCSV_jetNotdijet.clear();
     do {
            v_BADtrijet.clear();
            v_DCSV_trijet.clear();
            for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
                if(bitmask[njet]) {
                    v_BADtrijet.push_back(v_allJets[njet]);
                    v_DCSV_trijet.push_back(v_DCSV_allJets[njet]);
                }
            }
            tempTtrijetMass = (v_BADtrijet[0]+v_BADtrijet[1]+v_BADtrijet[2]).M();
            if (fabs(tempTtrijetMass-MTOP) == diff_TopMass){
                continue;
            }
            else if (fabs(tempTtrijetMass-MTOP) > 30){ continue; }                       
            else{            
                BADTOPjet1     = v_BADtrijet[0];
                BADTOPjet2     = v_BADtrijet[1];                
                BADTOPjet3     = v_BADtrijet[2];                            
                DCSV_BADTOPjet1     = v_DCSV_trijet[0];
                DCSV_BADTOPjet2     = v_DCSV_trijet[1];                
                DCSV_BADTOPjet3     = v_DCSV_trijet[2];

                BD_Ttrijet_TopMass.push_back((BADTOPjet1+BADTOPjet2+BADTOPjet3).M());
                double v_BADdr[3];
                TLorentzVector BAD_dijet, jetNotdijet;     
                v_BADdr[0] = BADTOPjet1.DeltaR(BADTOPjet2);
                v_BADdr[1] = BADTOPjet2.DeltaR(BADTOPjet3);
                v_BADdr[2] = BADTOPjet2.DeltaR(BADTOPjet3); 

                int idx_minDR_jetCombo = std::min_element(v_BADdr, v_BADdr+3) - v_BADdr;
                if(idx_minDR_jetCombo==0){
                    BAD_dijet = BADTOPjet1+BADTOPjet2;
                    jetNotdijet = BADTOPjet3;
                    BD_DCSV_jetNotdijet.push_back(DCSV_BADTOPjet3);
                }
                else if (idx_minDR_jetCombo==1){                                     
                    BAD_dijet = BADTOPjet1+BADTOPjet3;
                    jetNotdijet = BADTOPjet2;
                    BD_DCSV_jetNotdijet.push_back(DCSV_BADTOPjet2);
                }
                else if (idx_minDR_jetCombo==2){
                    BAD_dijet = BADTOPjet2+BADTOPjet3;     
                    jetNotdijet = BADTOPjet1;
                    BD_DCSV_jetNotdijet.push_back(DCSV_BADTOPjet1);
                }
                BD_Mass_minDR_dijet.push_back(BAD_dijet.M());
                Mag_Trijet = (BADTOPjet1+BADTOPjet2+BADTOPjet3).Mag();
                ScalarSumpT_Trijet = (BADTOPjet1.Pt()+BADTOPjet2.Pt()+BADTOPjet3.Pt());
                BD_pTrat.push_back(Mag_Trijet/ScalarSumpT_Trijet);
                BD_DR_Tridijet.push_back((BADTOPjet1+BADTOPjet2+BADTOPjet3).DeltaR(BAD_dijet));                                                                            
                BD_DR_Trijet_jetNotdijet.push_back((BADTOPjet1+BADTOPjet2+BADTOPjet3).DeltaR(jetNotdijet));
            }
     } while(std::prev_permutation(bitmask.begin(), bitmask.end()));          

     

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
//       	if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 1){
		    if(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941){        
      		fifthJetInd+=1;
      		if(fifthJetInd==5){PtFifthJet=theJetPt_JetSubCalc_PtOrdered->at(ijet);}
      		if(fifthJetInd>=5) break;
      		}
      	}
      if(fifthJetInd<5){
		for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
// 		   if(theJetBTag_JetSubCalc_PtOrdered->at(ijet) == 0){
	    	if(theJetCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetCSVbb_JetSubCalc_PtOrdered->at(ijet) < 0.4941){        
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

      b_MHRE->Fill();
      b_HTx->Fill();
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
      b_csvJet3->Fill();
      b_csvJet4->Fill();      
     
	  b_GD_pTrat->Fill();
	  b_BD_pTrat->Fill();	  
      b_GD_DR_Tridijet->Fill();
	  b_BD_DR_Tridijet->Fill();
	  b_GD_Ttrijet_TopMass->Fill();
	  b_BD_Ttrijet_TopMass->Fill();
      b_GD_DCSV_jetNotdijet->Fill();
      b_BD_DCSV_jetNotdijet->Fill();      
	  b_GD_Mass_minDR_dijet->Fill();	  
	  b_BD_Mass_minDR_dijet->Fill();	  	  
	  b_GD_DR_Trijet_jetNotdijet->Fill();
	  b_BD_DR_Trijet_jetNotdijet->Fill();
	  b_deltaR_lepJetInMinMljet->Fill();
	  b_deltaPhi_lepJetInMinMljet->Fill();	  
	  b_deltaR_lepbJetInMinMlb->Fill();
	  b_deltaPhi_lepbJetInMinMlb->Fill();	  
   }
std::cout<<"DONE "<<nentries<<std::endl;   
outputFile->Write();
delete outputFile;
delete inputFile;
}
