/**********************************************************************************
 * Project   : TMVA - a Root-integrated toolkit for multivariate data analysis    *
 * Package   : TMVA                                                               *
 * Exectuable: TMVAClassificationApplication                                      *
 *                                                                                *
 * This macro provides a simple example on how to use the trained classifiers     *
 * within an analysis module                                                      *
 **********************************************************************************/

#include <cstdlib>
#include <vector>
#include <iostream>
#include <map>
#include <string>

#include "TFile.h"
#include "TTree.h"
#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include "TStopwatch.h"

#include "TMVA/Tools.h"
#include "TMVA/Reader.h"
#include "TMVA/MethodCuts.h"

using namespace TMVA;

void TMVAClassificationApplication( TString myMethodList = "", TString inputFile="", TString outputFile="" ) 
{   

   //---------------------------------------------------------------

   // This loads the library
   TMVA::Tools::Instance();

   // Default MVA methods to be trained + tested
   std::map<std::string,int> Use;

   // --- Cut optimisation
   Use["Cuts"]            = 1;
   Use["CutsD"]           = 1;
   Use["CutsPCA"]         = 0;
   Use["CutsGA"]          = 0;
   Use["CutsSA"]          = 0;
   // 
   // --- 1-dimensional likelihood ("naive Bayes estimator")
   Use["Likelihood"]      = 1;
   Use["LikelihoodD"]     = 0; // the "D" extension indicates decorrelated input variables (see option strings)
   Use["LikelihoodPCA"]   = 1; // the "PCA" extension indicates PCA-transformed input variables (see option strings)
   Use["LikelihoodKDE"]   = 0;
   Use["LikelihoodMIX"]   = 0;
   //
   // --- Mutidimensional likelihood and Nearest-Neighbour methods
   Use["PDERS"]           = 1;
   Use["PDERSD"]          = 0;
   Use["PDERSPCA"]        = 0;
   Use["PDEFoam"]         = 1;
   Use["PDEFoamBoost"]    = 0; // uses generalised MVA method boosting
   Use["KNN"]             = 1; // k-nearest neighbour method
   //
   // --- Linear Discriminant Analysis
   Use["LD"]              = 1; // Linear Discriminant identical to Fisher
   Use["Fisher"]          = 0;
   Use["FisherG"]         = 0;
   Use["BoostedFisher"]   = 0; // uses generalised MVA method boosting
   Use["HMatrix"]         = 0;
   //
   // --- Function Discriminant analysis
   Use["FDA_GA"]          = 1; // minimisation of user-defined function using Genetics Algorithm
   Use["FDA_SA"]          = 0;
   Use["FDA_MC"]          = 0;
   Use["FDA_MT"]          = 0;
   Use["FDA_GAMT"]        = 0;
   Use["FDA_MCMT"]        = 0;
   //
   // --- Neural Networks (all are feed-forward Multilayer Perceptrons)
   Use["MLP"]             = 0; // Recommended ANN
   Use["MLPBFGS"]         = 0; // Recommended ANN with optional training method
   Use["MLPBNN"]          = 1; // Recommended ANN with BFGS training method and bayesian regulator
   Use["CFMlpANN"]        = 0; // Depreciated ANN from ALEPH
   Use["TMlpANN"]         = 0; // ROOT's own ANN
   Use["DNN_CPU"]         = 0; // ROOT's own ANN
   //
   // --- Support Vector Machine 
   Use["SVM"]             = 1;
   // 
   // --- Boosted Decision Trees
   Use["BDT"]             = 1; // uses Adaptive Boost
   Use["BDTG"]            = 0; // uses Gradient Boost
   Use["BDTB"]            = 0; // uses Bagging
   Use["BDTD"]            = 0; // decorrelation + Adaptive Boost
   // 
   // --- Friedman's RuleFit method, ie, an optimised series of cuts ("rules")
   Use["RuleFit"]         = 1;
   // ---------------------------------------------------------------
   Use["Plugin"]          = 0;
   Use["Category"]        = 0;
   Use["SVM_Gauss"]       = 0;
   Use["SVM_Poly"]        = 0;
   Use["SVM_Lin"]         = 0;

   
   std::cout << std::endl;
   std::cout << "==> Start TMVAClassificationApplication" << std::endl;

   // Select methods (don't look at this code - not of interest)
   if (myMethodList != "") {
      for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) it->second = 0;

      std::vector<TString> mlist = gTools().SplitString( myMethodList, ',' );
      for (UInt_t i=0; i<mlist.size(); i++) {
         std::string regMethod(mlist[i]);

         if (Use.find(regMethod) == Use.end()) {
            std::cout << "Method \"" << regMethod 
                      << "\" not known in TMVA under this name. Choose among the following:" << std::endl;
            for (std::map<std::string,int>::iterator it = Use.begin(); it != Use.end(); it++) {
               std::cout << it->first << " ";
            }
            std::cout << std::endl;
            return;
         }
         Use[regMethod] = 1;
      }
   }

   // --------------------------------------------------------------------------------------------------

   // --- Create the Reader object

   TMVA::Reader *reader = new TMVA::Reader( "!Color:!Silent" );    

   // Create a set of variables and declare them to the reader
   // - the variable names MUST corresponds in name and type to those given in the weight file(s) used
   Float_t var1;
   Float_t var2;
   Float_t var3;
   Float_t var4;
   Float_t var5;
   Float_t var6;
   Float_t var7;
   Float_t var8;
   Float_t var9;
   Float_t var10;
   Float_t var11;
   Float_t var12;
   Float_t var13;
   Float_t var14;
   Float_t var15;
   Float_t var16;
   Float_t var17;
   Float_t var18;
   Float_t var19;
   Float_t var20;
   Float_t var21;
   Float_t var22;
   Float_t var23;
   Float_t var24;
   Float_t varF25;
   Double_t varD25;
   Float_t var26;
   Float_t var27;
   Float_t var28;
   Float_t var29;
   Float_t var30;
   Float_t var31;
   Float_t var32;
   Float_t var33;
   Float_t var34;
   Float_t var35;
   Float_t var36;
   Float_t var37;
   Float_t var38;
   Float_t var39;
   Float_t var40;
   Float_t var41;
   Float_t var42;
   Float_t var43;
   Float_t var44;
   Float_t var45;
   Float_t var46;
   Float_t var47;
   Float_t var48;
   Float_t var49;
   Float_t varF50;
   Int_t varI50;
   Float_t var51;
   Float_t var52;
   Float_t var53;
   Float_t var54;
   Float_t var55;
   Float_t var56;
   Float_t var57;
   Float_t varF58;
   Int_t varI58;
   Float_t varF59;
   Int_t varI59;
   Float_t varF60;
   Int_t varI60;
   Float_t varF61;
   Int_t varI61;
   reader->AddVariable( "AK4HTpMETpLepPt", &var1 );
   reader->AddVariable( "minMleppBjet", &var2 );
   reader->AddVariable( "mass_minBBdr", &var3 );
   reader->AddVariable( "deltaR_lepBJet_maxpt", &var4 );
   reader->AddVariable( "lepDR_minBBdr", &var5 );
   reader->AddVariable( "centrality", &var6 );
   reader->AddVariable( "deltaEta_maxBB", &var7 );
   reader->AddVariable( "aveCSVpt", &var8 );
   reader->AddVariable( "aveBBdr", &var9 );
   reader->AddVariable( "FW_momentum_0", &var10 );
   reader->AddVariable( "FW_momentum_1", &var11 );
   reader->AddVariable( "FW_momentum_2", &var12 );
   reader->AddVariable( "FW_momentum_3", &var13 );
   reader->AddVariable( "FW_momentum_4", &var14 );
   reader->AddVariable( "FW_momentum_5", &var15 );
   reader->AddVariable( "FW_momentum_6", &var16 );
   reader->AddVariable( "mass_maxJJJpt", &var17 );
   reader->AddVariable( "BJetLeadPt", &var18 );
   reader->AddVariable( "deltaR_minBB", &var19 );
   reader->AddVariable( "minDR_lepBJet", &var20 );
   reader->AddVariable( "MT_lepMet", &var21 );
   reader->AddVariable( "AK4HT", &var22 );
   reader->AddVariable( "hemiout", &var23 );
   reader->AddVariable( "theJetLeadPt", &var24 );
   reader->AddVariable( "corr_met_MultiLepCalc", &varF25 );
   reader->AddVariable( "leptonPt_MultiLepCalc", &var26 );
   reader->AddVariable( "mass_lepJets0", &var27 );
   reader->AddVariable( "mass_lepJets1", &var28 );
   reader->AddVariable( "mass_lepJets2", &var29 );
   reader->AddVariable( "MT2bb", &var30 );
   reader->AddVariable( "mass_lepBJet0", &var31 );
   reader->AddVariable( "mass_lepBJet_mindr", &var32 );
   reader->AddVariable( "secondJetPt", &var33 );
   reader->AddVariable( "fifthJetPt", &var34 );
   reader->AddVariable( "sixthJetPt", &var35 );
   reader->AddVariable( "PtFifthJet", &var36 );
   reader->AddVariable( "mass_minLLdr", &var37 );
   reader->AddVariable( "mass_maxBBmass", &var38 );
   reader->AddVariable( "deltaR_lepJetInMinMljet", &var39 );
   reader->AddVariable( "deltaPhi_lepJetInMinMljet", &var40 );
   reader->AddVariable( "deltaR_lepbJetInMinMlb", &var41 );
   reader->AddVariable( "deltaPhi_lepbJetInMinMlb", &var42 );
   reader->AddVariable( "M_allJet_W", &var43 );
   reader->AddVariable( "HT_bjets", &var44 );
   reader->AddVariable( "ratio_HTdHT4leadjets", &var45 );
   reader->AddVariable( "csvJet3", &var46 );
   reader->AddVariable( "csvJet4", &var47 );
   reader->AddVariable( "thirdcsvb_bb", &var48 );
   reader->AddVariable( "fourthcsvb_bb", &var49 );
   reader->AddVariable( "NJets_JetSubCalc", &varF50 );
   reader->AddVariable( "HT_2m", &var51 );
   reader->AddVariable( "Sphericity", &var52 );
   reader->AddVariable( "Aplanarity", &var53 );
   reader->AddVariable( "BDTtrijet1", &var54 );
   reader->AddVariable( "BDTtrijet2", &var55 );
   reader->AddVariable( "BDTtrijet3", &var56 );
   reader->AddVariable( "BDTtrijet4", &var57 );
   reader->AddVariable( "NresolvedTops1pFake", &varF58 );
   reader->AddVariable( "NJetsTtagged", &varF59 );
   reader->AddVariable( "NJetsWtagged", &varF60 );
   reader->AddVariable( "NJetsCSVwithSF_JetSubCalc", &varF61 );

   // --- Book the MVA methods

   // Book method(s)
   reader->BookMVA( "BDT method", "/home/eusai/4t/TTTT/TMVA/dataset2020Feb10/weights/BDT_BigComb_61vars_mDepth2/TMVAClassification_BDT.weights.xml" );

   // Prepare input tree (this must be replaced by your data source)
   // in this example, there is a toy tree with signal and one with background events
   // we'll later on use only the "signal" events for the test in this example.
   //   
   TFile *input(0);
     
   if (!gSystem->AccessPathName( inputFile )){ 
      input = TFile::Open( inputFile ); // check if file in local directory exists 
      } 
   if (!input) {
      std::cout << "ERROR: could not open data file: "<<inputFile << std::endl;
      exit(1);
   }
   std::cout << "--- TMVAClassificationApp    : Using input file: " << input->GetName() << std::endl;
   
   // --- Event loop

   // Prepare the event tree
   // - here the variable names have to corresponds to your tree
   // - you can use the same variables as above which is slightly faster,
   //   but of course you can use different ones and copy the values inside the event loop
   //
   std::cout << "--- Select signal sample" << std::endl;
   TTree* theTree = (TTree*)input->Get("ljmet");
   theTree->SetBranchAddress( "AK4HTpMETpLepPt", &var1 );
   theTree->SetBranchAddress( "minMleppBjet", &var2 );
   theTree->SetBranchAddress( "mass_minBBdr", &var3 );
   theTree->SetBranchAddress( "deltaR_lepBJet_maxpt", &var4 );
   theTree->SetBranchAddress( "lepDR_minBBdr", &var5 );
   theTree->SetBranchAddress( "centrality", &var6 );
   theTree->SetBranchAddress( "deltaEta_maxBB", &var7 );
   theTree->SetBranchAddress( "aveCSVpt", &var8 );
   theTree->SetBranchAddress( "aveBBdr", &var9 );
   theTree->SetBranchAddress( "FW_momentum_0", &var10 );
   theTree->SetBranchAddress( "FW_momentum_1", &var11 );
   theTree->SetBranchAddress( "FW_momentum_2", &var12 );
   theTree->SetBranchAddress( "FW_momentum_3", &var13 );
   theTree->SetBranchAddress( "FW_momentum_4", &var14 );
   theTree->SetBranchAddress( "FW_momentum_5", &var15 );
   theTree->SetBranchAddress( "FW_momentum_6", &var16 );
   theTree->SetBranchAddress( "mass_maxJJJpt", &var17 );
   theTree->SetBranchAddress( "BJetLeadPt", &var18 );
   theTree->SetBranchAddress( "deltaR_minBB", &var19 );
   theTree->SetBranchAddress( "minDR_lepBJet", &var20 );
   theTree->SetBranchAddress( "MT_lepMet", &var21 );
   theTree->SetBranchAddress( "AK4HT", &var22 );
   theTree->SetBranchAddress( "hemiout", &var23 );
   theTree->SetBranchAddress( "theJetLeadPt", &var24 );
   theTree->SetBranchAddress( "corr_met_MultiLepCalc", &varD25 );
   theTree->SetBranchAddress( "leptonPt_MultiLepCalc", &var26 );
   theTree->SetBranchAddress( "mass_lepJets0", &var27 );
   theTree->SetBranchAddress( "mass_lepJets1", &var28 );
   theTree->SetBranchAddress( "mass_lepJets2", &var29 );
   theTree->SetBranchAddress( "MT2bb", &var30 );
   theTree->SetBranchAddress( "mass_lepBJet0", &var31 );
   theTree->SetBranchAddress( "mass_lepBJet_mindr", &var32 );
   theTree->SetBranchAddress( "secondJetPt", &var33 );
   theTree->SetBranchAddress( "fifthJetPt", &var34 );
   theTree->SetBranchAddress( "sixthJetPt", &var35 );
   theTree->SetBranchAddress( "PtFifthJet", &var36 );
   theTree->SetBranchAddress( "mass_minLLdr", &var37 );
   theTree->SetBranchAddress( "mass_maxBBmass", &var38 );
   theTree->SetBranchAddress( "deltaR_lepJetInMinMljet", &var39 );
   theTree->SetBranchAddress( "deltaPhi_lepJetInMinMljet", &var40 );
   theTree->SetBranchAddress( "deltaR_lepbJetInMinMlb", &var41 );
   theTree->SetBranchAddress( "deltaPhi_lepbJetInMinMlb", &var42 );
   theTree->SetBranchAddress( "M_allJet_W", &var43 );
   theTree->SetBranchAddress( "HT_bjets", &var44 );
   theTree->SetBranchAddress( "ratio_HTdHT4leadjets", &var45 );
   theTree->SetBranchAddress( "csvJet3", &var46 );
   theTree->SetBranchAddress( "csvJet4", &var47 );
   theTree->SetBranchAddress( "thirdcsvb_bb", &var48 );
   theTree->SetBranchAddress( "fourthcsvb_bb", &var49 );
   theTree->SetBranchAddress( "NJets_JetSubCalc", &varI50 );
   theTree->SetBranchAddress( "HT_2m", &var51 );
   theTree->SetBranchAddress( "Sphericity", &var52 );
   theTree->SetBranchAddress( "Aplanarity", &var53 );
   theTree->SetBranchAddress( "BDTtrijet1", &var54 );
   theTree->SetBranchAddress( "BDTtrijet2", &var55 );
   theTree->SetBranchAddress( "BDTtrijet3", &var56 );
   theTree->SetBranchAddress( "BDTtrijet4", &var57 );
   theTree->SetBranchAddress( "NresolvedTops1pFake", &varI58 );
   theTree->SetBranchAddress( "NJetsTtagged", &varI59 );
   theTree->SetBranchAddress( "NJetsWtagged", &varI60 );
   theTree->SetBranchAddress( "NJetsCSVwithSF_JetSubCalc", &varI61 );

   TFile *target  = new TFile( outputFile,"RECREATE" );
   target->cd();
   TTree *newTree = theTree->CloneTree(0);   
   Float_t BDT;
   TBranch *b_BDT = newTree->Branch( "BDT", &BDT, "BDT/F" );

   // Efficiency calculator for cut method
   Int_t    nSelCutsGA = 0;
   Double_t effS       = 0.7;

   std::cout << "--- Processing: " << theTree->GetEntries() << " events" << std::endl;
   TStopwatch sw;
   sw.Start();
   for (Long64_t ievt=0; ievt<theTree->GetEntries();ievt++) {

      if (ievt%1000 == 0) std::cout << "--- ... Processing event: " << ievt << std::endl;

      theTree->GetEntry(ievt);

      // --- Return the MVA outputs and fill into histograms

      if (Use["CutsGA"]) {
         // Cuts is a special case: give the desired signal efficienciy
         Bool_t passed = reader->EvaluateMVA( "CutsGA method", effS );
         if (passed) nSelCutsGA++;
      }
      
      varF25=(Float_t)varD25;
      varF50=(Float_t)varI50;
      varF58=(Float_t)varI58;
      varF59=(Float_t)varI59;
      varF60=(Float_t)varI60;
      varF61=(Float_t)varI61;
      BDT = reader->EvaluateMVA( "BDT method" );
      
      newTree->Fill();
   }

   // Get elapsed time
   sw.Stop();
   std::cout << "--- End of event loop: "; sw.Print();

   // Get efficiency for cuts classifier
   if (Use["CutsGA"]) std::cout << "--- Efficiency for CutsGA method: " << double(nSelCutsGA)/theTree->GetEntries()
                                << " (for a required signal efficiency of " << effS << ")" << std::endl;

   if (Use["CutsGA"]) {

      // test: retrieve cuts for particular signal efficiency
      // CINT ignores dynamic_casts so we have to use a cuts-secific Reader function to acces the pointer  
      TMVA::MethodCuts* mcuts = reader->FindCutsMVA( "CutsGA method" ) ;

      if (mcuts) {      
         std::vector<Double_t> cutsMin;
         std::vector<Double_t> cutsMax;
         mcuts->GetCuts( 0.7, cutsMin, cutsMax );
         std::cout << "--- -------------------------------------------------------------" << std::endl;
         std::cout << "--- Retrieve cut values for signal efficiency of 0.7 from Reader" << std::endl;
         for (UInt_t ivar=0; ivar<cutsMin.size(); ivar++) {
            std::cout << "... Cut: " 
                      << cutsMin[ivar] 
                      << " < \"" 
                      << mcuts->GetInputVar(ivar)
                      << "\" <= " 
                      << cutsMax[ivar] << std::endl;
         }
         std::cout << "--- -------------------------------------------------------------" << std::endl;
      }
   }

   // --- Write tree
   newTree->Write();
   target->Close();

   std::cout << "--- Created root file: \"TMVApp.root\" containing the MVA output histograms" << std::endl;
  
   delete reader;
    
   std::cout << "==> TMVAClassificationApplication is done!" << std::endl << std::endl;
} 
