#include "step2.cc"
#include "Davismt2.cc"

void makeStep2(TString macroDir, TString inputFile, TString outputFile){

  gROOT->SetMacroPath(macroDir);

  gSystem->AddIncludePath("-I$CMSSW_BASE/src/");

  TString incl("-I");
  incl+=macroDir;
  gSystem->AddIncludePath(incl);

  step2 t(inputFile,outputFile);
  t.Loop();
}
