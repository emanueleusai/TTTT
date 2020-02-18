import os,sys
import varsList

shift = sys.argv[1]
BDT = 'BDT'

varListKey = 'BigComb'
#templateFile = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/src/TMVA/TMVAClassificationApplication_template.C'
templateFile = '/home/eusai/4t/TTTT/TMVA/TMVAClassificationApplication_template.C'
# massList = ['Low1','Low2']
#weightFile = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/src/TMVA/dataset/weights/'
weightFile = '/home/eusai/4t/TTTT/TMVA/dataset2020Feb10/weights/'
weightFile+= BDT+'_BigComb_61vars_mDepth2/TMVAClassification_'+BDT+'.weights.xml'

#IO directories must be full paths
#relbase   = '/user_data/jlee/TTTT/CMSSW_9_4_6_patch1/'
relbase = '/home/eusai/4t/CMSSW_10_2_16_UL/'

inputDir  = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_02052020_step2'
#outputDir = '/isilon/hadoop/store/user/jblee/TTTT/LJMet94X_1lepTT_022719_step2_saraBDay_'+BDT+'_BigComb_3var/'+shift+'/'
outputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_02182020_step3_61var/'+shift+'/'
# outputDir = '/isilon/hadoop/store/user/mhadley/LJMet94X_1lepTT_022719_step2_saraBDay_'+BDT+'_BigComb_3var/'+shift+'/'


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
					fout.write('   Float_t var'+str(i+1)+';\n')
			elif 'AddVariable' in line:
				for i, var in enumerate(varList): 
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
					fout.write('   theTree->SetBranchAddress( \"'+var[0]+'\", &var'+str(i+1)+' );\n')
			elif 'BDT<mass> = reader->EvaluateMVA' in line:
# 				for mass in massList: 
				fout.write('      BDT = reader->EvaluateMVA( \"BDT method\" );\n')
			else: fout.write(line)
makeTMVAClassAppConf(condorDir+'/TMVAClassificationApplication.C')

rootfiles = os.popen('ls '+inputDir)
os.system('mkdir -p '+outputDir)

count=0
for file in rootfiles:
    if '.root' not in file: continue
    # if 'QCD_HT300to500_TuneCP5' not in file: continue
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
    # os.system('condor_submit %(FILENAME)s.job'%dict)
    os.system('sleep 0.5')                                
    os.chdir('%s'%(runDir))
    print count, "jobs submitted!!!"

