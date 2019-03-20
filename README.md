Documentation for STEP2 and BDT framework

STEP2
1. Step2 for 4 tops analysis to add MVA variables on top of step1 ntuples.
    A. check before run
      * specify which shift you want to run as written in submitstep2.sh
      * specify input/output directory in makeStep2condor.py
  
2. to run step2
    *  cd step2
    *  ./submitstep2.sh


BDT
1. go to TMVA directory
2. python doCondorClassification.py
*specify - number of trees, variable set label to use for training as in varsList.py
3. python TMVAPlotting.py
*specify a path for your training output root file
4. python doCondorApplication.py [SHIFTS]
*specify - path for your training output xml file and step2 root files, path to save BDT weight applied output files, variable set label used for training
                
    