#!/usr/bin/python

import os,sys,time,math,datetime,pickle,itertools,getopt
from ROOT import TH1D,gROOT,TFile,TTree
parent = os.path.dirname(os.getcwd())
sys.path.append(parent)
from numpy import linspace
from weights import *
from analyze import *
from samples import *
from utils import *

gROOT.SetBatch(1)
start_time = time.time()

lumiStr = str(targetlumi/1000).replace('.','p') # 1/fb
#step1Dir = '/mnt/hadoop/users/ssagir/LJMet94X_1lepTT_020619_step1hadds/nominal'
#step1Dir = '/isilon/hadoop/store/user/mhadley/TTTT/LJMet94X_1lepTT_022719_step2_saraBDay/nominal' #step2Dir,actually, in this case
#step1Dir = '/isilon/hadoop/store/user/mhadley/TTTT/LJMet94X_1lepTT_030619_step2_20GeVJetPtCut/nominal' #step2Dir actually, in this case
#step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lepTT_032219_step2_30GeV/nominal' #testing 30 GeV sample 2019_3_22
#step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lepTT_032219_step2_20GeV/nominal' #testing 20 GeV sample 2019_3_23
#step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lepTT_032719_step2/nominal' # based on 30 GeV sample that Sinan began with
#step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lepTT_033119_step2/nominal' #updated so that all the branches should be filled
#step1Dir ='/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lep_033119_step1hadds/nominal' #used to test updated singleLepAnalyzer
#step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lep_040319_step2/nominal' #step2Dir, actually, in this case
# step1Dir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lep_040819_step2haddsL1Prefiring/nominal' #Step2Dir with L1 prefiring branches implemented
step1Dir = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/src/step1/nominal'#TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd_step1.root


"""
Note: 
--Each process in step1 (or step2) directories should have the root files hadded! 
--The code will look for <step1Dir>/<process>_hadd.root for nominal trees.
The uncertainty shape shifted files will be taken from <step1Dir>/../<shape>/<process>_hadd.root,
where <shape> is for example "JECUp". hadder.py can be used to prepare input files this way! 
--Each process given in the lists below must have a definition in "samples.py"
--Check the set of cuts in "analyze.py"
"""

bkgList = [
		  #'DY',
# 		  'DYMG',
# 		 'WJetsMG200', 'WJetsMG400','WJetsMG600','WJetsMG800','WJetsMG1200','WJetsMG2500', 
		  'TTJetsHad0'#,'TTJetsHad700','TTJetsHad1000',
# 		  'TTJetsSemiLep0', 'TTJetsSemiLep700','TTJetsSemiLep1000',
# 	 	  'TTJets2L2nu0','TTJets2L2nu700','TTJets2L2nu1000',
# 		  'TTJetsPH700mtt','TTJetsPH1000mtt',
# 		  'Ts','Tt','Tbt','TtW','TbtW', 'Tbs', 'TTH', 'TTZ', 'TTW',
		  #'TTWl','TTZl',
#                   'WW', 'WZ', 'ZZ',
		  #'QCDht100',
# 		  'QCDht200', 
# 		  'QCDht300','QCDht500','QCDht700','QCDht1000','QCDht1500','QCDht2000',
		  ]

ttFlvs = ['_tt2b','_ttbb','_ttb','_ttcc','_ttlf']
dataList = ['DataERRBCDEF','DataMRRBCDEF']

whichSignal = '4T' #HTB, TT, BB, or X53X53
massList = [690]#range(800,1600+1,100)
sigList = [whichSignal+'M'+str(mass) for mass in massList]
if whichSignal=='X53X53': sigList = [whichSignal+'M'+str(mass)+chiral for mass in massList for chiral in ['left','right']]
elif whichSignal=='TT': decays = ['BWBW','THTH','TZTZ','TZBW','THBW','TZTH'] #T' decays
elif whichSignal=='BB': decays = ['TWTW','BHBH','BZBZ','BZTW','BHTW','BZBH'] #B' decays
else: decays = [''] #decays to tWtW 100% of the time

iPlot = 'deltaR_lepJets' #choose a discriminant from plotList below!
if len(sys.argv)>2: iPlot=sys.argv[2]
region = 'PS'
if len(sys.argv)>3: region=sys.argv[3]
isCategorized = 0
if len(sys.argv)>4: isCategorized=int(sys.argv[4])
isotrig = 1
doJetRwt= 0
doAllSys= False
doQ2sys = False
#this list is defunct, and do Q2sys is always dead
q2List  = [#energy scale sample to be processed
	       'TTJetsPHQ2U','TTJetsPHQ2D',
	       ]
runData = True
runBkgs = True
runSigs = True

cutList = {'elPtCut':35,'muPtCut':30,'metCut':60,'mtCut':60,'jet1PtCut':0,'jet2PtCut':0,'jet3PtCut':0, 'AK4HTCut': 300}

cutString  = 'el'+str(int(cutList['elPtCut']))+'mu'+str(int(cutList['muPtCut']))
cutString += '_MET'+str(int(cutList['metCut']))+'_MT'+str(cutList['mtCut'])
cutString += '_1jet'+str(int(cutList['jet1PtCut']))+'_2jet'+str(int(cutList['jet2PtCut']))+str(int(cutList['jet3PtCut']))

cTime=datetime.datetime.now()
datestr='%i_%i_%i'%(cTime.year,cTime.month,cTime.day)
timestr='%i_%i_%i'%(cTime.hour,cTime.minute,cTime.second)
if region=='TTCR': pfix='ttbar_'
elif region=='WJCR': pfix='wjets_'
else: pfix='templates_'
if not isCategorized: pfix='kinematics_'+region+'_'
pfix+=iPlot
pfix+='_TEST_'+datestr#+'_'+timestr
		
if len(sys.argv)>5: isEMlist=[str(sys.argv[5])]
else: isEMlist = ['E','M']
if len(sys.argv)>6: nttaglist=[str(sys.argv[6])]
else: 
	if not isCategorized: nttaglist = ['0p']
	if region=='SR': nttaglist=['0','1p']
	else: nttaglist = ['0p']
if len(sys.argv)>7: nWtaglist=[str(sys.argv[7])]
else: 
	if region=='TTCR': nWtaglist = ['0p']
	else: 
		if not isCategorized: nWtaglist = ['0p']
		else: nWtaglist=['0','1p']
if len(sys.argv)>8: nbtaglist=[str(sys.argv[8])]
else: 
	if region=='WJCR': nbtaglist = ['0']
	else: 
		if not isCategorized: nbtaglist = ['1p'] #was '1p' chaning to '2p' because I want to do a local test of what Freya requetsed before launching condor 28 Feb. 2019 #changed back to '1p' 6 March 2019
		else: nbtaglist=['1','2p']
if len(sys.argv)>9: njetslist=[str(sys.argv[9])]
else: 
	if region=='PS': njetslist=['4p']   #used to be '3p', changing to '4p' to be consistent with the cut sinan made in step 1 15 Feb. 2019 
	else: njetslist=['4p']

def readTree(file):
	if not os.path.exists(file): 
		print "Error: File does not exist! Aborting ...",file
		os._exit(1)
	tFile = TFile(file,'READ')
	tTree = tFile.Get('ljmet')
	return tFile, tTree 

print "READING TREES"
#shapesFiles = ['jec','jer']
shapesFiles = []
#shapesFiles = ['muRFcorrd'] #these don't come from shapes files, things like jec and jer come from shapes files!!
tTreeData = {}
tFileData = {}
for data in dataList:
	if not runData: break
	print "READING:", data
	tFileData[data],tTreeData[data]=readTree(step1Dir+'/'+samples[data]+'_hadd.root')

tTreeSig = {}
tFileSig = {}
for sig in sigList:
	if not runSigs: break
	for decay in decays:
		print "READING:", sig+decay
		print "        nominal"
		tFileSig[sig+decay],tTreeSig[sig+decay]=readTree(step1Dir+'/'+samples[sig+decay]+'_hadd.root')
		if doAllSys:
			for syst in shapesFiles:
				for ud in ['Up','Down']:
					print "        "+syst+ud
					tFileSig[sig+decay+syst+ud],tTreeSig[sig+decay+syst+ud]=readTree(step1Dir.replace('nominal',syst.upper()+ud.lower())+'/'+samples[sig+decay]+'_hadd.root')

tTreeBkg = {}
tFileBkg = {}
for bkg in bkgList+q2List:
	if not runBkgs: break
	if bkg in q2List and not doQ2sys: continue
	print "READING:",bkg
	print "        nominal"
	tFileBkg[bkg],tTreeBkg[bkg]=readTree(step1Dir+'/'+samples[bkg]+'_hadd.root')
	if doAllSys:
		for syst in shapesFiles:
			for ud in ['Up','Down']:
				if bkg in q2List:
					tFileBkg[bkg+syst+ud],tTreeBkg[bkg+syst+ud]=None,None
				else:
					print "        "+syst+ud
					tFileBkg[bkg+syst+ud],tTreeBkg[bkg+syst+ud]=readTree(step1Dir.replace('nominal',syst.upper()+ud.lower())+'/'+samples[bkg]+'_hadd.root')
print "FINISHED READING"

#bigbins = [0,50,100,150,200,250,300,350,400,450,500,600,700,800,1000,1200,1500]
bigbins = [0,50,100,125,150,175,200,225,250,275,300,325,350,375,400,450,500,600,700,800,900,1000,1200,1400,1600,1800,2000,2500,3000,3500,4000,5000]

plotList = {#discriminantName:(discriminantLJMETName, binning, xAxisLabel)
	'deltaRAK8':('minDR_leadAK8otherAK8',linspace(0,5,51).tolist(),';min #DeltaR(1^{st} AK8 jet, other AK8 jet)'),
	'MTlmet':('MT_lepMet',linspace(0,250,51).tolist(),';M_{T}(l,#slash{E}_{T}) [GeV]'),
	'NPV'   :('nPV_singleLepCalc',linspace(0, 60, 61).tolist(),';PV multiplicity'),
	'nTrueInt':('nTrueInteractions_singleLepCalc',linspace(0, 75, 76).tolist(),';# true interactions'),
	'lepPt' :('leptonPt_singleLepCalc',linspace(0, 1000, 51).tolist(),';Lepton p_{T} [GeV]'),
	'lepEta':('leptonEta_singleLepCalc',linspace(-4, 4, 41).tolist(),';Lepton #eta'),
	'JetEta':('theJetEta_JetSubCalc_PtOrdered',linspace(-4, 4, 41).tolist(),';AK4 jet #eta'),
	'JetPt' :('theJetPt_JetSubCalc_PtOrdered',linspace(0, 800, 81).tolist(),';jet p_{T} [GeV]'),
	'Jet1Pt':('theJetPt_JetSubCalc_PtOrdered[0]',linspace(0, 800, 81).tolist(),';p_{T}(j_{1}) [GeV]'),
	'Jet2Pt':('theJetPt_JetSubCalc_PtOrdered[1]',linspace(0, 800, 81).tolist(),';p_{T}(j_{2}) [GeV]'),
	'Jet3Pt':('theJetPt_JetSubCalc_PtOrdered[2]',linspace(0, 800, 81).tolist(),';p_{T}(j_{3}) [GeV]'),
	'Jet4Pt':('theJetPt_JetSubCalc_PtOrdered[3]',linspace(0, 300, 31).tolist(),';p_{T}(j_{4}) [GeV]'),
	'Jet5Pt':('theJetPt_JetSubCalc_PtOrdered[4]',linspace(0, 300, 31).tolist(),';p_{T}(j_{5}) [GeV]'),
	'Jet6Pt':('theJetPt_JetSubCalc_PtOrdered[5]',linspace(0, 300, 31).tolist(),';p_{T}(j_{6}) [GeV]'),
	'JetPtBins' :('theJetPt_JetSubCalc_PtOrdered',linspace(0,2000,21).tolist(),';AK4 jet p_{T} [GeV]'),
	'Jet1PtBins':('theJetPt_JetSubCalc_PtOrdered[0]',linspace(0,2000,21).tolist(),';p_{T}(j_{1}) [GeV]'),
	'Jet2PtBins':('theJetPt_JetSubCalc_PtOrdered[1]',linspace(0,2000,21).tolist(),';p_{T}(j_{2}) [GeV]'),
	'Jet3PtBins':('theJetPt_JetSubCalc_PtOrdered[2]',linspace(0,2000,21).tolist(),';p_{T}(j_{3}) [GeV]'),
	'Jet4PtBins':('theJetPt_JetSubCalc_PtOrdered[3]',linspace(0,2000,21).tolist(),';p_{T}(j_{4}) [GeV]'),
	'Jet5PtBins':('theJetPt_JetSubCalc_PtOrdered[4]',linspace(0,2000,21).tolist(),';p_{T}(j_{5}) [GeV]'),
	'Jet6PtBins':('theJetPt_JetSubCalc_PtOrdered[5]',linspace(0,2000,21).tolist(),';p_{T}(j_{6}) [GeV]'),
	'MET'   :('corr_met_singleLepCalc',linspace(0, 1500, 51).tolist(),';#slash{E}_{T} [GeV]'),
	'NJets' :('NJets_JetSubCalc',linspace(0, 15, 16).tolist(),';AK4 jet multiplicity'),
	'NBJets':('NJetsCSVwithSF_JetSubCalc',linspace(0, 10, 11).tolist(),';b-tagged jet multiplicity'),
	'NBJetsNoSF':('NJetsCSV_JetSubCalc',linspace(0, 10, 11).tolist(),';b-tagged jet multiplicity'),
	'NWJets':('NPuppiWtagged_0p55_notTtagged',linspace(0, 6, 7).tolist(),';W-tagged jet multiplicity'),
	'NTJets':('NJetsTtagged_0p81',linspace(0, 4, 5).tolist(),';t-tagged jet multiplicity'),
	'NJetsAK8':('NJetsAK8_JetSubCalc',linspace(0, 8, 9).tolist(),';AK8 jet multiplicity'),
	'JetPtAK8':('theJetAK8Pt_JetSubCalc_PtOrdered',linspace(0, 1500, 51).tolist(),';AK8 jet p_{T} [GeV]'),
	'JetPtBinsAK8':('theJetAK8Pt_JetSubCalc_PtOrdered',bigbins,';AK8 jet p_{T} [GeV];'),
	'JetEtaAK8':('theJetAK8Eta_JetSubCalc_PtOrdered',linspace(-4, 4, 41).tolist(),';AK8 jet #eta'),
	'Tau21'  :('theJetAK8NjettinessTau2_JetSubCalc_PtOrdered/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered',linspace(0, 1, 51).tolist(),';AK8 jet #tau_{2}/#tau_{1}'),
	'Tau21Nm1'  :('theJetAK8NjettinessTau2_JetSubCalc_PtOrdered/theJetAK8NjettinessTau1_JetSubCalc_PtOrdered',linspace(0, 1, 51).tolist(),';AK8 jet #tau_{2}/#tau_{1}'),
	'Tau32'  :('theJetAK8NjettinessTau3_JetSubCalc_PtOrdered/theJetAK8NjettinessTau2_JetSubCalc_PtOrdered',linspace(0, 1, 51).tolist(),';AK8 jet #tau_{3}/#tau_{2}'),
	'Tau32Nm1'  :('theJetAK8NjettinessTau3_JetSubCalc_PtOrdered/theJetAK8NjettinessTau2_JetSubCalc_PtOrdered',linspace(0, 1, 51).tolist(),';AK8 jet #tau_{3}/#tau_{2}'),
	'Pruned' :('theJetAK8PrunedMass_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet pruned mass [GeV]'),
	'PrunedSmeared' :('theJetAK8PrunedMass_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet pruned mass [GeV]'),
	'PrunedSmearedNm1' :('theJetAK8PrunedMassWtagUncerts_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet pruned mass [GeV]'),
	'SoftDropMass' :('theJetAK8SoftDropCorr_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet soft-drop mass [GeV]'),
	'SoftDropMassNm1W' :('theJetAK8SoftDropCorr_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet soft-drop mass [GeV]'),
	'SoftDropMassNm1t' :('theJetAK8SoftDropCorr_JetSubCalc_PtOrdered',linspace(0, 500, 51).tolist(),';AK8 jet soft-drop mass [GeV]'),
 	'mindeltaR':('minDR_lepJet',linspace(0, 5, 51).tolist(),';#DeltaR(l, closest jet)'),
	'deltaRjet1':('deltaR_lepJets[0]',linspace(0, 5, 51).tolist(),';#DeltaR(l,j_{1})'),
	'deltaRjet2':('deltaR_lepJets[1]',linspace(0, 5, 51).tolist(),';#DeltaR(l,j_{2})'),
	'deltaRjet3':('deltaR_lepJets[2]',linspace(0, 5, 51).tolist(),';#DeltaR(l,j_{3})'),
	'nLepGen':('NLeptonDecays_TpTpCalc',linspace(0,10,11).tolist(),';N lepton decays from TT'),
	'METphi':('corr_met_phi_singleLepCalc',linspace(-3.2,3.2,65).tolist(),';#phi(#slash{E}_{T})'),
	'lepPhi':('leptonPhi_singleLepCalc',linspace(-3.2,3.2,65).tolist(),';#phi(l)'),
	'lepDxy':('leptonDxy_singleLepCalc',linspace(-0.02,0.02,51).tolist(),';lepton xy impact param [cm]'),
	'lepDz':('leptonDz_singleLepCalc',linspace(-0.1,0.1,51).tolist(),';lepton z impact param [cm]'),
	'lepCharge':('leptonCharge_singleLepCalc',linspace(-2,2,5).tolist(),';lepton charge'),
	'lepIso':('leptonMiniIso_singleLepCalc',linspace(0,0.1,51).tolist(),';lepton mini isolation'),
	'Tau1':('theJetAK8NjettinessTau1_JetSubCalc_PtOrdered',linspace(0,1,51).tolist(),';AK8 Jet #tau_{1}'),
	'Tau2':('theJetAK8NjettinessTau2_JetSubCalc_PtOrdered',linspace(0,1,51).tolist(),';AK8 Jet #tau_{2}'),
	'JetPhi':('theJetPhi_JetSubCalc_PtOrdered',linspace(-3.2,3.2,65).tolist(),';AK4 Jet #phi'),
	'JetPhiAK8':('theJetAK8Phi_JetSubCalc_PtOrdered',linspace(-3.2,3.2,65).tolist(),';AK8 Jet #phi'),
	'Bjet1Pt':('BJetLeadPt',linspace(0,1500,51).tolist(),';p_{T}(b_{1}) [GeV]'),  ## B TAG
	'Wjet1Pt':('WJetLeadPt',linspace(0,1500,51).tolist(),';p_{T}(W_{1}) [GeV]'),
	'Tjet1Pt':('TJetLeadPt',linspace(0,1500,51).tolist(),';p_{T}(t_{1}) [GeV]'),
	'topMass':('topMass',linspace(0,1500,51).tolist(),';M^{rec}(t) [GeV]'),
	'topPt':('topPt',linspace(0,1500,51).tolist(),';p_{T}^{rec}(t) [GeV]'),
	'minMlj':('minMleppJet',linspace(0,1000,51).tolist(),';min[M(l,j)] [GeV], j #neq b'),
	'minMljDR':('deltaRlepJetInMinMljet',linspace(0,5,51).tolist(),';#DeltaR(l,j) with min[M(l,j)], j #neq b'),
	'minMljDPhi':('deltaPhilepJetInMinMljet',linspace(0,5,51).tolist(),';#Delta#phi(l,jet) with min[M(l,j)], j #neq b'),
	'minMlbDR':('deltaRlepbJetInMinMlb',linspace(0,5,51).tolist(),';#DeltaR(l,b) with min[M(l,b)]'), ## B TAG
	'minMlbDPhi':('deltaPhilepbJetInMinMlb',linspace(0,5,51).tolist(),';#Delta#phi(l,b) with min[M(l,b)]'), ## B TAG
	'nonMinMlbDR':('deltaRlepbJetNotInMinMlb',linspace(0,5,51).tolist(),';#DeltaR(l,b), b #neq b in min[M(l,b)]'),  ## B TAG
	'MWb1':('M_taggedW_bjet1',linspace(0,1000,51).tolist(),';M(W_{jet},b_{1}) [GeV]'), ## B TAG
	'MWb2':('M_taggedW_bjet2',linspace(0,1000,51).tolist(),';M(W_{jet},b_{2}) [GeV]'), ## 2 B TAG
	'deltaRlb1':('deltaRlepbJet1',linspace(0,5,51).tolist(),';#DeltaR(l,b_{1})'), ## B TAG
	'deltaRlb2':('deltaRlepbJet2',linspace(0,5,51).tolist(),';#DeltaR(l,b_{2})'), ## 2 B TAG
	'deltaRtW':('deltaRtopWjet',linspace(0,5,51).tolist(),';#DeltaR(reco t, W jet)'),
	'deltaRlW':('deltaRlepWjet',linspace(0,5,51).tolist(),';#DeltaR(l,W_{jet})'),
	'deltaRWb1':('deltaRtaggedWbJet1',linspace(0,5,51).tolist(),';#DeltaR(W_{jet},b_{1})'), ## B TAG
	'deltaRWb2':('deltaRtaggedWbJet2',linspace(0,5,51).tolist(),';#DeltaR(W_{jet},b_{2})'), ## 2 B TAG
	'deltaPhilb1':('deltaPhilepbJet1',linspace(0,5,51).tolist(),';#Delta#phi(l,b_{1})'), ## B TAG
	'deltaPhilb2':('deltaPhilepbJet2',linspace(0,5,51).tolist(),';#Delta#phi(l,b_{2})'), ## 2 B TAG
	'deltaPhitW':('deltaPhitopWjet',linspace(0,5,51).tolist(),';#Delta#phi(t_{lep}, W_{jet})'),
	'deltaPhilW':('deltaPhilepWjet',linspace(0,5,51).tolist(),';#Delta#phi(l, W_{jet})'),
	'deltaPhiWb1':('deltaPhitaggedWbJet1',linspace(0,5,51).tolist(),';#Delta#phi(W_{jet},b_{1})'), ## B TAG
	'deltaPhiWb2':('deltaPhitaggedWbJet2',linspace(0,5,51).tolist(),';#Delta#phi(W_{jet},b_{2})'), ## 2 B TAG
	'WjetPt':('WJetTaggedPt',linspace(0,1500,51).tolist(),';p_{T}(W_{jet}) [GeV]'),
 	'PtRel':('ptRel_lepJet',linspace(0,500,51).tolist(),';p_{T,rel}(l, closest jet) [GeV]'),
	'deltaPhiLMET':('deltaPhi_lepMET',linspace(-3.2,3.2,51).tolist(),';#Delta#phi(l,#slash{E}_{T})'),
	
	'NJets_vs_NBJets':('NJets_JetSubCalc:NJetsCSV_JetSubCalc',linspace(0, 15, 16).tolist(),';AK4 jet multiplicity',linspace(0, 10, 11).tolist(),';b-tagged jet multiplicity'),

 	'HT':('AK4HT',linspace(0, 4000, 101).tolist(),';H_{T} [GeV]'),
	'ST':('AK4HTpMETpLepPt',linspace(0, 4000, 101).tolist(),';S_{T} [GeV]'),
# # 	'minMlb':('minMleppBjet',linspace(0, 1000, 51).tolist(),';min[M(l,b)] [GeV]'),
# # 	'HT':('AK4HT',linspace(450, 4000, 711).tolist(),';H_{T} [GeV]'),
# # 	'ST':('AK4HTpMETpLepPt',linspace(650, 4000, 671).tolist(),';S_{T} [GeV]'),
#	'minMlb':('minMleppBjet',linspace(0, 1000, 201).tolist(),';min[M(l,b)] [GeV]'),
	'minMlbSBins':('minMleppBjet',linspace(0, 1000, 1001).tolist(),';min[M(l,b)] [GeV]'),
    'HT_b':('HT_bjets',linspace(0, 4000, 101).tolist(),';H_{T} of b jets [GeV]'),  
    'HT_ratio':('HT_ratio',linspace(0, 40, 41).tolist(),';H_{T} ratio of 4 leading pT jets to other jets'), 
    'HT_2m':('HT_2m',linspace(0, 3000, 101).tolist(),';Event H_{T} - (H_{T} of 2 lead b jets)'),
    'Centrality':('centrality',linspace(0, 1, 21).tolist(),';H_{T}/H'),
     'thirdcsvb_bb':('thirdcsvb_bb',linspace(0, 1, 51).tolist(),'Jet with third-highest DeepCSVb + DeepCSVbb in the evt'),
    'fourthcsvb_bb':('fourthcsvb_bb',linspace(0, 1, 21).tolist(),'Jet with fourth-highest DeepCSVb + DeepCSVbb in the evt'),
    'csvJet3':('csvJet3',linspace(0, 1, 21).tolist(),'DeepCSVb + DeepCSVbb for jet3pt'),
    'csvJet4':('csvJet4',linspace(0, 1, 21).tolist(),'DeepCSVb + DeepCSVbb for jet4pt'),
    'HTx':('HTx',linspace(0, 1000, 101).tolist(),';H_{T} of reduced hadronic system [GeV]'), 
    'MHRE':('MHRE',linspace(0, 1000, 101).tolist(),';Invariant mass of all jets minus reconst. had. tops [GeV]'), 
    'GD_Ttrijet_TopMass':('GD_Ttrijet_TopMass',linspace(0, 400, 101).tolist(),';Invariant mass of good trijet [GeV]'),
    'BD_Ttrijet_TopMass':('BD_Ttrijet_TopMass',linspace(0, 2000, 501).tolist(),';Invariant mass of bad trijets [GeV]'),
    'GD_DCSV_jetNotdijet':('GD_DCSV_jetNotdijet',linspace(0, 1, 21).tolist(),';DCSVb + DCSVbb for jet NOT used in dijet invariant mass for good trijet'),
    'BD_DCSV_jetNotdijet':('BD_DCSV_jetNotdijet',linspace(0, 1, 21).tolist(),';DCSVb + DCSVbb for jet NOT used in dijet invariant mass for bad trijets'),
    'GD_DR_Tridijet':('GD_DR_Tridijet',linspace(0, 4, 21).tolist(),';dR between trijet and the W dijet for the good trijet'),
    'BD_DR_Tridijet':('BD_DR_Tridijet',linspace(0, 4, 21).tolist(),';dR between trijet and the W dijet for the bad trijets'),
    'GD_DR_Trijet_jetNotdijet':('GD_DR_Trijet_jetNotdijet',linspace(0, 5, 21).tolist(),';dR between trijet and the b jet (jet not in W dijet) for the good trijet'),
    'BD_DR_Trijet_jetNotdijet':('BD_DR_Trijet_jetNotdijet',linspace(0, 5, 21).tolist(),';dR between trijet and the b jet (jet not in W dijet) for the bad trijets'),
    'GD_Mass_minDR_dijet':('GD_Mass_minDR_dijet',linspace(0, 250, 51).tolist(),';dijet inv. mass of 2 jets in good trijet with min dR separation [GeV]'),
    'BD_Mass_minDR_dijet':('BD_Mass_minDR_dijet',linspace(0, 1000, 201).tolist(),';dijet invariant mass of two jets in bad trijets with min dR separation [GeV]'),
    'GD_pTrat':('GD_pTrat',linspace(0, 2, 21).tolist(),';rat. vec. sum  pT jets to scalar sum pT jets in good trijet'),
    'BD_pTrat':('BD_pTrat',linspace(0, 4, 41).tolist(),';rat. vec. sum  pT jets to scalar sum pT jets in bad trijets'),
    'Aplanarity':('Aplanarity',linspace(0, .5, 26).tolist(),';Aplanarity'),
    'FW_momentum_0':('FW_momentum_0',linspace(.999999, 1.000001, 21).tolist(),';FW moment 0'),
    'FW_momentum_1':('FW_momentum_1',linspace(0, 1., 51).tolist(),';FW moment 1'),
    'FW_momentum_2':('FW_momentum_2',linspace(0, 1., 51).tolist(),';FW moment 2'),
    'FW_momentum_3':('FW_momentum_3',linspace(0, 1., 51).tolist(),';FW moment 3'),
    'FW_momentum_4':('FW_momentum_4',linspace(0, 1., 51).tolist(),';FW moment 4'),
    'FW_momentum_5':('FW_momentum_5',linspace(0, 1., 51).tolist(),';FW moment 5'),
    'FW_momentum_6':('FW_momentum_6',linspace(0, 1., 51).tolist(),';FW moment 6'),
#    'FW_momentum_6':('FW_momentum_6',linspace(0, 1., 51).tolist(),';FW moment 6'),
    'HT_woBESTjet' :('HT_woBESTjet', linspace(0,3000, 101).tolist(),';HT minus HT of best trijet [GeV]'),
    'MT_lepMet' :('MT_lepMet', linspace(0,1000, 51).tolist(),';MT (lep, MET) [GeV]'),
    'MT_woBESTjet' :('MT_woBESTjet', linspace(0,6000, 101).tolist(),';MT minus MT of best trijet [GeV]'),
    'M_allJet_W' :('M_allJet_W', linspace(0,7000, 101).tolist(),';M (all jets + best W) [GeV]'),
    'M_woBESTjet' :('M_woBESTjet', linspace(0,5000, 101).tolist(),';M minus M of best trijet [GeV]'),
    'PT_woBESTjet' :('PT_woBESTjet', linspace(0,1200, 101).tolist(),';pT (event - best trijet) [GeV]'),
    'PtFifthJet' :('PtFifthJet', linspace(0,1000, 51).tolist(),';pT of fifth b-tagged jet [GeV]'),
    'Sphericity' :('Sphericity', linspace(0,1, 21).tolist(),';Sphericity'),
    'W_PtdM' :('W_PtdM', linspace(0,5, 51).tolist(),';Ratio of pT to Mass for the best W'),
    'aveBBdr' :('aveBBdr', linspace(0,5, 51).tolist(),';Average deltaR between b jets'),
    'invM_jet34' :('invM_jet34', linspace(0,1500, 51).tolist(),';Mass of jets with third and fourth highest CSV scores'),
    'invM_jet35' :('invM_jet35', linspace(0,400, 201).tolist(),';Mass of jets with third and fifth highest CSV scores'),
    'invM_jet36' :('invM_jet36', linspace(0,400, 201).tolist(),';Mass of jets with third and sixth highest CSV scores'),
    'invM_jet45' :('invM_jet45', linspace(0,400, 201).tolist(),';Mass of jets with fourth and fith highest CSV scores'),
    'invM_jet46' :('invM_jet46', linspace(0,400, 201).tolist(),';Mass of jets with fourth and sixth highest CSV scores'),
    'invM_jet56' :('invM_jet56', linspace(0,400, 201).tolist(),';Mass of jets with fifth and sixth highest CSV scores'),
    'alphaT' :('alphaT', linspace(0,200, 201).tolist(),';alphaT'), #need to figure this out!!
    'corr_met_singleLepCalc' :('corr_met_singleLepCalc', linspace(0,800, 201).tolist(),';MET [GeV]'),
    'csvJet1' :('csvJet1', linspace(0,1, 101).tolist(),'; DeepCSVb+DeepCSVbb Score of 1st pT jet'),
    'csvJet2' :('csvJet2', linspace(0,1, 101).tolist(),'; DeepCSVb+DeepCSVbb Score of 2nd pT jet'),
    'csvJet3' :('csvJet3', linspace(0,1, 101).tolist(),'; DeepCSVb+DeepCSVbb Score of 3rd pT jet'),
    'csvJet4' :('csvJet4', linspace(0,1, 101).tolist(),'; DeepCSVb+DeepCSVbb Score of 4th pT jet'),
    'corr_met_phi_singleLepCalc' :('corr_met_phi_singleLepCalc', linspace(-4,4, 101).tolist(),';Phi of the MET'),
    'deltaEta_maxBB' :('deltaEta_maxBB', linspace(-10,10, 101).tolist(),';deltaEta between most separated b jets'), #binning is probably wrong
    'deltaPhi_lepMET' :('deltaPhi_lepMET', linspace(-5,5, 51).tolist(),';deltaPhi between MET and lep'),
    'deltaPhi_j1j2' :('deltaPhi_j1j2', linspace(-5,5, 51).tolist(),';deltaPhi between 1st and 2nd highest pT jets'),
    'deltaPhi_lepJetInMinMljet' :('deltaPhi_lepJetInMinMljet', linspace(-5,5, 51).tolist(),';deltaPhi between lep and jet with min combined mass'),
    'deltaPhi_METjets' :('deltaPhi_METjets', linspace(-5,5, 51).tolist(),';deltaPhi between MET and jets'),
    'deltaPhi_lepbJetInMinMlb' :('deltaPhi_lepbJetInMinMlb', linspace(-5,5, 51).tolist(),';deltaPhi between lep and b jet with min combined mass'),
    'deltaR_lepBJet_maxpt' :('deltaR_lepBJet_maxpt', linspace(0,5, 21).tolist(),';deltaR between lep and pT wtih max comb. pT'),
    'deltaR_lepBJets0' :('deltaR_lepBJets0', linspace(0,5, 21).tolist(),';dR lep and lead pT b tagged jet'),
    'deltaR_lepBJets1' :('deltaR_lepBJets1', linspace(0,5, 21).tolist(),';dR lep and 2nd lead pT b tagged jet'),
    'deltaR_lepBJets' :('deltaR_lepBJets', linspace(0,5, 21).tolist(),';dR lep and b tagged jet'),
    'deltaR_lepJetInMinMljet' :('deltaR_lepJetInMinMljet', linspace(0,5, 21).tolist(),';deltaR lep and jet with min comb. mass'),
    'deltaR_lepJets' :('deltaR_lepJets', linspace(0,5, 21).tolist(),';deltaR lep and jets'),
    'deltaR_lepbJetInMinMlb' :('deltaR_lepbJetInMinMlb', linspace(0,6, 21).tolist(),';deltaR lep and b jet in min mass lep b pair'),
    'deltaR_lepbJetNotInMinMlb' :('deltaR_lepbJetNotInMinMlb', linspace(0,6, 21).tolist(),';deltaR lep and b jet not in min mass lep b pair'),
    'deltaR_minBB' :('deltaR_minBB', linspace(0,12, 31).tolist(),';deltaR between closest b jets'),
    'firstcsvb_bb' :('firstcsvb_bb', linspace(0,1, 51).tolist(),';DeepCSVb+DeepCSVbb score of jet with best DCSVbpbb score'),
    'fourthcsvb_bb' :('fourthcsvb_bb', linspace(0,1, 51).tolist(),';DeepCSVb+DeepCSVbb score of jet with fourth-best DCSVbpbb score'),
    'hemiout' :('hemiout', linspace(0,2000, 101).tolist(),';Hemiout [GeV]'),
    'lepDR_minBBdr' :('lepDR_minBBdr', linspace(0,6, 21).tolist(),';dR between min. separated b jet pair and lep'),
    'mass_lepBB_minBBdr' :('mass_lepBB_minBBdr', linspace(0,1200, 101).tolist(),';mass of lep and min. separated b jet pair [GeV]'),
    'mass_lepBJet0' :('mass_lepBJet0', linspace(0,1200, 101).tolist(),';Mass of lep and lead pT b tagged jet [GeV]'),
    'mass_lepBJet_mindr' :('mass_lepBJet_mindr', linspace(0,800, 101).tolist(),';mass of lep and b with min. dr [GeV]'),
    'mass_lepJJ_minJJdr' :('mass_lepJJ_minJJdr', linspace(0,1500, 201).tolist(),';mass of lep and jet pair with min dR [GeV]'),
    'mass_lepJets0' :('mass_lepJets0', linspace(0,1500, 201).tolist(),';Mass of lep and lead pT jet [GeV]'),
    'mass_lepJets1' :('mass_lepJets1', linspace(0,1200, 201).tolist(),';Mass of lep and 2nd-lead pT jet [GeV]'),
    'mass_lepJets2' :('mass_lepJets2', linspace(0,1000, 201).tolist(),';Mass of lep and 3rd-lead pT jet [GeV]'),
    'mass_maxBBmass' :('mass_maxBBmass', linspace(0,1500, 301).tolist(),';Max mass b jet pair [GeV]'),
    'mass_maxBBpt' :('mass_maxBBpt', linspace(0,1000, 301).tolist(),';bb pair with max pT [GeV]'),
    'mass_maxJJJpt' :('mass_maxJJJpt', linspace(0,2000, 401).tolist(),';trijet with max pT [GeV]'),
    'mass_minBBdr' :('mass_minBBdr', linspace(0,400, 101).tolist(),';mass of b pair with min dr [GeV]'),
    'mass_minLLdr' :('mass_minLLdr', linspace(0,400, 101).tolist(),';mass of non b tagged pair with min dr [GeV]'),
    'mean_csv' :('mean_csv', linspace(0,1, 101).tolist(),';mean DCSVb + DCSVbb value of jets in the evt'),
    'minBBdr' :('minBBdr', linspace(0,20, 101).tolist(),';mindr between b jets'),
    'minDR_lepBJet' :('minDR_lepBJet', linspace(0,20, 101).tolist(),';dr of minimally separated lep and  b jet'),
    'minMleppBjet' :('minMleppBjet', linspace(0,1500, 301).tolist(),';min mass lep and b jet pair [GeV]'),
    'min_deltaPhi_METjets' :('min_deltaPhi_METjets', linspace(0,2, 51).tolist(),';min deltaPhi between MET and jet'),
    'pT_3rdcsvJet' :('pT_3rdcsvJet', linspace(0,2, 51).tolist(),';pT of jet with 3rd highest DCSVb+DCSVbb score [GeV]'), #no longer as of 31 March 2019#dummy for the moment because the branch was not filled in the edition of step2 from pre 31 March 2019
    'pT_4thcsvJet' :('pT_4thcsvJet', linspace(0,2, 51).tolist(),';pT of jet with 3rd highest DCSVb+DCSVbb score [Gev]'), #no longer as of 31 March 2019#dummy for the moment because the branch was not filled in the edition of step2 from pre 31 March 2019
    'pTjet5_6' :('pTjet5_6', linspace(0,400, 101).tolist(),';vec. sum of pT of 5th & 6th pT jets'),
    'pt3HT' :('pt3HT', linspace(0,400, 101).tolist(),';ratio of pT of 3rd highest pT jet to total HT'), #no longer as of 31 March 2019 #dummy for the moment bc branch was not filled in the pre 31 March 2019 edition of step2
    'pt4HT' :('pt4HT', linspace(0,400, 101).tolist(),';ratio of pT of 3rd highest pT jet to total HT'),#no longer as of 31 March 2019 #dummy for the moment bc branch was not filled in the pre 31 March 2019 edition of step2
	'ratio_HTdHT4leadjets' :('ratio_HTdHT4leadjets', linspace(1,3, 51).tolist(),';ratio of total HT divided by HT of 4 lead pT jets'),
	'secondcsvb_bb' :('secondcsvb_bb', linspace(0,1, 51).tolist(),';DeepCSVb+DeepCSVbb score of jet with second-best DCSVbpbb score'),
	'theJetLeadPt' :('theJetLeadPt', linspace(0,800, 81).tolist(),';pT of lead pT jet [GeV]'), #should duplicate the info in Jet1Pt but putting this in to match what Jangbae has in some of his code...although really should not be necessary but I have already typed it in so...
	'MT2bb' :('MT2bb', linspace(0,100, 101).tolist(),';Davis Moment 2 of 2 lead pT b jets'), #no longer as of 31 March 2019#dummy for the moment bc branch was not filled in the pre 31 March 2019 edition of step2
	'TJetLeadPt' :('TJetLeadPt', linspace(-100,-98, 21).tolist(),';Lead pT top jet'), #dummy for the moment bc branch was not filled in the pre 31 march 2019 edition of step2
	'WJetLeadPt' :('WJetLeadPt', linspace(-100,-98, 21).tolist(),';Lead pT W jet'), #dummy for the moment bc branch was not filled in the pre 31 march 2019 edition of step2
	'minMleppJet' :('minMleppJet', linspace(0,300, 31).tolist(),';Min mass lep & jet pair [GeV]'),
	}

print "PLOTTING:",iPlot
print "         LJMET Variable:",plotList[iPlot][0]
print "         X-AXIS TITLE  :",plotList[iPlot][2]
print "         BINNING USED  :",plotList[iPlot][1]

catList = list(itertools.product(isEMlist,nttaglist,nWtaglist,nbtaglist,njetslist))
nCats  = len(catList)

catInd = 1
for cat in catList:
 	if not runData: break
 	catDir = cat[0]+'_nT'+cat[1]+'_nW'+cat[2]+'_nB'+cat[3]+'_nJ'+cat[4]
 	datahists = {}
 	if len(sys.argv)>1: outDir=sys.argv[1]
 	else: 
		outDir = os.getcwd()
		outDir+='/'+pfix
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+cutString
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+catDir
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
 	category = {'isEM':cat[0],'nttag':cat[1],'nWtag':cat[2],'nbtag':cat[3],'njets':cat[4]}
 	for data in dataList: 
 		datahists.update(analyze(tTreeData,data,data,cutList,isotrig,False,doJetRwt,iPlot,plotList[iPlot],category,region,isCategorized))
 		if catInd==nCats: del tFileData[data]
 	pickle.dump(datahists,open(outDir+'/datahists_'+iPlot+'.p','wb'))
 	catInd+=1

catInd = 1
for cat in catList:
 	if not runBkgs: break
 	catDir = cat[0]+'_nT'+cat[1]+'_nW'+cat[2]+'_nB'+cat[3]+'_nJ'+cat[4]
 	bkghists  = {}
 	if len(sys.argv)>1: outDir=sys.argv[1]
 	else: 
		outDir = os.getcwd()
		outDir+='/'+pfix
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+cutString
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+catDir
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
 	category = {'isEM':cat[0],'nttag':cat[1],'nWtag':cat[2],'nbtag':cat[3],'njets':cat[4]}
 	for bkg in bkgList: 
 		bkghists.update(analyze(tTreeBkg,bkg,bkg,cutList,isotrig,doAllSys,doJetRwt,iPlot,plotList[iPlot],category,region,isCategorized))
 		if 'TTJets' in bkg and len(ttFlvs)!=0:
 			for flv in ttFlvs: bkghists.update(analyze(tTreeBkg,bkg,bkg+flv,cutList,isotrig,doAllSys,doJetRwt,iPlot,plotList[iPlot],category,region,isCategorized))
 		if catInd==nCats: del tFileBkg[bkg]
 		if doAllSys and catInd==nCats:
 			for syst in shapesFiles:
 				for ud in ['Up','Down']: del tFileBkg[bkg+syst+ud]
 	if doQ2sys: 
 		for q2 in q2List: 
 			bkghists.update(analyze(tTreeBkg,q2,q2,cutList,isotrig,False,doJetRwt,iPlot,plotList[iPlot],category,region,isCategorized))
 			if catInd==nCats: del tFileBkg[q2]
	pickle.dump(bkghists,open(outDir+'/bkghists_'+iPlot+'.p','wb'))
 	catInd+=1

catInd = 1
for cat in catList:
 	if not runSigs: break
 	catDir = cat[0]+'_nT'+cat[1]+'_nW'+cat[2]+'_nB'+cat[3]+'_nJ'+cat[4]
 	sighists  = {}
 	if len(sys.argv)>1: outDir=sys.argv[1]
 	else: 
		outDir = os.getcwd()
		outDir+='/'+pfix
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+cutString
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
		outDir+='/'+catDir
		if not os.path.exists(outDir): os.system('mkdir '+outDir)
 	category = {'isEM':cat[0],'nttag':cat[1],'nWtag':cat[2],'nbtag':cat[3],'njets':cat[4]}
 	for sig in sigList: 
 		for decay in decays: 
 			sighists.update(analyze(tTreeSig,sig+decay,sig+decay,cutList,isotrig,doAllSys,doJetRwt,iPlot,plotList[iPlot],category,region,isCategorized))
 			if catInd==nCats: del tFileSig[sig+decay]
 			if doAllSys and catInd==nCats:
 				for syst in shapesFiles:
 					for ud in ['Up','Down']: del tFileSig[sig+decay+syst+ud]
	pickle.dump(sighists,open(outDir+'/sighists_'+iPlot+'.p','wb'))
 	catInd+=1

print("--- %s minutes ---" % (round((time.time() - start_time)/60,2)))
