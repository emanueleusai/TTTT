#!/bin/bash

infilename=${1}
outfilename=${2}
inputDir=${3}
outputDir=${4}

macroDir=${PWD}

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc630

scramv1 project CMSSW CMSSW_9_4_6_patch1
cd CMSSW_9_4_6_patch1
eval `scramv1 runtime -sh`
cd -

export PATH=$PATH:$macroDir

root -l -b -q makeStep2.C\(\"$macroDir\",\"$inputDir/$infilename\",\"$outfilename\"\)

cp $outfilename $outputDir/
rm $outfilename
