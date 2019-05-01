#!/usr/bin/env python


import os,sys  # exit
import time   # time accounting
import getopt # command line parser
import numpy as np
import varsList
from os import environ
from ROOT import gSystem, gROOT, gApplication
from ROOT import TMVA, TFile, TTree, TCut, TString
from subprocess import call
from os.path import isfile

from keras.models import Sequential
from keras.layers.core import Dense
from keras.optimizers import Adam

from array import array
# Setup TMVA
TMVA.Tools.Instance()
TMVA.PyMethodBase.PyInitialize()
reader = TMVA.Reader("Color:!Silent")

iFile = str(sys.argv[1])
oFile = str(sys.argv[2])
wFile = str(sys.argv[3])



data = TFile.Open(iFile)

branches = {}

# branches[  "deltaR_minBB"     ] = array('f', [-999])
# branches[  "aveBBdr"          ] = array('f', [-999])
# branches[  "deltaEta_maxBB"   ] = array('f', [-999])
branches[  "AK4HT"            ] = array('f', [-999])
branches[  "centrality"       ] = array('f', [-999])
branches[  "FW_momentum_2"    ] = array('f', [-999])
# branches[  "aveCSVpt"         ] = array('f', [-999])

# branches[  "minMleppBjet"     ] = array('f', [-999])
# branches[  "BJetLeadPt"       ] = array('f', [-999])
# branches[  "mass_maxJJJpt"    ] = array('f', [-999])
# branches[  "lepDR_minBBdr"    ] = array('f', [-999])
# branches[  "corr_met"         ] = array('f', [-999])
# branches[  "MT_lepMet"        ] = array('f', [-999])



# reader.AddVariable(    "deltaR_minBB",   branches[  "deltaR_minBB"    ])
# reader.AddVariable(         "aveBBdr",   branches[  "aveBBdr"         ])
# reader.AddVariable(  "deltaEta_maxBB",   branches[  "deltaEta_maxBB"  ])
reader.AddVariable(           "AK4HT",   branches[  "AK4HT"           ])
reader.AddVariable(      "centrality",   branches[  "centrality"      ])
reader.AddVariable(   "FW_momentum_2",   branches[  "FW_momentum_2"   ])
# reader.AddVariable(        "aveCSVpt",   branches[  "aveCSVpt"        ])
# reader.AddVariable(    "minMleppBjet",   branches[  "minMleppBjet"    ])
# reader.AddVariable(      "BJetLeadPt",   branches[  "BJetLeadPt"      ])
# reader.AddVariable(   "mass_maxJJJpt",   branches[  "mass_maxJJJpt"   ])
# reader.AddVariable(   "lepDR_minBBdr",   branches[  "lepDR_minBBdr"   ])
# reader.AddVariable(        "corr_met",   branches[  "corr_met"        ])
# reader.AddVariable(       "MT_lepMet",   branches[  "MT_lepMet"       ])



# Book methods
reader.BookMVA('PyKeras', TString(wFile))

theTree = data.Get('ljmet')

# theTree.SetBranchAddress(    "deltaR_minBB",   branches[  "deltaR_minBB"    ])
# theTree.SetBranchAddress(         "aveBBdr",   branches[  "aveBBdr"         ])
# theTree.SetBranchAddress(  "deltaEta_maxBB",   branches[  "deltaEta_maxBB"  ])
theTree.SetBranchAddress(           "AK4HT",   branches[  "AK4HT"           ])
theTree.SetBranchAddress(      "centrality",   branches[  "centrality"      ])
theTree.SetBranchAddress(   "FW_momentum_2",   branches[  "FW_momentum_2"   ])
# theTree.SetBranchAddress(        "aveCSVpt",   branches[  "aveCSVpt"        ])

# theTree.SetBranchAddress(    "minMleppBjet",   branches[  "minMleppBjet"    ])
# theTree.SetBranchAddress(      "BJetLeadPt",   branches[  "BJetLeadPt"      ])
# theTree.SetBranchAddress(   "mass_maxJJJpt",   branches[  "mass_maxJJJpt"   ])
# theTree.SetBranchAddress(   "lepDR_minBBdr",   branches[  "lepDR_minBBdr"   ])
# theTree.SetBranchAddress(        "corr_met",   branches[  "corr_met"        ])
# theTree.SetBranchAddress(       "MT_lepMet",   branches[  "MT_lepMet"       ])

target = TFile( oFile, "RECREATE" );
target.cd()
newTree = theTree.CloneTree(0);   
DNN = array('f', [0])
newTree.Branch( "DNN", DNN, "DNN/F" );

for i in range(theTree.GetEntries()):
#     print "i : ", i
    theTree.GetEntry(i)
    DNN[0] = reader.EvaluateMVA('PyKeras')
    newTree.Fill()



newTree.Write()
target.Close()
