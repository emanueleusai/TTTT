import os,sys
import varsList

# nominal 2017 73 4

shift = sys.argv[1]

BDT = 'BDT'
year = sys.argv[2]
njet = sys.argv[4]
nvar = sys.argv[3]
pfx = sys.argv[5]

if nvar == '73':
	varListKey = 'SepRank6j73vars2017year'
else:
	varListKey = 'SepRank6j73vars2017year'+nvar+'top'


templateFile = '/home/eusai/4t/TTTT/TMVA/TMVAClassificationApplication_template.C'
weightFile = '/home/eusai/4t/TTTT/TMVA/dataset2021/weights/'

# BDT_SepRank6j73vars2017year50top_50vars_mDepth2_6j_year2018
# BDT_SepRank6j73vars2017year_73vars_mDepth2_4j_year2017

weightFile+= BDT+'_'+varListKey+'_'+nvar+'vars_mDepth2_'+njet+'j_year'+year+pfx+'/TMVAClassification_'+BDT+'.weights.xml'

inputDir  = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep'+year+'_Oct2019_4t_10072020_step2'

outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep'+year+'_Oct2019_4t_11072020_step3_'+nvar+'vars_'+njet+'j'+pfx+'/'+shift+'/'

relbase = '/home/eusai/4t/CMSSW_10_2_16_UL/'

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
		vars_to_convert = ['NJets_JetSubCalc','NresolvedTops1pFake','NJetsTtagged','NJetsWtagged','NJetsCSVwithSF_JetSubCalc','NJetsCSV_MultiLepCalc','NJetsCSVwithSF_MultiLepCalc']
		for line in templateFileLines:
			if line.startswith('input ='): fout.write('input = \''+rFile+'\'')
			if 'Float_t var<number>' in line:
				for i, var in enumerate(varList): 
					if var[0]=='corr_met_MultiLepCalc':
						fout.write('   Float_t varF'+str(i+1)+';\n')
						fout.write('   Double_t varD'+str(i+1)+';\n')
					elif var[0] in vars_to_convert:
						fout.write('   Float_t varF'+str(i+1)+';\n')
						fout.write('   Int_t varI'+str(i+1)+';\n')
					else:
						fout.write('   Float_t var'+str(i+1)+';\n')
			elif 'AddVariable' in line:
				for i, var in enumerate(varList):
					if var[0]=='corr_met_MultiLepCalc': 
						fout.write('   reader->AddVariable( \"'+var[0]+'\", &varF'+str(i+1)+' );\n')
					elif var[0] in vars_to_convert:
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
					elif var[0] in vars_to_convert:
						fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &varI'+str(i+1)+' );\n')
					else:
						fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &var'+str(i+1)+' );\n')
			elif 'BDT<mass> = reader->EvaluateMVA' in line:
# 				for mass in massList: 
				for i, var in enumerate(varList):
					if var[0]=='corr_met_MultiLepCalc': 
						fout.write('      varF'+str(i+1)+'=(Float_t)varD'+str(i+1)+';\n')
					elif var[0] in vars_to_convert:
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

