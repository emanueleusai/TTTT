//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Fri Feb 22 09:28:38 2019 by ROOT version 6.10/09
// from TTree ljmet/ljmet
// found on file: TTTT_TuneCP5_13TeV-amcatnlo-pythia8_hadd.root
//////////////////////////////////////////////////////////

#ifndef step2_h
#define step2_h

#include <iostream>
#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>

// Header file for the classes stored in the TTree if any.
#include "vector"
#include "TLorentzVector.h"
#include "Davismt2.h"

class step2 {
public :
   //!pointer to the analyzed TTree or TChain
   TTree          *inputTree;   //!pointer to the analyzed TTree or TChain
   TFile          *inputFile, *outputFile;

   Int_t           fCurrent; //!current Tree number in a TChain

// Fixed size dimensions of array or collections stored in the TTree if any.
   Int_t           isTraining;
   Float_t         xsecEff; //this is the weight actually!! so (Lumi * xsec)/nEvents, but keeping the naming the same to be consistent with Jangbae
   // Declaration of leaf types
   Long64_t        event_CommonCalc;
   Int_t           run_CommonCalc;
   Int_t           lumi_CommonCalc;
   Int_t           nPV_singleLepCalc;
   Int_t           nTrueInteractions_singleLepCalc;
   Int_t           isElectron;
   Int_t           isMuon;
   Int_t           MCPastTrigger;
   Int_t           DataPastTrigger;
   Double_t        MCWeight_singleLepCalc;
   vector<double>  *renormWeights;
   vector<double>  *pdfWeights;
   Float_t         pileupWeight;
   Float_t         pileupWeightUp;
   Float_t         pileupWeightDown;
   Float_t         HTSF_Pol;
   Float_t         HTSF_PolUp;
   Float_t         HTSF_PolDn;
   Double_t        ttbarMass_TTbarMassCalc;
   Int_t           isTT_TTbarMassCalc;
   Double_t        corr_met_singleLepCalc;
   Double_t        corr_met_phi_singleLepCalc;
   Float_t         leptonPt_singleLepCalc;
   Float_t         leptonEta_singleLepCalc;
   Float_t         leptonPhi_singleLepCalc;
   Float_t         leptonEnergy_singleLepCalc;
   Float_t         leptonMVAValue_singleLepCalc;
   Float_t         leptonMiniIso_singleLepCalc;

   vector<double>  *genPt_singleLepCalc;   
   vector<double>  *genEta_singleLepCalc;   
   vector<double>  *genPhi_singleLepCalc;   
   vector<double>  *genEnergy_singleLepCalc;            
   vector<double>  *genID_singleLepCalc;
   vector<double>  *genMotherID_singleLepCalc;               
   vector<double>  *genMotherIndex_singleLepCalc;               
   vector<double>  *theJetPt_JetSubCalc_PtOrdered;
   vector<double>  *theJetEta_JetSubCalc_PtOrdered;
   vector<double>  *theJetPhi_JetSubCalc_PtOrdered;
   vector<double>  *theJetEnergy_JetSubCalc_PtOrdered;
   vector<double>  *theJetDeepCSVb_JetSubCalc_PtOrdered;
   vector<double>  *theJetDeepCSVbb_JetSubCalc_PtOrdered;
   vector<double>  *theJetDeepCSVc_JetSubCalc_PtOrdered;
   vector<double>  *theJetDeepCSVudsg_JetSubCalc_PtOrdered;
   vector<int>     *theJetHFlav_JetSubCalc_PtOrdered;
   vector<int>     *theJetPFlav_JetSubCalc_PtOrdered;
   vector<int>     *theJetBTag_JetSubCalc_PtOrdered;
   Float_t         BJetLeadPt;
   Float_t         WJetLeadPt;
   Float_t         TJetLeadPt;
   Float_t         AK4HTpMETpLepPt;
   Float_t         AK4HT;
   Int_t           NJets_JetSubCalc;
   Int_t           NJetsCSV_JetSubCalc;
   Int_t           NJetsCSVwithSF_JetSubCalc;
   Float_t         topPt;
   Float_t         topPtGen;
   Float_t         topMass;
   Float_t         minMleppBjet;
   Float_t         tmp_minMleppBjet;
   Float_t         minMleppJet;
   Float_t         genTopPt;
   Float_t         genAntiTopPt;
   Float_t         topPtWeight13TeV;
   Float_t         minDR_lepJet;
   Float_t         ptRel_lepJet;
   Float_t         MT_lepMet;
   vector<double>  *deltaR_lepJets;
   vector<double>  *deltaR_lepBJets;
   vector<int>     *muIsLoose_singleLepCalc;
   vector<int>     *muIsMedium_singleLepCalc;
   vector<int>     *muIsMediumPrompt_singleLepCalc;
   vector<int>     *muIsTight_singleLepCalc;

   Float_t         elIsTightBarrel_singleLepCalc;
   Float_t         elIsMediumBarrel_singleLepCalc;
   Float_t         elIsLooseBarrel_singleLepCalc;
   Float_t         elIsVetoBarrel_singleLepCalc;
   Float_t         elIsTightEndCap_singleLepCalc;
   Float_t         elIsMediumEndCap_singleLepCalc;
   Float_t         elIsLooseEndCap_singleLepCalc;
   Float_t         elIsVetoEndCap_singleLepCalc;

   vector<double>  *elPt_singleLepCalc;
   vector<int>     *elMother_id_singleLepCalc;
   vector<double>  *elMother_pt_singleLepCalc;
   vector<double>  *elMother_eta_singleLepCalc;
   vector<double>  *elMother_phi_singleLepCalc;
   vector<double>  *elMother_energy_singleLepCalc;
   vector<int>     *elNumberOfMothers_singleLepCalc;   

   vector<double>  *muPt_singleLepCalc;
   vector<int>     *muMother_id_singleLepCalc;
   vector<double>  *muMother_pt_singleLepCalc;
   vector<double>  *muMother_eta_singleLepCalc;
   vector<double>  *muMother_phi_singleLepCalc;
   vector<double>  *muMother_energy_singleLepCalc;
   vector<int>     *muNumberOfMothers_singleLepCalc;   
   
   Float_t         EGammaGsfSF;
   Float_t         lepIdSF;
   vector<int>     *HadronicVHtID_JetSubCalc;
   vector<double>  *HadronicVHtPt_JetSubCalc;
   vector<double>  *HadronicVHtEta_JetSubCalc;
   vector<double>  *HadronicVHtPhi_JetSubCalc;
   vector<double>  *HadronicVHtEnergy_JetSubCalc;
   vector<double>  *theJetAK8Pt_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8Eta_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8Phi_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8Mass_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8Energy_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8SoftDropRaw_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8SoftDropCorr_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8SoftDrop_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered;
   vector<double>  *theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered;
   vector<double>  *theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered;
   vector<double>  *theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered;
   vector<double>  *theJetAK8NjettinessTau1_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8NjettinessTau2_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8NjettinessTau3_JetSubCalc_PtOrdered;
   vector<int>     *theJetAK8Wmatch_JetSubCalc_PtOrdered;
   vector<int>     *theJetAK8Tmatch_JetSubCalc_PtOrdered;
   vector<double>  *theJetAK8MatchedPt_JetSubCalc_PtOrdered;
   Int_t           NJetsAK8_JetSubCalc;
   Int_t           NPuppiWtagged_0p55;
   Int_t           NPuppiWtagged_0p55_notTtagged;
   Int_t           NJetsTtagged_0p81;
   Float_t         minDR_leadAK8otherAK8;
   Float_t         minDR_lepAK8;
   vector<double>  GD_DR_Tridijet;
   vector<double>  BD_DR_Tridijet;   
   vector<double>  GD_Ttrijet_TopMass;
   vector<double>  BD_Ttrijet_TopMass;
   vector<double>  GD_Mass_minDR_dijet;
   vector<double>  BD_Mass_minDR_dijet;
   vector<double>  GD_pTrat;
   vector<double>  BD_pTrat;
   vector<double>  GD_DR_Trijet_jetNotdijet;
   vector<double>  BD_DR_Trijet_jetNotdijet;  
   vector<double>  *deltaR_lepAK8s;
   vector<double>  deltaPhi_METjets;
   Float_t         nGD_trijet;
   Float_t         is_genMissingDaughter;
   Float_t         is_genFourTopsOnelepton;



   vector<double>  *topPt_TTbarMassCalc;
   vector<double>  *topEta_TTbarMassCalc;
   vector<double>  *topPhi_TTbarMassCalc;
   vector<double>  *topEnergy_TTbarMassCalc;         

   vector<double>  *topWID_TTbarMassCalc;
   vector<double>  *topWPt_TTbarMassCalc;
   vector<double>  *topWEta_TTbarMassCalc;
   vector<double>  *topWPhi_TTbarMassCalc;
   vector<double>  *topWEnergy_TTbarMassCalc;

   vector<double>  *topbID_TTbarMassCalc;
   vector<double>  *topbPt_TTbarMassCalc;
   vector<double>  *topbEta_TTbarMassCalc;
   vector<double>  *topbPhi_TTbarMassCalc;
   vector<double>  *topbEnergy_TTbarMassCalc;         

   
   //Additional Variables from the charged higgs analysis
   Float_t         minBBdr;
   Float_t         deltaR_minBB;
   Float_t         aveBBdr;
   Float_t         deltaEta_maxBB; 
   Float_t         FW_momentum_2;
   Float_t         centrality;
   Float_t         aveCSVpt;
   Float_t         mass_maxJJJpt; 
   Float_t         lepDR_minBBdr;
   Float_t         HT_bjets;
   Float_t         HT_ratio;        
   Float_t         HT_2m;
   Float_t         firstcsvb_bb;        
   Float_t         secondcsvb_bb;        
   Float_t         thirdcsvb_bb;        
   Float_t         fourthcsvb_bb;  
   Float_t         PtFifthJet;
   Float_t         deltaR_lepJetInMinMljet;      
   Float_t         deltaPhi_lepJetInMinMljet;         
   Float_t         deltaR_lepbJetInMinMlb;
   Float_t         deltaPhi_lepbJetInMinMlb;
   Float_t         MT2bb; 
   Float_t         pt3HT;
   Float_t         pt4HT;   
   Float_t         pTjet5_6;
   Float_t         invM_jet34;
   Float_t         invM_jet35;   
   Float_t         invM_jet36;
   Float_t         invM_jet45;         
   Float_t         invM_jet46;         
   Float_t         invM_jet56;            
   Float_t         mean_csv;
   Float_t         csvJet1;
   Float_t         csvJet2;
   Float_t         csvJet3;
   Float_t         csvJet4;
   Float_t         pT_3rdcsvJet;
   Float_t         pT_4thcsvJet;      
   Float_t         MHRE;
   Float_t         HTx;
   Float_t         Sphericity;
   Float_t         Aplanarity;
   Float_t         deltaR_lepbJetNotInMinMlb;
   vector<double>  GD_DCSV_jetNotdijet;
   vector<double>  BD_DCSV_jetNotdijet;   
      
   Float_t         mass_minBBdr;   
   Float_t         mass_minLLdr;
   Float_t         mass_maxBBpt;
   Float_t         mass_maxBBmass;
   Float_t         theJetLeadPt;
   Float_t         mass_lepJets0;
   Float_t         mass_lepJets1;
   Float_t         mass_lepJets2;
   Float_t         deltaR_lepBJets0;
   Float_t         deltaR_lepBJets1;   
   Float_t         minDR_lepBJet;
   Float_t         mass_lepBJet0;
   Float_t         mass_lepBB_minBBdr;
   Float_t         mass_lepJJ_minJJdr;
   Float_t         mass_lepBJet_mindr;
   Float_t         deltaR_lepBJet_maxpt;
   Float_t         deltaPhi_maxBB;
   Float_t         hemiout;
   Float_t         corr_met;
   Float_t         deltaPhi_lepMET;
   Float_t         min_deltaPhi_METjets;
   Float_t         aveCSV;
   Float_t         deltaPhi_j1j2;
   Float_t         alphaT;
   Float_t         FW_momentum_0;
   Float_t         FW_momentum_1;
   Float_t         FW_momentum_3;
   Float_t         FW_momentum_4;
   Float_t         FW_momentum_5;
   Float_t         FW_momentum_6;

   Float_t         HT_woBESTjet;
   Float_t         MT_woBESTjet;
   Float_t         PT_woBESTjet;      
   Float_t         M_woBESTjet;            
   Float_t         M_allJet_W;
   Float_t         ratio_HTdHT4leadjets;
   Float_t         W_PtdM;
                   
   // List of branches
   TBranch        *b_event_CommonCalc;   //!
   TBranch        *b_run_CommonCalc;   //!
   TBranch        *b_lumi_CommonCalc;   //!
   TBranch        *b_nPV_singleLepCalc;   //!
   TBranch        *b_nTrueInteractions_singleLepCalc;   //!
   TBranch        *b_isElectron;   //!
   TBranch        *b_isMuon;   //!
   TBranch        *b_MCPastTrigger;   //!
   TBranch        *b_DataPastTrigger;   //!
   TBranch        *b_MCWeight_singleLepCalc;   //!
   TBranch        *b_renormWeights;   //!
   TBranch        *b_pdfWeights;   //!
   TBranch        *b_pileupWeight;   //!
   TBranch        *b_pileupWeightUp;   //!
   TBranch        *b_pileupWeightDown;   //!
   TBranch        *b_HTSF_Pol;   //!
   TBranch        *b_HTSF_PolUp;   //!
   TBranch        *b_HTSF_PolDn;   //!
   TBranch        *b_ttbarMass_TTbarMassCalc;   //!
   TBranch        *b_isTT_TTbarMassCalc;   //!
   TBranch        *b_corr_met_singleLepCalc;   //!
   TBranch        *b_corr_met_phi_singleLepCalc;   //!
   TBranch        *b_leptonPt_singleLepCalc;   //!
   TBranch        *b_leptonEta_singleLepCalc;   //!
   TBranch        *b_leptonPhi_singleLepCalc;   //!
   TBranch        *b_leptonEnergy_singleLepCalc;   //!
   TBranch        *b_leptonMVAValue_singleLepCalc;   //!
   TBranch        *b_leptonMiniIso_singleLepCalc;   //!

   TBranch        *b_genPt_singleLepCalc;   
   TBranch        *b_genEta_singleLepCalc;   
   TBranch        *b_genPhi_singleLepCalc;   
   TBranch        *b_genEnergy_singleLepCalc;            
   TBranch        *b_genID_singleLepCalc;               
   TBranch        *b_genMotherID_singleLepCalc;
   TBranch        *b_genMotherIndex_singleLepCalc;

   TBranch        *b_theJetPt_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetEta_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetPhi_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetEnergy_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetDeepCSVb_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetDeepCSVbb_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetDeepCSVc_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetDeepCSVudsg_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetHFlav_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetPFlav_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetBTag_JetSubCalc_PtOrdered;   //!
   TBranch        *b_BJetLeadPt;   //!
   TBranch        *b_WJetLeadPt;   //!
   TBranch        *b_TJetLeadPt;   //!
   TBranch        *b_AK4HTpMETpLepPt;   //!
   TBranch        *b_AK4HT;   //!
   TBranch        *b_NJets_JetSubCalc;   //!
   TBranch        *b_NJetsCSV_JetSubCalc;   //!
   TBranch        *b_NJetsCSVwithSF_JetSubCalc;   //!
   TBranch        *b_topPt;   //!
   TBranch        *b_topPtGen;   //!
   TBranch        *b_topMass;   //!
   TBranch        *b_minMleppBjet;   //!
   TBranch        *b_mixnMleppJet;   //!
   TBranch        *b_genTopPt;   //!
   TBranch        *b_genAntiTopPt;   //!
   TBranch        *b_topPtWeight13TeV;   //!
   TBranch        *b_minDR_lepJet;   //!
   TBranch        *b_ptRel_lepJet;   //!
   TBranch        *b_MT_lepMet;   //!
   TBranch        *b_deltaR_lepJets;   //!
   TBranch        *b_deltaR_lepBJets;   //!
   TBranch        *b_muIsLoose_singleLepCalc;   //!
   TBranch        *b_muIsMedium_singleLepCalc;   //!
   TBranch        *b_muIsMediumPrompt_singleLepCalc;   //!
   TBranch        *b_muIsTight_singleLepCalc;   //!
   TBranch        *b_elIsTightBarrel_singleLepCalc;   //!
   TBranch        *b_elIsMediumBarrel_singleLepCalc;   //!
   TBranch        *b_elIsLooseBarrel_singleLepCalc;   //!
   TBranch        *b_elIsVetoBarrel_singleLepCalc;   //!
   TBranch        *b_elIsTightEndCap_singleLepCalc;   //!
   TBranch        *b_elIsMediumEndCap_singleLepCalc;   //!
   TBranch        *b_elIsLooseEndCap_singleLepCalc;   //!
   TBranch        *b_elIsVetoEndCap_singleLepCalc;   //!

   TBranch        *b_elPt_singleLepCalc;
   TBranch        *b_elMother_id_singleLepCalc;
   TBranch        *b_elMother_pt_singleLepCalc;
   TBranch        *b_elMother_eta_singleLepCalc;
   TBranch        *b_elMother_phi_singleLepCalc;
   TBranch        *b_elMother_energy_singleLepCalc;
   TBranch        *b_elNumberOfMothers_singleLepCalc;   

   TBranch        *b_muPt_singleLepCalc;
   TBranch        *b_muMother_id_singleLepCalc;
   TBranch        *b_muMother_pt_singleLepCalc;
   TBranch        *b_muMother_eta_singleLepCalc;
   TBranch        *b_muMother_phi_singleLepCalc;
   TBranch        *b_muMother_energy_singleLepCalc;
   TBranch        *b_muNumberOfMothers_singleLepCalc;   

   TBranch        *b_EGammaGsfSF;   //!
   TBranch        *b_lepIdSF;   //!
   TBranch        *b_HadronicVHtID_JetSubCalc;   //!
   TBranch        *b_HadronicVHtPt_JetSubCalc;   //!
   TBranch        *b_HadronicVHtEta_JetSubCalc;   //!
   TBranch        *b_HadronicVHtPhi_JetSubCalc;   //!
   TBranch        *b_HadronicVHtEnergy_JetSubCalc;   //!
   TBranch        *b_theJetAK8Pt_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Eta_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Phi_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Mass_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Energy_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDropRaw_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDropCorr_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDrop_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered;   //!
   TBranch        *b_theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered;   //!
   TBranch        *b_theJetAK8NjettinessTau1_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8NjettinessTau2_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8NjettinessTau3_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Wmatch_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8Tmatch_JetSubCalc_PtOrdered;   //!
   TBranch        *b_theJetAK8MatchedPt_JetSubCalc_PtOrdered;   //!
   TBranch        *b_NJetsAK8_JetSubCalc;   //!
   TBranch        *b_NPuppiWtagged_0p55;   //!
   TBranch        *b_NPuppiWtagged_0p55_notTtagged;   //!
   TBranch        *b_NJetsTtagged_0p81;   //!
   TBranch        *b_minDR_leadAK8otherAK8;   //!
   TBranch        *b_minDR_lepAK8;   //!
   TBranch        *b_deltaR_lepAK8s;   //!

   TBranch        *b_topPt_TTbarMassCalc;
   TBranch        *b_topEta_TTbarMassCalc;
   TBranch        *b_topPhi_TTbarMassCalc;
   TBranch        *b_topEnergy_TTbarMassCalc;         

   TBranch        *b_topWID_TTbarMassCalc;
   TBranch        *b_topWPt_TTbarMassCalc;
   TBranch        *b_topWEta_TTbarMassCalc;
   TBranch        *b_topWPhi_TTbarMassCalc;
   TBranch        *b_topWEnergy_TTbarMassCalc;

   TBranch        *b_topbID_TTbarMassCalc;
   TBranch        *b_topbPt_TTbarMassCalc;
   TBranch        *b_topbEta_TTbarMassCalc;
   TBranch        *b_topbPhi_TTbarMassCalc;
   TBranch        *b_topbEnergy_TTbarMassCalc;         


   step2(TString inputFileName, TString outputFileName);
   virtual ~step2();
   virtual Int_t    Cut(Long64_t entry);
   virtual Int_t    GetEntry(Long64_t entry);
   virtual Long64_t LoadTree(Long64_t entry);
   virtual void     Init(TTree *tree);
   virtual void     Loop();
   virtual Bool_t   Notify();
   virtual void     Show(Long64_t entry = -1);
};

#endif

#ifdef step2_cxx
step2::step2(TString inputFileName, TString outputFileName)// : inputTree(0), inputFile(0), outputFile(0) 
{   //weight branches to be used in the BDT training, xsecEff is the weight

   // TT bkg divided into TTToSemiLep, TTToHadronic, TT high mass appear below

   //TTToSemiLep
   if (inputFileName.Contains("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700")) xsecEff = 0.137784841012;
   else if (inputFileName.Contains("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf")) xsecEff = 0.0309363357165;
   else if (inputFileName.Contains("TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000")) xsecEff = 0.0514566653858;
   
   //TTToHadronic
   else if (inputFileName.Contains("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700")) xsecEff =  0.121490806141;
   else if (inputFileName.Contains("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf")) xsecEff = 0.030031985381;
   else if (inputFileName.Contains("TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000")) xsecEff = 0.0490022856079;
   
   //TTTo2l2nu
   else if (inputFileName.Contains("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700")) xsecEff = 0.0525799344238;
   else if (inputFileName.Contains("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf")) xsecEff = 0.0226832371713;
   else if (inputFileName.Contains("TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000")) xsecEff = 0.0320566270444;
   
   //TT high mass 
   else if (inputFileName.Contains("TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8")) xsecEff = 0.0294081434678;
   else if (inputFileName.Contains("TT_Mtt-700to1000_TuneCP5_13TeV-powheg-pythia8")) xsecEff = 0.0473629131251;
   
   //TTTT signal below
   
   else if (inputFileName.Contains("TTTT_TuneCP5_PSweights_13TeV-amcatnlo-pythia8")) xsecEff = 0.0485879401951;
   
   //For everything else, just have this branch be dummy at the moment, 1 will do nothing
   else xsecEff = 1.0;
      
// if parameter tree is not specified (or zero), connect the file
// used to generate this class and read the Tree.
//    if (tree == 0) {
//       TFile *f = (TFile*)gROOT->GetListOfFiles()->FindObject("TTTT_TuneCP5_13TeV-amcatnlo-pythia8_hadd.root");
//       if (!f || !f->IsOpen()) {
//          f = new TFile("TTTT_TuneCP5_13TeV-amcatnlo-pythia8_hadd.root");
//       }
//       f->GetObject("ljmet",tree);
// 
//    } 

   inputFile=new TFile(inputFileName);
   inputTree = (TTree*)inputFile->Get("ljmet");  
   inputTree->SetBranchStatus("*",1);   
   Init(inputTree);
   outputFile = new TFile(outputFileName,"RECREATE");   
}

step2::~step2()
{
   if (!inputTree) return;
   delete inputTree->GetCurrentFile();
}

Int_t step2::GetEntry(Long64_t entry)
{
// Read contents of entry.
   if (!inputTree) return 0;
   return inputTree->GetEntry(entry);
}
Long64_t step2::LoadTree(Long64_t entry)
{
// Set the environment to read one entry
   if (!inputTree) return -5;
   Long64_t centry = inputTree->LoadTree(entry);
   if (centry < 0) return centry;
   if (inputTree->GetTreeNumber() != fCurrent) {
      fCurrent = inputTree->GetTreeNumber();
      Notify();
   }
   return centry;
}

void step2::Init(TTree *tree)
{
   // The Init() function is called when the selector needs to initialize
   // a new tree or chain. Typically here the branch addresses and branch
   // pointers of the tree will be set.
   // It is normally not necessary to make changes to the generated
   // code, but the routine can be extended by the user if needed.
   // Init() will be called many times when running on PROOF
   // (once per file to be processed).

   // Set object pointer
   renormWeights = 0;
   pdfWeights = 0;
   theJetPt_JetSubCalc_PtOrdered = 0;
   theJetEta_JetSubCalc_PtOrdered = 0;
   theJetPhi_JetSubCalc_PtOrdered = 0;
   theJetEnergy_JetSubCalc_PtOrdered = 0;
   theJetDeepCSVb_JetSubCalc_PtOrdered = 0;
   theJetDeepCSVbb_JetSubCalc_PtOrdered = 0;
   theJetDeepCSVc_JetSubCalc_PtOrdered = 0;
   theJetDeepCSVudsg_JetSubCalc_PtOrdered = 0;
   theJetHFlav_JetSubCalc_PtOrdered = 0;
   theJetPFlav_JetSubCalc_PtOrdered = 0;
   theJetBTag_JetSubCalc_PtOrdered = 0;
   deltaR_lepJets = 0;
   deltaR_lepBJets = 0;
   
   genPt_singleLepCalc = 0;
   genEta_singleLepCalc = 0;
   genPhi_singleLepCalc = 0;
   genEnergy_singleLepCalc = 0;
   genID_singleLepCalc = 0;
   genMotherID_singleLepCalc = 0;                  
   genMotherIndex_singleLepCalc = 0;

   muIsLoose_singleLepCalc = 0;
   muIsMedium_singleLepCalc = 0;
   muIsMediumPrompt_singleLepCalc = 0;
   muIsTight_singleLepCalc = 0;
   
   elPt_singleLepCalc = 0;
   elMother_id_singleLepCalc = 0;
   elMother_pt_singleLepCalc = 0;
   elMother_eta_singleLepCalc = 0;
   elMother_phi_singleLepCalc = 0;
   elMother_energy_singleLepCalc = 0;
   elNumberOfMothers_singleLepCalc = 0;

   muPt_singleLepCalc = 0;
   muMother_id_singleLepCalc = 0;
   muMother_pt_singleLepCalc = 0;
   muMother_eta_singleLepCalc = 0;
   muMother_phi_singleLepCalc = 0;
   muMother_energy_singleLepCalc = 0;
   muNumberOfMothers_singleLepCalc = 0;

   HadronicVHtID_JetSubCalc = 0;
   HadronicVHtPt_JetSubCalc = 0;
   HadronicVHtEta_JetSubCalc = 0;
   HadronicVHtPhi_JetSubCalc = 0;
   HadronicVHtEnergy_JetSubCalc = 0;
   theJetAK8Pt_JetSubCalc_PtOrdered = 0;
   theJetAK8Eta_JetSubCalc_PtOrdered = 0;
   theJetAK8Phi_JetSubCalc_PtOrdered = 0;
   theJetAK8Mass_JetSubCalc_PtOrdered = 0;
   theJetAK8Energy_JetSubCalc_PtOrdered = 0;
   theJetAK8SoftDropRaw_JetSubCalc_PtOrdered = 0;
   theJetAK8SoftDropCorr_JetSubCalc_PtOrdered = 0;
   theJetAK8SoftDrop_JetSubCalc_PtOrdered = 0;
   theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered = 0;
   theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered = 0;
   theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered = 0;
   theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered = 0;
   theJetAK8NjettinessTau1_JetSubCalc_PtOrdered = 0;
   theJetAK8NjettinessTau2_JetSubCalc_PtOrdered = 0;
   theJetAK8NjettinessTau3_JetSubCalc_PtOrdered = 0;
   theJetAK8Wmatch_JetSubCalc_PtOrdered = 0;
   theJetAK8Tmatch_JetSubCalc_PtOrdered = 0;
   theJetAK8MatchedPt_JetSubCalc_PtOrdered = 0;
   deltaR_lepAK8s = 0;

   topPt_TTbarMassCalc = 0;
   topEta_TTbarMassCalc = 0;
   topPhi_TTbarMassCalc = 0;
   topEnergy_TTbarMassCalc = 0;

   topWID_TTbarMassCalc = 0;
   topWPt_TTbarMassCalc = 0;
   topWEta_TTbarMassCalc = 0;
   topWPhi_TTbarMassCalc = 0;
   topWEnergy_TTbarMassCalc = 0;

   topbID_TTbarMassCalc = 0;
   topbPt_TTbarMassCalc = 0;
   topbEta_TTbarMassCalc = 0;
   topbPhi_TTbarMassCalc = 0;
   topbEnergy_TTbarMassCalc = 0;

   // Set branch addresses and branch pointers
   if (!tree) return;
   inputTree = tree;
   fCurrent = -1;
//    inputTree->SetMakeClass(1);

   inputTree->SetBranchAddress("event_CommonCalc", &event_CommonCalc, &b_event_CommonCalc);
   inputTree->SetBranchAddress("run_CommonCalc", &run_CommonCalc, &b_run_CommonCalc);
   inputTree->SetBranchAddress("lumi_CommonCalc", &lumi_CommonCalc, &b_lumi_CommonCalc);
   inputTree->SetBranchAddress("nPV_singleLepCalc", &nPV_singleLepCalc, &b_nPV_singleLepCalc);
   inputTree->SetBranchAddress("nTrueInteractions_singleLepCalc", &nTrueInteractions_singleLepCalc, &b_nTrueInteractions_singleLepCalc);
   inputTree->SetBranchAddress("isElectron", &isElectron, &b_isElectron);
   inputTree->SetBranchAddress("isMuon", &isMuon, &b_isMuon);
   inputTree->SetBranchAddress("MCPastTrigger", &MCPastTrigger, &b_MCPastTrigger);
   inputTree->SetBranchAddress("DataPastTrigger", &DataPastTrigger, &b_DataPastTrigger);
   inputTree->SetBranchAddress("MCWeight_singleLepCalc", &MCWeight_singleLepCalc, &b_MCWeight_singleLepCalc);
   inputTree->SetBranchAddress("renormWeights", &renormWeights, &b_renormWeights);
   inputTree->SetBranchAddress("pdfWeights", &pdfWeights, &b_pdfWeights);
   inputTree->SetBranchAddress("pileupWeight", &pileupWeight, &b_pileupWeight);
   inputTree->SetBranchAddress("pileupWeightUp", &pileupWeightUp, &b_pileupWeightUp);
   inputTree->SetBranchAddress("pileupWeightDown", &pileupWeightDown, &b_pileupWeightDown);
   inputTree->SetBranchAddress("HTSF_Pol", &HTSF_Pol, &b_HTSF_Pol);
   inputTree->SetBranchAddress("HTSF_PolUp", &HTSF_PolUp, &b_HTSF_PolUp);
   inputTree->SetBranchAddress("HTSF_PolDn", &HTSF_PolDn, &b_HTSF_PolDn);
   inputTree->SetBranchAddress("ttbarMass_TTbarMassCalc", &ttbarMass_TTbarMassCalc, &b_ttbarMass_TTbarMassCalc);
   inputTree->SetBranchAddress("isTT_TTbarMassCalc", &isTT_TTbarMassCalc, &b_isTT_TTbarMassCalc);
   inputTree->SetBranchAddress("corr_met_singleLepCalc", &corr_met_singleLepCalc, &b_corr_met_singleLepCalc);
   inputTree->SetBranchAddress("corr_met_phi_singleLepCalc", &corr_met_phi_singleLepCalc, &b_corr_met_phi_singleLepCalc);
   inputTree->SetBranchAddress("leptonPt_singleLepCalc", &leptonPt_singleLepCalc, &b_leptonPt_singleLepCalc);
   inputTree->SetBranchAddress("leptonEta_singleLepCalc", &leptonEta_singleLepCalc, &b_leptonEta_singleLepCalc);
   inputTree->SetBranchAddress("leptonPhi_singleLepCalc", &leptonPhi_singleLepCalc, &b_leptonPhi_singleLepCalc);
   inputTree->SetBranchAddress("leptonEnergy_singleLepCalc", &leptonEnergy_singleLepCalc, &b_leptonEnergy_singleLepCalc);
   inputTree->SetBranchAddress("leptonMVAValue_singleLepCalc", &leptonMVAValue_singleLepCalc, &b_leptonMVAValue_singleLepCalc);
   inputTree->SetBranchAddress("leptonMiniIso_singleLepCalc", &leptonMiniIso_singleLepCalc, &b_leptonMiniIso_singleLepCalc);

   inputTree->SetBranchAddress("genPt_singleLepCalc", &genPt_singleLepCalc, &b_genPt_singleLepCalc);
   inputTree->SetBranchAddress("genEta_singleLepCalc", &genEta_singleLepCalc, &b_genEta_singleLepCalc);
   inputTree->SetBranchAddress("genPhi_singleLepCalc", &genPhi_singleLepCalc, &b_genPhi_singleLepCalc);
   inputTree->SetBranchAddress("genEnergy_singleLepCalc", &genEnergy_singleLepCalc, &b_genEnergy_singleLepCalc);
   inputTree->SetBranchAddress("genID_singleLepCalc", &genID_singleLepCalc, &b_genID_singleLepCalc);            
   inputTree->SetBranchAddress("genMotherID_singleLepCalc", &genMotherID_singleLepCalc, &b_genMotherID_singleLepCalc);            
   inputTree->SetBranchAddress("genMotherIndex_singleLepCalc", &genMotherIndex_singleLepCalc, &b_genMotherIndex_singleLepCalc);            

   inputTree->SetBranchAddress("theJetPt_JetSubCalc_PtOrdered", &theJetPt_JetSubCalc_PtOrdered, &b_theJetPt_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetEta_JetSubCalc_PtOrdered", &theJetEta_JetSubCalc_PtOrdered, &b_theJetEta_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetPhi_JetSubCalc_PtOrdered", &theJetPhi_JetSubCalc_PtOrdered, &b_theJetPhi_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetEnergy_JetSubCalc_PtOrdered", &theJetEnergy_JetSubCalc_PtOrdered, &b_theJetEnergy_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetDeepCSVb_JetSubCalc_PtOrdered", &theJetDeepCSVb_JetSubCalc_PtOrdered, &b_theJetDeepCSVb_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetDeepCSVbb_JetSubCalc_PtOrdered", &theJetDeepCSVbb_JetSubCalc_PtOrdered, &b_theJetDeepCSVbb_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetDeepCSVc_JetSubCalc_PtOrdered", &theJetDeepCSVc_JetSubCalc_PtOrdered, &b_theJetDeepCSVc_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetDeepCSVudsg_JetSubCalc_PtOrdered", &theJetDeepCSVudsg_JetSubCalc_PtOrdered, &b_theJetDeepCSVudsg_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetHFlav_JetSubCalc_PtOrdered", &theJetHFlav_JetSubCalc_PtOrdered, &b_theJetHFlav_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetPFlav_JetSubCalc_PtOrdered", &theJetPFlav_JetSubCalc_PtOrdered, &b_theJetPFlav_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetBTag_JetSubCalc_PtOrdered", &theJetBTag_JetSubCalc_PtOrdered, &b_theJetBTag_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("BJetLeadPt", &BJetLeadPt, &b_BJetLeadPt);
   inputTree->SetBranchAddress("WJetLeadPt", &WJetLeadPt, &b_WJetLeadPt);
   inputTree->SetBranchAddress("TJetLeadPt", &TJetLeadPt, &b_TJetLeadPt);
   inputTree->SetBranchAddress("AK4HTpMETpLepPt", &AK4HTpMETpLepPt, &b_AK4HTpMETpLepPt);
   inputTree->SetBranchAddress("AK4HT", &AK4HT, &b_AK4HT);
   inputTree->SetBranchAddress("NJets_JetSubCalc", &NJets_JetSubCalc, &b_NJets_JetSubCalc);
   inputTree->SetBranchAddress("NJetsCSV_JetSubCalc", &NJetsCSV_JetSubCalc, &b_NJetsCSV_JetSubCalc);
   inputTree->SetBranchAddress("NJetsCSVwithSF_JetSubCalc", &NJetsCSVwithSF_JetSubCalc, &b_NJetsCSVwithSF_JetSubCalc);
   inputTree->SetBranchAddress("topPt", &topPt, &b_topPt);
   inputTree->SetBranchAddress("topPtGen", &topPtGen, &b_topPtGen);
   inputTree->SetBranchAddress("topMass", &topMass, &b_topMass);
   inputTree->SetBranchAddress("minMleppBjet", &minMleppBjet, &b_minMleppBjet);
   inputTree->SetBranchAddress("minMleppJet", &minMleppJet, &b_mixnMleppJet);
   inputTree->SetBranchAddress("genTopPt", &genTopPt, &b_genTopPt);
   inputTree->SetBranchAddress("genAntiTopPt", &genAntiTopPt, &b_genAntiTopPt);
   inputTree->SetBranchAddress("topPtWeight13TeV", &topPtWeight13TeV, &b_topPtWeight13TeV);
   inputTree->SetBranchAddress("minDR_lepJet", &minDR_lepJet, &b_minDR_lepJet);
   inputTree->SetBranchAddress("ptRel_lepJet", &ptRel_lepJet, &b_ptRel_lepJet);
   inputTree->SetBranchAddress("MT_lepMet", &MT_lepMet, &b_MT_lepMet);
   inputTree->SetBranchAddress("deltaR_lepJets", &deltaR_lepJets, &b_deltaR_lepJets);
   inputTree->SetBranchAddress("deltaR_lepBJets", &deltaR_lepBJets, &b_deltaR_lepBJets);
   inputTree->SetBranchAddress("muIsLoose_singleLepCalc", &muIsLoose_singleLepCalc, &b_muIsLoose_singleLepCalc);
   inputTree->SetBranchAddress("muIsMedium_singleLepCalc", &muIsMedium_singleLepCalc, &b_muIsMedium_singleLepCalc);
   inputTree->SetBranchAddress("muIsMediumPrompt_singleLepCalc", &muIsMediumPrompt_singleLepCalc, &b_muIsMediumPrompt_singleLepCalc);
   inputTree->SetBranchAddress("muIsTight_singleLepCalc", &muIsTight_singleLepCalc, &b_muIsTight_singleLepCalc);

   inputTree->SetBranchAddress("muPt_singleLepCalc", &muPt_singleLepCalc, &b_muPt_singleLepCalc);   
   inputTree->SetBranchAddress("muMother_id_singleLepCalc", &muMother_id_singleLepCalc, &b_muMother_id_singleLepCalc);
   inputTree->SetBranchAddress("muMother_pt_singleLepCalc", &muMother_pt_singleLepCalc, &b_muMother_pt_singleLepCalc);
   inputTree->SetBranchAddress("muMother_eta_singleLepCalc", &muMother_eta_singleLepCalc, &b_muMother_eta_singleLepCalc);
   inputTree->SetBranchAddress("muMother_phi_singleLepCalc", &muMother_phi_singleLepCalc, &b_muMother_phi_singleLepCalc);
   inputTree->SetBranchAddress("muMother_energy_singleLepCalc", &muMother_energy_singleLepCalc, &b_muMother_energy_singleLepCalc);
   inputTree->SetBranchAddress("muNumberOfMothers_singleLepCalc", &muNumberOfMothers_singleLepCalc, &b_muNumberOfMothers_singleLepCalc);
                  
   inputTree->SetBranchAddress("elIsTightBarrel_singleLepCalc", &elIsTightBarrel_singleLepCalc, &b_elIsTightBarrel_singleLepCalc);
   inputTree->SetBranchAddress("elIsMediumBarrel_singleLepCalc", &elIsMediumBarrel_singleLepCalc, &b_elIsMediumBarrel_singleLepCalc);
   inputTree->SetBranchAddress("elIsLooseBarrel_singleLepCalc", &elIsLooseBarrel_singleLepCalc, &b_elIsLooseBarrel_singleLepCalc);
   inputTree->SetBranchAddress("elIsVetoBarrel_singleLepCalc", &elIsVetoBarrel_singleLepCalc, &b_elIsVetoBarrel_singleLepCalc);
   inputTree->SetBranchAddress("elIsTightEndCap_singleLepCalc", &elIsTightEndCap_singleLepCalc, &b_elIsTightEndCap_singleLepCalc);
   inputTree->SetBranchAddress("elIsMediumEndCap_singleLepCalc", &elIsMediumEndCap_singleLepCalc, &b_elIsMediumEndCap_singleLepCalc);
   inputTree->SetBranchAddress("elIsLooseEndCap_singleLepCalc", &elIsLooseEndCap_singleLepCalc, &b_elIsLooseEndCap_singleLepCalc);
   inputTree->SetBranchAddress("elIsVetoEndCap_singleLepCalc", &elIsVetoEndCap_singleLepCalc, &b_elIsVetoEndCap_singleLepCalc);

   inputTree->SetBranchAddress("elPt_singleLepCalc", &elPt_singleLepCalc, &b_elPt_singleLepCalc);   
   inputTree->SetBranchAddress("elMother_id_singleLepCalc", &elMother_id_singleLepCalc, &b_elMother_id_singleLepCalc);
   inputTree->SetBranchAddress("elMother_pt_singleLepCalc", &elMother_pt_singleLepCalc, &b_elMother_pt_singleLepCalc);
   inputTree->SetBranchAddress("elMother_eta_singleLepCalc", &elMother_eta_singleLepCalc, &b_elMother_eta_singleLepCalc);
   inputTree->SetBranchAddress("elMother_phi_singleLepCalc", &elMother_phi_singleLepCalc, &b_elMother_phi_singleLepCalc);
   inputTree->SetBranchAddress("elMother_energy_singleLepCalc", &elMother_energy_singleLepCalc, &b_elMother_energy_singleLepCalc);
   inputTree->SetBranchAddress("elNumberOfMothers_singleLepCalc", &elNumberOfMothers_singleLepCalc, &b_elNumberOfMothers_singleLepCalc);

   inputTree->SetBranchAddress("EGammaGsfSF", &EGammaGsfSF, &b_EGammaGsfSF);
   inputTree->SetBranchAddress("lepIdSF", &lepIdSF, &b_lepIdSF);
   inputTree->SetBranchAddress("HadronicVHtID_JetSubCalc", &HadronicVHtID_JetSubCalc, &b_HadronicVHtID_JetSubCalc);
   inputTree->SetBranchAddress("HadronicVHtPt_JetSubCalc", &HadronicVHtPt_JetSubCalc, &b_HadronicVHtPt_JetSubCalc);
   inputTree->SetBranchAddress("HadronicVHtEta_JetSubCalc", &HadronicVHtEta_JetSubCalc, &b_HadronicVHtEta_JetSubCalc);
   inputTree->SetBranchAddress("HadronicVHtPhi_JetSubCalc", &HadronicVHtPhi_JetSubCalc, &b_HadronicVHtPhi_JetSubCalc);
   inputTree->SetBranchAddress("HadronicVHtEnergy_JetSubCalc", &HadronicVHtEnergy_JetSubCalc, &b_HadronicVHtEnergy_JetSubCalc);
   inputTree->SetBranchAddress("theJetAK8Pt_JetSubCalc_PtOrdered", &theJetAK8Pt_JetSubCalc_PtOrdered, &b_theJetAK8Pt_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Eta_JetSubCalc_PtOrdered", &theJetAK8Eta_JetSubCalc_PtOrdered, &b_theJetAK8Eta_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Phi_JetSubCalc_PtOrdered", &theJetAK8Phi_JetSubCalc_PtOrdered, &b_theJetAK8Phi_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Mass_JetSubCalc_PtOrdered", &theJetAK8Mass_JetSubCalc_PtOrdered, &b_theJetAK8Mass_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Energy_JetSubCalc_PtOrdered", &theJetAK8Energy_JetSubCalc_PtOrdered, &b_theJetAK8Energy_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDropRaw_JetSubCalc_PtOrdered", &theJetAK8SoftDropRaw_JetSubCalc_PtOrdered, &b_theJetAK8SoftDropRaw_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDropCorr_JetSubCalc_PtOrdered", &theJetAK8SoftDropCorr_JetSubCalc_PtOrdered, &b_theJetAK8SoftDropCorr_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDrop_JetSubCalc_PtOrdered", &theJetAK8SoftDrop_JetSubCalc_PtOrdered, &b_theJetAK8SoftDrop_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered", &theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered, &b_theJetAK8SoftDrop_JetSubCalc_JMRup_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered", &theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered, &b_theJetAK8SoftDrop_JetSubCalc_JMRdn_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered", &theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered, &b_theJetAK8SoftDrop_JetSubCalc_JMSup_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered", &theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered, &b_theJetAK8SoftDrop_JetSubCalc_JMSdn_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8NjettinessTau1_JetSubCalc_PtOrdered", &theJetAK8NjettinessTau1_JetSubCalc_PtOrdered, &b_theJetAK8NjettinessTau1_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8NjettinessTau2_JetSubCalc_PtOrdered", &theJetAK8NjettinessTau2_JetSubCalc_PtOrdered, &b_theJetAK8NjettinessTau2_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8NjettinessTau3_JetSubCalc_PtOrdered", &theJetAK8NjettinessTau3_JetSubCalc_PtOrdered, &b_theJetAK8NjettinessTau3_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Wmatch_JetSubCalc_PtOrdered", &theJetAK8Wmatch_JetSubCalc_PtOrdered, &b_theJetAK8Wmatch_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8Tmatch_JetSubCalc_PtOrdered", &theJetAK8Tmatch_JetSubCalc_PtOrdered, &b_theJetAK8Tmatch_JetSubCalc_PtOrdered);
   inputTree->SetBranchAddress("theJetAK8MatchedPt_JetSubCalc_PtOrdered", &theJetAK8MatchedPt_JetSubCalc_PtOrdered, &b_theJetAK8MatchedPt_JetSubCalc_PtOrdered);
//    inputTree->SetBranchAddress("BJetLeadPt", &BJetLeadPt, &b_BJetLeadPt);
//    inputTree->SetBranchAddress("WJetLeadPt", &WJetLeadPt, &b_WJetLeadPt);
//    inputTree->SetBranchAddress("TJetLeadPt", &TJetLeadPt, &b_TJetLeadPt);
   inputTree->SetBranchAddress("NJetsAK8_JetSubCalc", &NJetsAK8_JetSubCalc, &b_NJetsAK8_JetSubCalc);
   inputTree->SetBranchAddress("NPuppiWtagged_0p55", &NPuppiWtagged_0p55, &b_NPuppiWtagged_0p55);
   inputTree->SetBranchAddress("NPuppiWtagged_0p55_notTtagged", &NPuppiWtagged_0p55_notTtagged, &b_NPuppiWtagged_0p55_notTtagged);
   inputTree->SetBranchAddress("NJetsTtagged_0p81", &NJetsTtagged_0p81, &b_NJetsTtagged_0p81);
   inputTree->SetBranchAddress("minDR_leadAK8otherAK8", &minDR_leadAK8otherAK8, &b_minDR_leadAK8otherAK8);
   inputTree->SetBranchAddress("minDR_lepAK8", &minDR_lepAK8, &b_minDR_lepAK8);
   inputTree->SetBranchAddress("deltaR_lepAK8s", &deltaR_lepAK8s, &b_deltaR_lepAK8s);

   inputTree->SetBranchAddress("topPt_TTbarMassCalc", &topPt_TTbarMassCalc, &b_topPt_TTbarMassCalc);
   inputTree->SetBranchAddress("topEta_TTbarMassCalc", &topEta_TTbarMassCalc, &b_topEta_TTbarMassCalc);
   inputTree->SetBranchAddress("topPhi_TTbarMassCalc", &topPhi_TTbarMassCalc, &b_topPhi_TTbarMassCalc);
   inputTree->SetBranchAddress("topEnergy_TTbarMassCalc", &topEnergy_TTbarMassCalc, &b_topEnergy_TTbarMassCalc);

   inputTree->SetBranchAddress("topWID_TTbarMassCalc", &topWID_TTbarMassCalc, &b_topWID_TTbarMassCalc);
   inputTree->SetBranchAddress("topWPt_TTbarMassCalc", &topWPt_TTbarMassCalc, &b_topWPt_TTbarMassCalc);
   inputTree->SetBranchAddress("topWEta_TTbarMassCalc", &topWEta_TTbarMassCalc, &b_topWEta_TTbarMassCalc);
   inputTree->SetBranchAddress("topWPhi_TTbarMassCalc", &topWPhi_TTbarMassCalc, &b_topWPhi_TTbarMassCalc);
   inputTree->SetBranchAddress("topWEnergy_TTbarMassCalc", &topWEnergy_TTbarMassCalc, &b_topWEnergy_TTbarMassCalc);

   inputTree->SetBranchAddress("topbID_TTbarMassCalc", &topbID_TTbarMassCalc, &b_topbID_TTbarMassCalc);      
   inputTree->SetBranchAddress("topbPt_TTbarMassCalc", &topbPt_TTbarMassCalc, &b_topbPt_TTbarMassCalc);
   inputTree->SetBranchAddress("topbEta_TTbarMassCalc", &topbEta_TTbarMassCalc, &b_topbEta_TTbarMassCalc);
   inputTree->SetBranchAddress("topbPhi_TTbarMassCalc", &topbPhi_TTbarMassCalc, &b_topbPhi_TTbarMassCalc);
   inputTree->SetBranchAddress("topbEnergy_TTbarMassCalc", &topbEnergy_TTbarMassCalc, &b_topbEnergy_TTbarMassCalc);


   Notify();
}

Bool_t step2::Notify()
{
   // The Notify() function is called when a new file is opened. This
   // can be either for a new TTree in a TChain or when when a new TTree
   // is started when using PROOF. It is normally not necessary to make changes
   // to the generated code, but the routine can be extended by the
   // user if needed. The return value is currently not used.

   return kTRUE;
}

void step2::Show(Long64_t entry)
{
// Print contents of entry.
// If entry is not specified, print current entry
   if (!inputTree) return;
   inputTree->Show(entry);
}
Int_t step2::Cut(Long64_t entry)
{
// This function may be called from Loop.
// returns  1 if entry is accepted.
// returns -1 otherwise.
   return 1;
}
#endif // #ifdef step2_cxx
