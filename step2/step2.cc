#define step2_cxx
#include "step2.h"
//#include "GeneralFunctions.h"
#include <TH2.h>
#include <TH1.h>
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
#include <TMatrixD.h>
#include <TVectorT.h>
#include "TROOT.h"
#include "Davismt2.h"
#include <bits/stdc++.h> 

using namespace std;

const double MTOP  = 173.5;
const double MW    = 80.4;
TLorentzVector Wlv;


void Trijet(
vector<TLorentzVector> &v_trijet, 
vector<double> &v_DCSV_trijet, 
vector<TLorentzVector> &v_allJets, 
vector<double> &v_DCSV_allJets,

vector<TLorentzVector>& v_GD_Trijets,                    
vector<TLorentzVector>& v_GD_jets,                     
vector<double>& v_GD_DCSV_jets,                          

vector<TLorentzVector>& v_BD_Trijets,                   
vector<TLorentzVector>& v_BD_jets,                       
vector<double>& v_BD_DCSV_jets,                            

vector<double>* topPt_TTbarMassCalc,

vector<double>* topWID_TTbarMassCalc,
vector<double>* topWPt_TTbarMassCalc,
vector<double>* topWEta_TTbarMassCalc,
vector<double>* topWPhi_TTbarMassCalc,
vector<double>* topWEnergy_TTbarMassCalc,

vector<double>* topbPt_TTbarMassCalc,
vector<double>* topbEta_TTbarMassCalc,
vector<double>* topbPhi_TTbarMassCalc,
vector<double>* topbEnergy_TTbarMassCalc, 

int& num_GD_trijet,
int& num_BD_trijet
){
    std::string bitmask(3,1);
    bitmask.resize(v_allJets.size(),0);
    std::vector<double> v_deltalR; 

    TLorentzVector tempGenTop;
    TLorentzVector tempGenTopWd1, tempGenTopWd2;    
    TLorentzVector tempGenTopb;
    int idx_minDR = -10;
           
    do {
        v_trijet.clear();
        v_DCSV_trijet.clear();

        for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
            if(bitmask[njet]) {
                v_trijet.push_back(v_allJets[njet]);
                v_DCSV_trijet.push_back(v_DCSV_allJets[njet]);
            } 
        }
        bitset<9> tempbit9set;        
        std::vector<bitset<9>> v_bit9set;
        std::vector<Double_t> v_flipDeltaR;

        v_bit9set.clear();
        v_flipDeltaR.clear();
        
        int matchedTopIdx = 0;        
        for(unsigned int njet = 0; njet < 3; ++njet){
            v_deltalR.clear();
            tempbit9set.reset();                
            for(unsigned int nTop = 0; nTop < topPt_TTbarMassCalc->size(); nTop++){
                if(abs(topWID_TTbarMassCalc->at(nTop*2)) > 6 || abs(topWID_TTbarMassCalc->at(nTop*2+1)) > 6){ 
                    continue; 
                }
                tempGenTopWd1.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2),topWEta_TTbarMassCalc->at(nTop*2),topWPhi_TTbarMassCalc->at(nTop*2),topWEnergy_TTbarMassCalc->at(nTop*2));	
                tempGenTopWd2.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2+1),topWEta_TTbarMassCalc->at(nTop*2+1),topWPhi_TTbarMassCalc->at(nTop*2+1),topWEnergy_TTbarMassCalc->at(nTop*2+1));	        
                tempGenTopb.SetPtEtaPhiE(topbPt_TTbarMassCalc->at(nTop),topbEta_TTbarMassCalc->at(nTop),topbPhi_TTbarMassCalc->at(nTop),topbEnergy_TTbarMassCalc->at(nTop));
                v_deltalR.push_back(v_trijet[njet].DeltaR(tempGenTopWd1));                                                            
                v_deltalR.push_back(v_trijet[njet].DeltaR(tempGenTopWd2));                                                            
                v_deltalR.push_back(v_trijet[njet].DeltaR(tempGenTopb));
            }
            idx_minDR = std::distance(v_deltalR.begin(), std::min_element(v_deltalR.begin(), v_deltalR.end()));
            if(v_deltalR[idx_minDR]<0.5){
                tempbit9set.flip(idx_minDR);
            }
            v_flipDeltaR.push_back(v_deltalR[idx_minDR]);
            v_bit9set.push_back(tempbit9set);
        }
        bitset<9> bit9set;        
        bit9set = (v_bit9set[0]|v_bit9set[1])|v_bit9set[2];             ///////////////// a complete bitset for a trijet /////////////////                 
        if(bit9set.test(0)*bit9set.test(1)*bit9set.test(2) || bit9set.test(3)*bit9set.test(4)*bit9set.test(5) || bit9set.test(6)*bit9set.test(7)*bit9set.test(8)){
            v_GD_Trijets.push_back(v_trijet[0]+v_trijet[1]+v_trijet[2]);
            v_GD_jets.push_back(v_trijet[0]);
            v_GD_jets.push_back(v_trijet[1]);
            v_GD_jets.push_back(v_trijet[2]);
            v_GD_DCSV_jets.push_back(v_DCSV_trijet[0]);                        
            v_GD_DCSV_jets.push_back(v_DCSV_trijet[1]);                        
            v_GD_DCSV_jets.push_back(v_DCSV_trijet[2]);                                                
            num_GD_trijet++;
        }
        else {
            num_BD_trijet++;
            v_BD_Trijets.push_back(v_trijet[0]+v_trijet[1]+v_trijet[2]);
            v_BD_jets.push_back(v_trijet[0]);
            v_BD_jets.push_back(v_trijet[1]);
            v_BD_jets.push_back(v_trijet[2]);
            v_BD_DCSV_jets.push_back(v_DCSV_trijet[0]);                        
            v_BD_DCSV_jets.push_back(v_DCSV_trijet[1]);                        
            v_BD_DCSV_jets.push_back(v_DCSV_trijet[2]);                                                                
        }
    } while(std::prev_permutation(bitmask.begin(), bitmask.end()));       
}


TMatrixD SpheAplaTensor(const vector<TLorentzVector> allJets){
      TMatrixD MomentumTensor(3,3); 
      Double_t p2_sum=0.0;
      for(unsigned int njet = 0; njet < allJets.size(); ++njet){
        MomentumTensor(0, 0) += allJets[njet].Px()*allJets[njet].Px();
        MomentumTensor(0, 1) += allJets[njet].Px()*allJets[njet].Py();
        MomentumTensor(0, 2) += allJets[njet].Px()*allJets[njet].Pz();
        MomentumTensor(1, 0) += allJets[njet].Py()*allJets[njet].Px();
        MomentumTensor(1, 1) += allJets[njet].Py()*allJets[njet].Py();
        MomentumTensor(1, 2) += allJets[njet].Py()*allJets[njet].Pz();
        MomentumTensor(2, 0) += allJets[njet].Pz()*allJets[njet].Px();
        MomentumTensor(2, 1) += allJets[njet].Pz()*allJets[njet].Py();
        MomentumTensor(2, 2) += allJets[njet].Pz()*allJets[njet].Pz();
        p2_sum += allJets[njet].Px()*allJets[njet].Px()+allJets[njet].Py()*allJets[njet].Py()+allJets[njet].Pz()*allJets[njet].Pz();
      }
      if (p2_sum != 0){
          MomentumTensor(0, 0) /= p2_sum;
          MomentumTensor(0, 1) /= p2_sum;
          MomentumTensor(0, 2) /= p2_sum;
          MomentumTensor(1, 0) /= p2_sum;
          MomentumTensor(1, 1) /= p2_sum;
          MomentumTensor(1, 2) /= p2_sum;
          MomentumTensor(2, 0) /= p2_sum;
          MomentumTensor(2, 1) /= p2_sum;
          MomentumTensor(2, 2) /= p2_sum;
      }
      TVectorD *_pv = new TVectorD(3);
      return MomentumTensor;
}

bool compareFunc(const pair<TLorentzVector, double> &a, const pair<TLorentzVector, double> &b){
    return (a.second > b.second);
}

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

TLorentzVector bestJet( const double corr_met_phi, 
                        const double corr_met, 
                        const double lepMass, 
                        const TLorentzVector lepVector, 
                        const vector<double>* theJetPt_PtOrdered,
                        const vector<double>* theJetEta_PtOrdered,
                        const vector<double>* theJetPhi_PtOrdered,
                        const vector<double>* theJetEnergy_PtOrdered                                                
                        ){
      double metpx = corr_met*cos(corr_met_phi);
      double metpy = corr_met*sin(corr_met_phi);
      double metpt = corr_met;

      double Dtmp = (MW*MW)-(lepMass*lepMass)+2*((lepVector.Px())*(metpx)+(lepVector.Py())*(metpy));
      double Atmp = 4.0*((lepVector.Energy())*(lepVector.Energy())-(lepVector.Pz())*(lepVector.Pz()));
      double Btmp = -4.0*Dtmp*(lepVector.Pz());
      double Ctmp = 4.0*(lepVector.Energy())*(lepVector.Energy())*(metpt)*(metpt)-Dtmp*Dtmp;
      
      double nuPz_1;
      double nuPz_2;
      
      double DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
      
      TLorentzVector Wlv_1, Wlv_2, lvTop, lvXTF;
      if(DETtmp >= 0) {
        nuPz_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
        nuPz_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
        TLorentzVector Nulv_1(metpx,metpy,nuPz_1,TMath::Sqrt((metpt)*(metpt)+(nuPz_1)*(nuPz_1)));
        TLorentzVector Nulv_2(metpx,metpy,nuPz_2,TMath::Sqrt((metpt)*(metpt)+(nuPz_2)*(nuPz_2)));
        Wlv_1 = Nulv_1+lepVector;
        Wlv_2 = Nulv_2+lepVector;
      }
      if(DETtmp < 0) {
        nuPz_1 = (-Btmp)/(2.0*Atmp);
        nuPz_2 = (-Btmp)/(2.0*Atmp);
        double alpha = (lepVector.Px())*(metpx)/(metpt)+(lepVector.Py())*(metpy)/(metpt);
        double Delta = (MW*MW)-(lepMass*lepMass);
        Atmp = 4.0*((lepVector.Pz())*(lepVector.Pz())-(lepVector.Energy())*(lepVector.Energy())+(alpha*alpha));
        Btmp = 4.0*alpha*Delta;
        Ctmp = Delta*Delta;
        DETtmp = Btmp*Btmp-4.0*Atmp*Ctmp;
        double pTnu_1 = (-Btmp+TMath::Sqrt(DETtmp))/(2.0*Atmp);
        double pTnu_2 = (-Btmp-TMath::Sqrt(DETtmp))/(2.0*Atmp);
        TLorentzVector Nulv_1(metpx*(pTnu_1)/(metpt),metpy*(pTnu_1)/(metpt),nuPz_1,TMath::Sqrt((pTnu_1)*(pTnu_1)+(nuPz_1)*(nuPz_1)));
        TLorentzVector Nulv_2(metpx*(pTnu_2)/(metpt),metpy*(pTnu_2)/(metpt),nuPz_2,TMath::Sqrt((pTnu_2)*(pTnu_2)+(nuPz_2)*(nuPz_2)));
        Wlv_1 = Nulv_1+lepVector;
        Wlv_2 = Nulv_2+lepVector;
        if (fabs(Wlv_1.M()-MW) < fabs(Wlv_2.M()-MW)) Wlv_2 = Wlv_1;
        else Wlv_1 = Wlv_2;
      }
      
      // ----------------------------------------------------------------------------
      // top --> W b --> l nu b using W from above
      // ----------------------------------------------------------------------------

      double dMTOP = 1e8;
      unsigned int topIndex = 0;
      bool firstW = true;
      double MTop_1, MTop_2;
      TLorentzVector jet_lv;
      for(unsigned int ijet=0; ijet < theJetPt_PtOrdered->size(); ijet++){
        jet_lv.SetPtEtaPhiE(theJetPt_PtOrdered->at(ijet),theJetEta_PtOrdered->at(ijet),theJetPhi_PtOrdered->at(ijet),theJetEnergy_PtOrdered->at(ijet));
        MTop_1 = (jet_lv + Wlv_1).M();
        MTop_2 = (jet_lv + Wlv_2).M();
        if(fabs(MTop_1 - MTOP) < dMTOP) {
          if(fabs(MTop_1 - MTOP) < fabs(MTop_2 - MTOP)) {
            firstW = true;
            topIndex = ijet;
            dMTOP = fabs(MTop_1 - MTOP);
          }
          else {
            firstW = false;
            topIndex = ijet;
            dMTOP = fabs(MTop_2 - MTOP);
          }
        }
        else if(fabs(MTop_2 - MTOP) < dMTOP) {
          firstW = false;
          topIndex = ijet;
          dMTOP = fabs(MTop_2 - MTOP);
        }
      }
      if(firstW) {Wlv = Wlv_1;}
      else{Wlv = Wlv_2;}
      jet_lv.SetPtEtaPhiE(theJetPt_PtOrdered->at(topIndex),theJetEta_PtOrdered->at(topIndex),theJetPhi_PtOrdered->at(topIndex),theJetEnergy_PtOrdered->at(topIndex));
      return jet_lv;
}


void step2::Loop()
{   
   if (inputTree == 0) return;
   outputFile->cd();
//    gROOT->SetBatch(kTRUE);   
   TTree *outputTree = inputTree->CloneTree(); //Copy of Input Tree
//    TTree *outputTree = new TTree("ljmet","ljmet"); //No Copy of Input Tree   
   TBranch *b_isTraining            = outputTree->Branch("isTraining",&isTraining,"isTraining/I");
   TBranch *b_xsecEff               = outputTree->Branch("xsecEff",&xsecEff,"xsecEff/F");
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

   TBranch *b_firstcsvb_bb          = outputTree->Branch("firstcsvb_bb",&firstcsvb_bb,"firstcsvb_bb");        
   TBranch *b_secondcsvb_bb         = outputTree->Branch("secondcsvb_bb",&secondcsvb_bb,"secondcsvb_bb");        
   TBranch *b_thirdcsvb_bb          = outputTree->Branch("thirdcsvb_bb",&thirdcsvb_bb,"thirdcsvb_bb");        
   TBranch *b_fourthcsvb_bb         = outputTree->Branch("fourthcsvb_bb",&fourthcsvb_bb,"fourthcsvb_bb/F");

   TBranch *b_secondJetPt           = outputTree->Branch("secondJetPt",&secondJetPt,"secondJetPt/F");        
   TBranch *b_fifthJetPt            = outputTree->Branch("fifthJetPt",&fifthJetPt,"fifthJetPt/F");        
   TBranch *b_sixthJetPt            = outputTree->Branch("sixthJetPt",&sixthJetPt,"sixthJetPt/F");

   TBranch *b_csvJet1               = outputTree->Branch("csvJet1",&csvJet1,"csvJet1/F");
   TBranch *b_csvJet2               = outputTree->Branch("csvJet2",&csvJet2,"csvJet2/F");
   TBranch *b_csvJet3               = outputTree->Branch("csvJet3",&csvJet3,"csvJet3/F");
   TBranch *b_csvJet4               = outputTree->Branch("csvJet4",&csvJet4,"csvJet4/F");

   TBranch *b_MHRE                  = outputTree->Branch("MHRE",&MHRE,"MHRE/F");              
   TBranch *b_HTx                   = outputTree->Branch("HTx",&HTx,"HTx/F");                 
   
   TBranch *b_nGD_trijet            = outputTree->Branch("nGD_trijet",&nGD_trijet,"nGD_trijet/F");
   TBranch *b_is_genMissingDaughter    = outputTree->Branch("is_genMissingDaughter",&is_genMissingDaughter,"is_genMissingDaughter/F");
   TBranch *b_is_genFourTopsOnelepton  = outputTree->Branch("is_genFourTopsOnelepton",&is_genFourTopsOnelepton,"is_genFourTopsOnelepton/F");      
   
   TBranch *b_GD_DCSV_jetNotdijet   = outputTree->Branch("GD_DCSV_jetNotdijet",&GD_DCSV_jetNotdijet);
   TBranch *b_BD_DCSV_jetNotdijet   = outputTree->Branch("BD_DCSV_jetNotdijet",&BD_DCSV_jetNotdijet);
   TBranch *b_GD_DR_Tridijet        = outputTree->Branch("GD_DR_Tridijet",&GD_DR_Tridijet);
   TBranch *b_BD_DR_Tridijet        = outputTree->Branch("BD_DR_Tridijet",&BD_DR_Tridijet);      
   TBranch *b_GD_Ttrijet_TopMass    = outputTree->Branch("GD_Ttrijet_TopMass",&GD_Ttrijet_TopMass);
   TBranch *b_BD_Ttrijet_TopMass    = outputTree->Branch("BD_Ttrijet_TopMass",&BD_Ttrijet_TopMass);   
   TBranch *b_GD_Mass_minDR_dijet   = outputTree->Branch("GD_Mass_minDR_dijet",&GD_Mass_minDR_dijet);      
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
   TBranch *b_GD_pTrat              = outputTree->Branch("GD_pTrat",&GD_pTrat);
   TBranch *b_BD_pTrat              = outputTree->Branch("BD_pTrat",&BD_pTrat);
   TBranch *b_GD_DR_Trijet_jetNotdijet       = outputTree->Branch("GD_DR_Trijet_jetNotdijet",&GD_DR_Trijet_jetNotdijet);
   TBranch *b_BD_DR_Trijet_jetNotdijet       = outputTree->Branch("BD_DR_Trijet_jetNotdijet",&BD_DR_Trijet_jetNotdijet);
   TBranch *b_deltaR_lepJetInMinMljet        = outputTree->Branch("deltaR_lepJetInMinMljet",&deltaR_lepJetInMinMljet,"deltaR_lepJetInMinMljet/F");
   TBranch *b_deltaPhi_lepJetInMinMljet      = outputTree->Branch("deltaPhi_lepJetInMinMljet",&deltaPhi_lepJetInMinMljet,"deltaPhi_lepJetInMinMljet/F");
   TBranch *b_deltaR_lepbJetInMinMlb         = outputTree->Branch("deltaR_lepbJetInMinMlb",&deltaR_lepbJetInMinMlb,"deltaR_lepbJetInMinMlb/F");
   TBranch *b_deltaR_lepbJetNotInMinMlb      = outputTree->Branch("deltaR_lepbJetNotInMinMlb",&deltaR_lepbJetNotInMinMlb,"deltaR_lepbJetNotInMinMlb/F");   
   TBranch *b_deltaPhi_lepbJetInMinMlb       = outputTree->Branch("deltaPhi_lepbJetInMinMlb",&deltaPhi_lepbJetInMinMlb,"deltaPhi_lepbJetInMinMlb/F");

   TBranch *b_HT_woBESTjet              = outputTree->Branch("HT_woBESTjet",&HT_woBESTjet,"HT_woBESTjet/F");
   TBranch *b_MT_woBESTjet              = outputTree->Branch("MT_woBESTjet",&MT_woBESTjet,"MT_woBESTjet/F");
   TBranch *b_PT_woBESTjet              = outputTree->Branch("PT_woBESTjet",&PT_woBESTjet,"PT_woBESTjet/F");
   TBranch *b_M_woBESTjet               = outputTree->Branch("M_woBESTjet",&M_woBESTjet,"M_woBESTjet/F");      
   TBranch *b_M_allJet_W                = outputTree->Branch("M_allJet_W",&M_allJet_W,"M_allJet_W/F");      
   TBranch *b_W_PtdM                    = outputTree->Branch("W_PtdM",&W_PtdM,"W_PtdM/F");         
   TBranch *b_ratio_HTdHT4leadjets      = outputTree->Branch("ratio_HTdHT4leadjets",&ratio_HTdHT4leadjets,"ratio_HTdHT4leadjets/F");      
   TBranch *b_pTjet5_6                  = outputTree->Branch("pTjet5_6",&pTjet5_6,"pTjet5_6/F");         
   TBranch *b_pt3HT                     = outputTree->Branch("pt3HT",&pt3HT,"pt3HT/F");         
   TBranch *b_pt4HT                     = outputTree->Branch("pt4HT",&pt4HT,"pt4HT/F");            
   TBranch *b_mean_csv                  = outputTree->Branch("mean_csv",&mean_csv,"mean_csv/F");               

   TBranch *b_pT_3rdcsvJet              = outputTree->Branch("pT_3rdcsvJet",&pT_3rdcsvJet,"pT_3rdcsvJet/F");         
   TBranch *b_pT_4thcsvJet              = outputTree->Branch("pT_4thcsvJet",&pT_4thcsvJet,"pT_4thcsvJet/F");            

   TBranch *b_invM_jet34                = outputTree->Branch("invM_jet34",&invM_jet34,"invM_jet34/F");            
   TBranch *b_invM_jet35                = outputTree->Branch("invM_jet35",&invM_jet35,"invM_jet35/F");            
   TBranch *b_invM_jet36                = outputTree->Branch("invM_jet36",&invM_jet36,"invM_jet36/F");               
   TBranch *b_invM_jet45                = outputTree->Branch("invM_jet45",&invM_jet45,"invM_jet45/F");            
   TBranch *b_invM_jet46                = outputTree->Branch("invM_jet46",&invM_jet46,"invM_jet46/F");            
   TBranch *b_invM_jet56                = outputTree->Branch("invM_jet56",&invM_jet56,"invM_jet56/F");                        

   TBranch *b_Sphericity                = outputTree->Branch("Sphericity",&Sphericity,"Sphericity/F");                        
   TBranch *b_Aplanarity                = outputTree->Branch("Aplanarity",&Aplanarity,"Aplanarity/F");                              

   Long64_t nentries = inputTree->GetEntriesFast();
   Long64_t nbytes = 0, nb = 0;
   TLorentzVector bjet1, bjet2, jet1, jet2, jet3, lep, met, jetTmp, BestTOPjet1, BestTOPjet2, BestTOPjet3, BADTOPjet1, BADTOPjet2, BADTOPjet3, BestGenTop, BestGenTopW1, BestGenTopW2, BestGenTopb;   
   bool bool_TopMassCut = 0;
   int allLeptonicWcount = 0;
   int allMatchingCount = 0;   
             
   for (Long64_t jentry=0; jentry<nentries;jentry++) {
     Long64_t ientry = LoadTree(jentry);
     if (ientry < 0) break;
     nb = inputTree->GetEntry(jentry);   nbytes += nb;
     if (Cut(ientry) != 1) continue;
     if(jentry % 1000 ==0) std::cout<<"Completed "<<jentry<<" out of "<<nentries<<" events"<<std::endl;      

     std::vector<TLorentzVector> GoodRecoJet1;         
     std::vector<TLorentzVector> GoodRecoJet2;         
     std::vector<TLorentzVector> GoodRecoJet3;                   
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
     Sphericity = -1;
     Aplanarity	= -1;  
     int njetscsv = 0;      
     double maxBBdeta = 0;
     double totalJetPt = 0; //this is mainly HT
     double totalJetE  = 0; 
     double HT_4jets = 0; //for ratio of HT(j1,2,3,4)/HT(other jets)     
     double HT_other = 0; //for ratio of HT(j1,2,3,4)/HT(other jets)          
     double npairs = 0;     
     double maxJJJpt = 0;
     double BjetSecondPt = 0;
     int num_GD_trijet = 0;
     int num_BD_trijet = 0;    

//////////////////////////////////////////////////////////////////
// build BB PAIR variables, aveCSVpt, HT_bjets, HT_ratio, HT_2m //
//////////////////////////////////////////////////////////////////

     HT_4jets = theJetPt_JetSubCalc_PtOrdered->at(0)+theJetPt_JetSubCalc_PtOrdered->at(1)+theJetPt_JetSubCalc_PtOrdered->at(2)+theJetPt_JetSubCalc_PtOrdered->at(3);
     for(unsigned int ijet = 4; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
         HT_other += theJetPt_JetSubCalc_PtOrdered->at(ijet);
     }
     if (NJets_JetSubCalc > 4){
         HT_ratio = HT_4jets/HT_other;
         ratio_HTdHT4leadjets = AK4HT/HT_4jets;
     }

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
     deltaR_lepbJetNotInMinMlb = -99;
     deltaPhi_maxBB = 1e9;
     hemiout = -1;
     deltaPhi_METjets.clear();
     min_deltaPhi_METjets = 1e9;
     aveCSV = -1;
     csvJet1 = 0;
     csvJet2 = 0;
     csvJet3 = 0;
     csvJet4 = 0;
     mean_csv = 0;
     pT_3rdcsvJet = 0;
     pT_4thcsvJet = 0;
     W_PtdM = -1;
     pt3HT = -10;
     pt4HT = -10;     
     pTjet5_6 = -10;
     invM_jet34 = -10;
     invM_jet35 = -10;     
     invM_jet36 = -10;          
     invM_jet45 = -10;               
     invM_jet46 = -10;                    
     invM_jet56 = -10;                         
     secondJetPt = -1;
     fifthJetPt = -1;
     sixthJetPt = -1;
     
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
     std::vector<std::pair<TLorentzVector, double>> v_pair_jet_CSV;

     v_pair_jet_CSV.clear();          
     v_trijet.clear();   
     v_BADtrijet.clear();        

     GD_DR_Tridijet.clear();
     BD_DR_Tridijet.clear();

     GD_Mass_minDR_dijet.clear();
     BD_Mass_minDR_dijet.clear();

     GD_Ttrijet_TopMass.clear();
     BD_Ttrijet_TopMass.clear();

     GD_DR_Trijet_jetNotdijet.clear();
     BD_DR_Trijet_jetNotdijet.clear();
     

     unsigned int tmpJetInd = 0;
     TLorentzVector bestJetinWjet;


     for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		if(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941){
		   //changed to > in line above because we want jets that pass the csv cut 
		   njetscsv+=1;
		   totalPtCSV += theJetPt_JetSubCalc_PtOrdered->at(ijet);
		   aveCSVpt += (theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet))*theJetPt_JetSubCalc_PtOrdered->at(ijet);
		}

		if (ijet==1){
            secondJetPt = theJetPt_JetSubCalc_PtOrdered->at(ijet);
        }
		if (ijet==6){        
            fifthJetPt = theJetPt_JetSubCalc_PtOrdered->at(ijet);
        }
        if (ijet==7){
            sixthJetPt = theJetPt_JetSubCalc_PtOrdered->at(ijet);
        }
        		
        TLorentzVector jetTmp, bjetTmp;   		
		jetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));	
        v_pair_jet_CSV.push_back(make_pair(jetTmp, theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet)));        
        
        if((lep + jetTmp).M() < minMleppJet) {
          minMleppJet = fabs((lep + jetTmp).M());
          deltaR_lepJetInMinMljet  = jetTmp.DeltaR(lep);
          deltaPhi_lepJetInMinMljet = jetTmp.DeltaPhi(lep);
        }		
		if(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941){        
          if((lep + jetTmp).M() < tmp_minMleppBjet) {
            tmp_minMleppBjet = fabs((lep + jetTmp).M() );
            deltaR_lepbJetInMinMlb = jetTmp.DeltaR(lep);
            deltaPhi_lepbJetInMinMlb = jetTmp.DeltaPhi(lep);
            tmpJetInd = ijet;
          }        
        }
        bool stop = 0;
        if (tmpJetInd==0){
            bjetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(tmpJetInd),theJetEta_JetSubCalc_PtOrdered->at(tmpJetInd),theJetPhi_JetSubCalc_PtOrdered->at(tmpJetInd),theJetEnergy_JetSubCalc_PtOrdered->at(tmpJetInd)); 
            for(unsigned int ijet = 1; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){        
                if((theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941) && stop == 0 ){
                    stop = 1;
                    bjetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet)); 
                    deltaR_lepbJetNotInMinMlb = bjetTmp.DeltaR(lep);        
                }
            }     
        }
        if (tmpJetInd>0){        
            stop = 0;
            for(unsigned int ijet = 0; ijet < tmpJetInd; ijet++){        
                if((theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941) && stop == 0 ){
                    stop = 1;
                    bjetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet)); 
                    deltaR_lepbJetNotInMinMlb = bjetTmp.DeltaR(lep);        
                }
            }
            if (stop == 0){
                for(unsigned int ijet = tmpJetInd+1; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){        
                    if((theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941) && stop == 0 ){
                        stop = 1;
                        bjetTmp.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet)); 
                        deltaR_lepbJetNotInMinMlb = bjetTmp.DeltaR(lep);        
                    }
                }                
            }
        }     

	    v_allJets.push_back(jetTmp);
        v_DCSV_allJets.push_back(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet));
	    csvJet1 = theJetDeepCSVb_JetSubCalc_PtOrdered->at(0)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(0);
	    csvJet2 = theJetDeepCSVb_JetSubCalc_PtOrdered->at(1)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(1);
	    csvJet3 = theJetDeepCSVb_JetSubCalc_PtOrdered->at(2)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(2);
	    csvJet4 = theJetDeepCSVb_JetSubCalc_PtOrdered->at(3)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(3);	    
        	    
		totalJetPt+=theJetPt_JetSubCalc_PtOrdered->at(ijet);
		totalJetE+=theJetEnergy_JetSubCalc_PtOrdered->at(ijet);
		deltaPhifromMET_ = TVector2::Phi_mpi_pi(theJetPhi_JetSubCalc_PtOrdered->at(ijet) - corr_met_phi_singleLepCalc);
		deltaPhi_METjets.push_back(deltaPhifromMET_);
		if(min_deltaPhi_METjets>fabs(deltaPhifromMET_)){min_deltaPhi_METjets=fabs(deltaPhifromMET_);}
		if(abs(deltaPhifromMET_)>TMath::Pi()/2){hemiout+=theJetPt_JetSubCalc_PtOrdered->at(ijet);}				
		
		if(!(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs
		
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
		  if(!(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs	  
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

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////HT without the best jet where best jet is the one used in leptonic top reconstruction//////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
      bestJetinWjet = bestJet( corr_met_phi_singleLepCalc, corr_met_singleLepCalc, lepM, lep, 
                               theJetPt_JetSubCalc_PtOrdered, theJetEta_JetSubCalc_PtOrdered, theJetPhi_JetSubCalc_PtOrdered, theJetEnergy_JetSubCalc_PtOrdered);
      TLorentzVector totalJetVectSum;

      HT_woBESTjet = -100;
      MT_woBESTjet = -100;
      PT_woBESTjet = -100;
      M_woBESTjet = -100;
      M_allJet_W = -100;
      for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
         totalJetVectSum += v_allJets[njet];
      }
      M_allJet_W = (totalJetVectSum + Wlv).M();
      HT_woBESTjet = AK4HT - bestJetinWjet.Pt();
      MT_woBESTjet = (totalJetVectSum-bestJetinWjet).Mt();
      PT_woBESTjet = (totalJetVectSum-bestJetinWjet).Pt();
      M_woBESTjet = (totalJetVectSum-bestJetinWjet).M();      


////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////// trijet selection ///////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
     bool mom_W = false;
     bool WfromTop = false;
     bool WnotFromTop = false;
     if (isElectron==1){
        for(int ind = 0; ind < elNumberOfMothers_singleLepCalc->at(0); ind++){
            if(abs(elMother_id_singleLepCalc->at(ind))==24) {mom_W=true;}
            if(abs(elMother_id_singleLepCalc->at(ind))==6 && mom_W) {WfromTop=true;}            
        }
	 }  

     if (isMuon==1){
        for(int ind = 0; ind < muNumberOfMothers_singleLepCalc->at(0); ind++){
            if(abs(muMother_id_singleLepCalc->at(ind))==24) {mom_W=true;}
            if(abs(muMother_id_singleLepCalc->at(ind))==6 && mom_W) {WfromTop=true;}            
        }
	 }

     std::string bitmask(3,1);
     bitmask.resize(v_allJets.size(),0);
     double tempTtrijetMass = 0;
     double Mag_Trijet = 1e9;         
     double ScalarSumpT_Trijet = 1e9;
     double DCSV_BestTOPjet1 = 0;
     double DCSV_BestTOPjet2 = 0;
     double DCSV_BestTOPjet3 = 0;  
     double trijetVectSumPt = 0;  
     GD_DCSV_jetNotdijet.clear();
     GD_pTrat.clear();
     nGD_trijet = -10;             
    TLorentzVector genLepton;
    int genLeptonCounter=0;

    is_genMissingDaughter = false;
    is_genFourTopsOnelepton = false;
    
    std::vector<TLorentzVector> genTops;
    std::vector<double> v_minDR_GenRecoTop;
        
    if(topPt_TTbarMassCalc->size()*2 != topWPt_TTbarMassCalc->size()){
        is_genMissingDaughter = true;
    }

    int genleptonCount = 0;
    for(unsigned int nTop = 0; nTop < (topWID_TTbarMassCalc->size()); nTop++){
        if(abs(topWID_TTbarMassCalc->at(nTop)) == 11 || abs(topWID_TTbarMassCalc->at(nTop)) == 13 || abs(topWID_TTbarMassCalc->at(nTop)) == 15){ 
            genleptonCount++;
        }
    }
    int num_genJets_passCuts = 0;
    TLorentzVector tempGenWd1, tempGenWd2;    
    TLorentzVector tempGenb;
    
    if (topPt_TTbarMassCalc->size() == 4 && genleptonCount == 1 && !is_genMissingDaughter){
        allLeptonicWcount++;
        is_genFourTopsOnelepton = true;
        for(unsigned int nTop = 0; nTop < topPt_TTbarMassCalc->size(); nTop++){
            if(abs(topWID_TTbarMassCalc->at(nTop*2)) > 6 || abs(topWID_TTbarMassCalc->at(nTop*2+1)) > 6){ 
                continue; 
            }
            tempGenWd1.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2),topWEta_TTbarMassCalc->at(nTop*2),topWPhi_TTbarMassCalc->at(nTop*2),topWEnergy_TTbarMassCalc->at(nTop*2));	
            tempGenWd2.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2+1),topWEta_TTbarMassCalc->at(nTop*2+1),topWPhi_TTbarMassCalc->at(nTop*2+1),topWEnergy_TTbarMassCalc->at(nTop*2+1));	        
            tempGenb.SetPtEtaPhiE(topbPt_TTbarMassCalc->at(nTop),topbEta_TTbarMassCalc->at(nTop),topbPhi_TTbarMassCalc->at(nTop),topbEnergy_TTbarMassCalc->at(nTop));
            if((tempGenWd1.Pt()>30 && tempGenWd2.Pt()>30 && tempGenb.Pt()>30) && (tempGenWd1.Eta()<2.4 && tempGenWd2.Eta()<2.4 && tempGenb.Eta()<2.4)){num_genJets_passCuts++;}
        }        
    }
    
    if (!is_genMissingDaughter && is_genFourTopsOnelepton && num_genJets_passCuts>0 && (WfromTop)){
        TLorentzVector tempGenTop;
        TLorentzVector tempGenTopWd1, tempGenTopWd2;    
        TLorentzVector tempGenTopb;

        int idx_minDR = -10;
        std::vector<double> v_deltalR;        
        std::vector<TLorentzVector> v_GD_Trijets;                    
        std::vector<TLorentzVector> v_GD_jets;                        
        std::vector<double> v_GD_DCSV_jets;                            

        std::vector<TLorentzVector> v_BD_Trijets;                    
        std::vector<TLorentzVector> v_BD_jets;                        
        std::vector<double> v_BD_DCSV_jets;                            
        
        Trijet(
            v_trijet, 
            v_DCSV_trijet, 
            v_allJets, 
            v_DCSV_allJets,

            v_GD_Trijets,                    
            v_GD_jets,                     
            v_GD_DCSV_jets,                          

            v_BD_Trijets,                   
            v_BD_jets,                       
            v_BD_DCSV_jets,                            

            topPt_TTbarMassCalc,

            topWID_TTbarMassCalc,
            topWPt_TTbarMassCalc,
            topWEta_TTbarMassCalc,
            topWPhi_TTbarMassCalc,
            topWEnergy_TTbarMassCalc,

            topbPt_TTbarMassCalc,
            topbEta_TTbarMassCalc,
            topbPhi_TTbarMassCalc,
            topbEnergy_TTbarMassCalc, 
            num_GD_trijet,
            num_BD_trijet
        );  

        nGD_trijet = num_GD_trijet;

        double tempMinDR = 10000;
        int tempBestTrijetIdx = -10;
        if(v_GD_Trijets.size()>0){
            for(unsigned int idx = 0; idx<v_GD_Trijets.size(); idx++){
                for(unsigned int nTop = 0; nTop < topPt_TTbarMassCalc->size(); nTop++){
                    if(abs(topWID_TTbarMassCalc->at(nTop*2)) > 6 || abs(topWID_TTbarMassCalc->at(nTop*2+1)) > 6){
                        continue; 
                    }
                    tempGenTop.SetPtEtaPhiE(topPt_TTbarMassCalc->at(nTop),topEta_TTbarMassCalc->at(nTop),topPhi_TTbarMassCalc->at(nTop),topEnergy_TTbarMassCalc->at(nTop));
                    if(v_GD_Trijets[idx].DeltaR(tempGenTop)<tempMinDR){
                        tempMinDR = v_GD_Trijets[idx].DeltaR(tempGenTop);
                        tempBestTrijetIdx = idx;
                    }
                }
            }
            if(num_genJets_passCuts == 2 and v_GD_Trijets.size()==1){
                TLorentzVector testGenWd1, testGenWd2;
                TLorentzVector testGenb;                
                for(unsigned int nTop = 0; nTop < topPt_TTbarMassCalc->size(); nTop++){
                    if(abs(topWID_TTbarMassCalc->at(nTop*2)) > 6 || abs(topWID_TTbarMassCalc->at(nTop*2+1)) > 6){ 
                        continue; 
                    }
                    testGenWd1.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2),topWEta_TTbarMassCalc->at(nTop*2),topWPhi_TTbarMassCalc->at(nTop*2),topWEnergy_TTbarMassCalc->at(nTop*2));	
                    testGenWd2.SetPtEtaPhiE(topWPt_TTbarMassCalc->at(nTop*2+1),topWEta_TTbarMassCalc->at(nTop*2+1),topWPhi_TTbarMassCalc->at(nTop*2+1),topWEnergy_TTbarMassCalc->at(nTop*2+1));	        
                    testGenb.SetPtEtaPhiE(topbPt_TTbarMassCalc->at(nTop),topbEta_TTbarMassCalc->at(nTop),topbPhi_TTbarMassCalc->at(nTop),topbEnergy_TTbarMassCalc->at(nTop));
                }
            }
            BestTOPjet1 = v_GD_jets[tempBestTrijetIdx*3];
            BestTOPjet2 = v_GD_jets[tempBestTrijetIdx*3+1];
            BestTOPjet3 = v_GD_jets[tempBestTrijetIdx*3+2];
            DCSV_BestTOPjet1= v_GD_DCSV_jets[tempBestTrijetIdx*3];
            DCSV_BestTOPjet2= v_GD_DCSV_jets[tempBestTrijetIdx*3+1];
            DCSV_BestTOPjet3= v_GD_DCSV_jets[tempBestTrijetIdx*3+2];
        
            Mag_Trijet = (BestTOPjet1+BestTOPjet2+BestTOPjet3).Mag();
            trijetVectSumPt = TMath::Sqrt(pow((BestTOPjet1+BestTOPjet2+BestTOPjet3).Px(),2)+pow((BestTOPjet1+BestTOPjet2+BestTOPjet3).Py(),2));
            ScalarSumpT_Trijet = (BestTOPjet1.Pt()+BestTOPjet2.Pt()+BestTOPjet3.Pt());  
            GD_pTrat.push_back(trijetVectSumPt/ScalarSumpT_Trijet);                                            
            GD_Ttrijet_TopMass.push_back((BestTOPjet1+BestTOPjet2+BestTOPjet3).M());
            double v_dr[3];
            TLorentzVector dijet, jetNotdijet;     
            v_dr[0] = BestTOPjet1.DeltaR(BestTOPjet2);
            v_dr[1] = BestTOPjet1.DeltaR(BestTOPjet3);
            v_dr[2] = BestTOPjet2.DeltaR(BestTOPjet3); 
            int idx_minDR_jetCombo = std::min_element(v_dr, v_dr+3) - v_dr;
            if(idx_minDR_jetCombo==0){
             dijet = BestTOPjet1+BestTOPjet2;
             jetNotdijet = BestTOPjet3;
             GD_DCSV_jetNotdijet.push_back(DCSV_BestTOPjet3);
            }
            else if (idx_minDR_jetCombo==1){                                     
             dijet = BestTOPjet1+BestTOPjet3;
             jetNotdijet = BestTOPjet2;
             GD_DCSV_jetNotdijet.push_back(DCSV_BestTOPjet2);         
            }
            else if (idx_minDR_jetCombo==2){
             dijet = BestTOPjet2+BestTOPjet3;     
             jetNotdijet = BestTOPjet1;
             GD_DCSV_jetNotdijet.push_back(DCSV_BestTOPjet1);         
            }
            GD_Mass_minDR_dijet.push_back(dijet.M());
            GD_DR_Tridijet.push_back((BestTOPjet1+BestTOPjet2+BestTOPjet3).DeltaR(dijet));
            GD_DR_Trijet_jetNotdijet.push_back((BestTOPjet1+BestTOPjet2+BestTOPjet3).DeltaR(jetNotdijet));
            TLorentzVector totalSumJetVect, totalSumJetVect_noTrijet;
            for(unsigned int njet = 0; njet < v_allJets.size(); ++njet){
            totalSumJetVect += v_allJets[njet];
            }
            totalSumJetVect_noTrijet = totalSumJetVect-BestTOPjet1-BestTOPjet2-BestTOPjet3;
            MHRE = totalSumJetVect_noTrijet.M();
            HTx = AK4HT-BestTOPjet1.Pt()-BestTOPjet2.Pt()-BestTOPjet3.Pt();
        }
        else{
            GD_pTrat.clear();
            GD_Ttrijet_TopMass.clear();
            GD_DCSV_jetNotdijet.clear();
            GD_Mass_minDR_dijet.clear();           
            GD_DR_Tridijet.clear();
            GD_DR_Trijet_jetNotdijet.clear();
            MHRE = -10;
            HTx = -10;            
        }
        double DCSV_BADTOPjet1=0;
        double DCSV_BADTOPjet2=0;
        double DCSV_BADTOPjet3=0;
        trijetVectSumPt = 0;     
        BD_pTrat.clear();
        BD_DCSV_jetNotdijet.clear();
        for (unsigned int idx = 0; idx < v_BD_Trijets.size(); idx++){
            BADTOPjet1     = v_BD_jets[idx*3];
            BADTOPjet2     = v_BD_jets[idx*3+1];                
            BADTOPjet3     = v_BD_jets[idx*3+2];                            
            DCSV_BADTOPjet1     = v_BD_DCSV_jets[idx*3];
            DCSV_BADTOPjet2     = v_BD_DCSV_jets[idx*3+1];                
            DCSV_BADTOPjet3     = v_BD_DCSV_jets[idx*3+2];     
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
            trijetVectSumPt = TMath::Sqrt(pow((BADTOPjet1+BADTOPjet2+BADTOPjet3).Px(),2)+pow((BADTOPjet1+BADTOPjet2+BADTOPjet3).Py(),2));
            ScalarSumpT_Trijet = (BADTOPjet1.Pt()+BADTOPjet2.Pt()+BADTOPjet3.Pt());
            BD_pTrat.push_back(trijetVectSumPt/ScalarSumpT_Trijet);
            BD_DR_Tridijet.push_back((BADTOPjet1+BADTOPjet2+BADTOPjet3).DeltaR(BAD_dijet));                                                                            
            BD_DR_Trijet_jetNotdijet.push_back((BADTOPjet1+BADTOPjet2+BADTOPjet3).DeltaR(jetNotdijet));
        }
    }
    else{
        GD_pTrat.clear();
        GD_Ttrijet_TopMass.clear();
        GD_DCSV_jetNotdijet.clear();
        GD_Mass_minDR_dijet.clear();           
        GD_DR_Tridijet.clear();
        GD_DR_Trijet_jetNotdijet.clear();    
        num_GD_trijet = -10;
        num_BD_trijet = -10;            
        MHRE = -10;
        HTx = -10;            
    }
    

//////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////
     std::sort(v_DCSV_allJets.rbegin(), v_DCSV_allJets.rend());
     
     firstcsvb_bb = v_DCSV_allJets.at(0);
     secondcsvb_bb = v_DCSV_allJets.at(1);
     thirdcsvb_bb = v_DCSV_allJets.at(2);
     fourthcsvb_bb = v_DCSV_allJets.at(3);
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

      if(totalJetE!=0) {
        centrality = totalJetPt/totalJetE;
        
      }	  
      double diff_temppairmass = 1e9;
      TLorentzVector jet1_W, jet2_W;
      // FIND LIGHT PAIRS
	  for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
		if((theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs

		jet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(ijet),theJetEta_JetSubCalc_PtOrdered->at(ijet),theJetPhi_JetSubCalc_PtOrdered->at(ijet),theJetEnergy_JetSubCalc_PtOrdered->at(ijet));

		for(unsigned int jjet = ijet + 1; jjet < theJetPt_JetSubCalc_PtOrdered->size(); jjet++){
		  if(jjet >= theJetPt_JetSubCalc_PtOrdered->size()) continue;
		  if((theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941)) continue; //without b-tag SFs
	  
		  jet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(jjet),theJetEta_JetSubCalc_PtOrdered->at(jjet),theJetPhi_JetSubCalc_PtOrdered->at(jjet),theJetEnergy_JetSubCalc_PtOrdered->at(jjet));

		  double pairdr = (jet1).DeltaR(jet2);
		  double pairmass = (jet1+jet2).M();
		  double pairmasslep = (lep+jet1+jet2).M();
		  if(pairdr < minLLdr){
			minLLdr = pairdr;
			mass_minLLdr = pairmass;
			mass_lepJJ_minJJdr = pairmasslep;
		  }
		  if(fabs(pairmass-MW)<diff_temppairmass){
			diff_temppairmass = pairmass;
			jet1_W = jet1;
			jet2_W = jet2;			
		  }
		}
	  }
	  W_PtdM = (jet1_W+jet2_W).Pt()/(jet1_W+jet2_W).M();

      sort(v_pair_jet_CSV.begin(), v_pair_jet_CSV.end(), compareFunc);  
      invM_jet34 = (v_pair_jet_CSV[2].first+v_pair_jet_CSV[3].first).M();
      pT_3rdcsvJet = v_pair_jet_CSV[2].first.Pt();
      pT_4thcsvJet = v_pair_jet_CSV[3].first.Pt();
      
      double totalCSV = 0;
      for (unsigned int ind = 0; ind < v_pair_jet_CSV.size(); ind++){
        if (v_pair_jet_CSV[ind].second>0){
          totalCSV += v_pair_jet_CSV[ind].second;
        }
      }
      mean_csv = totalCSV/NJets_JetSubCalc;

      if (NJets_JetSubCalc > 5){
          invM_jet35 = (v_pair_jet_CSV[2].first+v_pair_jet_CSV[4].first).M();
          invM_jet45 = (v_pair_jet_CSV[3].first+v_pair_jet_CSV[4].first).M();      
      }
      
      if (NJets_JetSubCalc > 6){
          pTjet5_6 = theJetPt_JetSubCalc_PtOrdered->at(4)+theJetPt_JetSubCalc_PtOrdered->at(5);
          invM_jet36 = (v_pair_jet_CSV[2].first+v_pair_jet_CSV[5].first).M();
          invM_jet46 = (v_pair_jet_CSV[3].first+v_pair_jet_CSV[5].first).M();
          invM_jet56 = (v_pair_jet_CSV[4].first+v_pair_jet_CSV[5].first).M();                                      
      }      
      
	  jet1.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(0),theJetEta_JetSubCalc_PtOrdered->at(0),theJetPhi_JetSubCalc_PtOrdered->at(0),theJetEnergy_JetSubCalc_PtOrdered->at(0));
	  jet2.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(1),theJetEta_JetSubCalc_PtOrdered->at(1),theJetPhi_JetSubCalc_PtOrdered->at(1),theJetEnergy_JetSubCalc_PtOrdered->at(1));
	  jet3.SetPtEtaPhiE(theJetPt_JetSubCalc_PtOrdered->at(2),theJetEta_JetSubCalc_PtOrdered->at(2),theJetPhi_JetSubCalc_PtOrdered->at(2),theJetEnergy_JetSubCalc_PtOrdered->at(2));	  
	  
	  pt3HT = theJetPt_JetSubCalc_PtOrdered->at(2)/AK4HT;
	  pt4HT = theJetPt_JetSubCalc_PtOrdered->at(3)/AK4HT;
	  	  
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
		    if(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) > 0.4941){        
      		fifthJetInd+=1;
      		if(fifthJetInd==5){PtFifthJet=theJetPt_JetSubCalc_PtOrdered->at(ijet);}
      		if(fifthJetInd>=5) break;
      		}
      	}
      if(fifthJetInd<5){
		for(unsigned int ijet = 0; ijet < theJetPt_JetSubCalc_PtOrdered->size(); ijet++){
	    	if(theJetDeepCSVb_JetSubCalc_PtOrdered->at(ijet)+theJetDeepCSVbb_JetSubCalc_PtOrdered->at(ijet) < 0.4941){        
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

//////////////////////////////////////////////////////////////////////////////////
////////////////////////////// Sphericity Aplanarity//////////////////////////////
//////////////////////////////////////////////////////////////////////////////////           
      TMatrixD M_Tensor = SpheAplaTensor(v_allJets);
      TVectorD *_pv = new TVectorD(3);      
      M_Tensor.EigenVectors(*_pv);
	  Sphericity = 1.5 * ( (*_pv)[2] + (*_pv)[1] );
	  Aplanarity = 1.5 * ( (*_pv)[2] );	  
//////////////////////////////////////////////////////////////////////////////////     	  
	  
	  b_isTraining->Fill();
      b_xsecEff->Fill();
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
	  b_firstcsvb_bb->Fill();
	  b_secondcsvb_bb->Fill();
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
      b_csvJet1->Fill();
      b_csvJet2->Fill();
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
	  b_deltaR_lepbJetNotInMinMlb->Fill();
	  b_deltaR_lepJetInMinMljet->Fill();
	  b_deltaPhi_lepJetInMinMljet->Fill();	  
	  b_deltaR_lepbJetInMinMlb->Fill();
	  b_deltaPhi_lepbJetInMinMlb->Fill();	  
	  b_HT_woBESTjet->Fill();	  
	  b_MT_woBESTjet->Fill();	  
	  b_PT_woBESTjet->Fill();	  
	  b_M_woBESTjet->Fill();
	  b_M_allJet_W->Fill();
	  b_ratio_HTdHT4leadjets->Fill();
	  b_W_PtdM->Fill();	 
	  b_pTjet5_6->Fill(); 
      b_mean_csv->Fill();
	  b_invM_jet34->Fill(); 
	  b_invM_jet35->Fill(); 
	  b_invM_jet36->Fill(); 
	  b_invM_jet45->Fill(); 
	  b_invM_jet46->Fill(); 
	  b_invM_jet56->Fill(); 
      b_Sphericity->Fill(); 
      b_Aplanarity->Fill(); 
      b_pT_3rdcsvJet->Fill(); //added 31 March 2019
      b_pT_4thcsvJet->Fill(); //added 31 March 2019
      b_pt3HT->Fill();       // added 31 March 2019
      b_pt4HT->Fill();      // added 31 March 2019
      b_MT2bb->Fill();     // added 31 March 2019
      b_minMleppJet->Fill(); //added 31 March 2019 //this is minimum lep jet mass for any jet, not specifically light
      b_nGD_trijet->Fill();
      b_is_genMissingDaughter->Fill();
      b_is_genFourTopsOnelepton->Fill();      
      b_secondJetPt->Fill(); 
      b_fifthJetPt->Fill(); 
      b_sixthJetPt->Fill(); 
      
     if (ientry > 50000) break;     		  
   }

std::cout<<"DONE "<<nentries<<std::endl;   
outputFile->Write();
delete outputFile;
delete inputFile;
}
