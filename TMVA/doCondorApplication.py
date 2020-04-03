import os,sys
import varsList

shift = sys.argv[1]
BDT = 'BDT'

# varListKey = 'BigComb'

# varListKey = 'Comb61andtrij'
varListKey = 'CombIpRank'



#templateFile = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/src/TMVA/TMVAClassificationApplication_template.C'
templateFile = '/home/eusai/4t/TTTT/TMVA/TMVAClassificationApplication_template.C'
# massList = ['Low1','Low2']
#weightFile = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/src/TMVA/dataset/weights/'
weightFile = '/home/eusai/4t/TTTT/TMVA/dataset2020/weights/'
# weightFile+= BDT+'_BigComb_61vars_mDepth2/TMVAClassification_'+BDT+'.weights.xml'

# weightFile+= BDT+'_Comb61andtrij_73vars_mDepth2_4j_year2017/TMVAClassification_'+BDT+'.weights.xml'
# weightFile+= BDT+'_Comb61andtrij_73vars_mDepth2_6j_year2017/TMVAClassification_'+BDT+'.weights.xml'
# weightFile+= BDT+'_CombIpRank_61vars_mDepth2_4j_year2017/TMVAClassification_'+BDT+'.weights.xml'
# weightFile+= BDT+'_CombIpRank_61vars_mDepth2_6j_year2017/TMVAClassification_'+BDT+'.weights.xml'

# weightFile+= BDT+'_Comb61andtrij_73vars_mDepth2_6j_year2018/TMVAClassification_'+BDT+'.weights.xml'
weightFile+= BDT+'_CombIpRank_61vars_mDepth2_6j_year2018/TMVAClassification_'+BDT+'.weights.xml'

#IO directories must be full paths

relbase = '/home/eusai/4t/CMSSW_10_2_16_UL/'

# inputDir  = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_02132020_step2'

# inputDir  = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_03032020_step2'
inputDir  = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2018_Oct2019_4t_03032020_step2'


# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_02192020_step3_61var/'+shift+'/'

# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_03192020_step3_73vars_4j/'+shift+'/'
# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_03192020_step3_73vars_6j/'+shift+'/'
# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_03192020_step3_61vars_4j/'+shift+'/'
# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_03192020_step3_61vars_6j/'+shift+'/'

# BDT_Comb61andtrij_73vars_mDepth2_4j_year2017
# BDT_Comb61andtrij_73vars_mDepth2_6j_year2017
# BDT_CombIpRank_61vars_mDepth2_4j_year2017
# BDT_CombIpRank_61vars_mDepth2_6j_year2017

# outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2018_Oct2019_4t_03192020_step3_73vars_6j/'+shift+'/'
outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2018_Oct2019_4t_03192020_step3_61vars_6j/'+shift+'/'

# BDT_Comb61andtrij_73vars_mDepth2_6j_year2018
# BDT_CombIpRank_61vars_mDepth2_6j_year2018

inputDir += '/'+shift+'/'
runDir=os.getcwd()
varList = varsList.varList[varListKey]
condorDir=runDir+'/Application_'+outputDir.split('/')[-3]+'_condorLogs/'+shift+'/'
os.system('mkdir -p '+condorDir)

f = open(templateFile, 'rU')
templateFileLines = f.readlines()
f.close()
def makeTMVAClassAppConf(thefile):
	with open(thefile,'w') as fout:
		for line in templateFileLines:
			if line.startswith('input ='): fout.write('input = \''+rFile+'\'')
			if 'Float_t var<number>' in line:
				for i, var in enumerate(varList): 
					if var[0]=='corr_met_MultiLepCalc':
						fout.write('   Float_t varF'+str(i+1)+';\n')
						fout.write('   Double_t varD'+str(i+1)+';\n')
					elif var[0] in ['NJets_JetSubCalc','NresolvedTops1pFake','NJetsTtagged','NJetsWtagged','NJetsCSVwithSF_JetSubCalc']:
						fout.write('   Float_t varF'+str(i+1)+';\n')
						fout.write('   Int_t varI'+str(i+1)+';\n')
					else:
						fout.write('   Float_t var'+str(i+1)+';\n')
			elif 'AddVariable' in line:
				for i, var in enumerate(varList):
					if var[0]=='corr_met_MultiLepCalc': 
						fout.write('   reader->AddVariable( \"'+var[0]+'\", &varF'+str(i+1)+' );\n')
					elif var[0] in ['NJets_JetSubCalc','NresolvedTops1pFake','NJetsTtagged','NJetsWtagged','NJetsCSVwithSF_JetSubCalc']:
						fout.write('   reader->AddVariable( \"'+var[0]+'\", &varF'+str(i+1)+' );\n')
					else:
						fout.write('   reader->AddVariable( \"'+var[0]+'\", &var'+str(i+1)+' );\n')
			elif 'BookMVA' in line:
# 				for mass in massList: 
				fout.write('   reader->BookMVA( \"BDT method\", \"'+weightFile+'\" );\n')
			elif 'Float_t BDT<mass>' in line:
# 				for mass in massList: 
				fout.write('   Float_t BDT;\n')
				fout.write('   TBranch *b_BDT = newTree->Branch( \"BDT\", &BDT, \"BDT/F\" );\n')
			elif 'SetBranchAddress' in line:
				for i, var in enumerate(varList): 
					if var[0]=='corr_met_MultiLepCalc': 
						fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &varD'+str(i+1)+' );\n')
					elif var[0] in ['NJets_JetSubCalc','NresolvedTops1pFake','NJetsTtagged','NJetsWtagged','NJetsCSVwithSF_JetSubCalc']:
						fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &varI'+str(i+1)+' );\n')
					else:
						fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &var'+str(i+1)+' );\n')
			elif 'BDT<mass> = reader->EvaluateMVA' in line:
# 				for mass in massList: 
				for i, var in enumerate(varList):
					if var[0]=='corr_met_MultiLepCalc': 
						fout.write('      varF'+str(i+1)+'=(Float_t)varD'+str(i+1)+';\n')
					elif var[0] in ['NJets_JetSubCalc','NresolvedTops1pFake','NJetsTtagged','NJetsWtagged','NJetsCSVwithSF_JetSubCalc']:
						fout.write('      varF'+str(i+1)+'=(Float_t)varI'+str(i+1)+';\n')

				fout.write('      BDT = reader->EvaluateMVA( \"BDT method\" );\n')
			else: fout.write(line)
makeTMVAClassAppConf(condorDir+'/TMVAClassificationApplication.C')

rootfiles = os.popen('ls '+inputDir)
os.system('mkdir -p '+outputDir)

count=0
for file in rootfiles:
    if '.root' not in file: continue
    # if 'TTTT' not in file: continue
    rawname = file[:-6]
    print file
    count+=1
    dict={'RUNDIR':runDir,'INPUTDIR':inputDir,'FILENAME':rawname,'OUTPUTDIR':outputDir,'CONDORDIR':condorDir,'CMSSWBASE':relbase,'BDT':BDT}
    jdfName=condorDir+'/%(FILENAME)s.job'%dict
    print jdfName
    jdf=open(jdfName,'w')
    jdf.write(
"""universe = vanilla
Executable = %(RUNDIR)s/doCondorApplication.sh
Should_Transfer_Files = YES
WhenToTransferOutput = ON_EXIT
request_memory = 3072
Transfer_Input_Files = %(CONDORDIR)s/TMVAClassificationApplication.C
Output = %(FILENAME)s.out
Error = %(FILENAME)s.err
Log = %(FILENAME)s.log
Notification = Never
Arguments = %(INPUTDIR)s %(OUTPUTDIR)s %(FILENAME)s.root %(BDT)s %(CONDORDIR)s

Queue 1"""%dict)
    jdf.close()
    os.chdir('%s/'%(condorDir))
    print 'condor_submit %(FILENAME)s.job'%dict
    os.system('condor_submit %(FILENAME)s.job'%dict)
    os.system('sleep 2')                                
    os.chdir('%s'%(runDir))
    print count, "jobs submitted!!!"

