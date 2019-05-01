#!/bin/bash

condorDir=$PWD
theDir=$1
iPlot=$2
region=$3
isCategorized=$4
isEM=$5
nttag=$6
nWtag=$7
nbtag=$8
njets=$9

source /cvmfs/cms.cern.ch/cmsset_default.sh
export SCRAM_ARCH=slc7_amd64_gcc630
cd $theDir
eval `scramv1 runtime -sh`

python doHists.py $condorDir $iPlot $region $isCategorized $isEM $nttag $nWtag $nbtag $njets
