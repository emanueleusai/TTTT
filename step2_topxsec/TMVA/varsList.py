#!/usr/bin/env python

#input variables
varList = {}

inputDir = '/mnt/hadoop/users/mhadley/TTTT/LJMet94X_1lep_040419_step2UpdatedFromJangbae/nominal/'


bkg = [
# 'DYJetsToLL_M-50_TuneCP5_13TeV-amcatnloFXFX-pythia8_hadd.root',
# 'QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
# 'ST_s-channel_4f_leptonDecays_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_hadd.root',
# 'ST_t-channel_antitop_5f_TuneCP5_PSweights_13TeV-powheg-madspin-pythia8_vtd_vts_prod_hadd.root',
# 'ST_t-channel_top_5f_TuneCP5_PSweights_13TeV-powheg-madspin-pythia8_vtd_vts_prod_hadd.root',
# 'ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
# 'ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt0to700_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt1000toInf_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_Mtt700to1000_hadd.root',
'TT_Mtt-1000toInf_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
# 'TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8_hadd.root',
# 'TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_hadd.root',
# 'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
# 'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
# 'WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
# 'WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
# 'WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root
]
#[<variable in trees>, <variable name for axes and titles>, <unit>]
 
varList['BigComb'] = [
['AK4HTpMETpLepPt','S_{T}','GeV'],
['minMleppBjet','min[M(l,b)]','GeV'],
['mass_minBBdr','M(b,b) with min[#DeltaR(b,b)]','GeV'],
['deltaR_lepBJet_maxpt','#DeltaR(l,b)] with max[p_{T}(l,b)]',''],
# ['deltaR_lepJets0','#DeltaR(l,j_{1})',''],
# ['deltaR_lepJets1','#DeltaR(l,j_{2})',''],
# ['deltaR_lepJets2','#DeltaR(l,j_{3})',''],
# ['deltaR_lepBJets0','#DeltaR(l,b_{1})',''],
#['deltaR_lepBJets1','#DeltaR(l,b_{2})',''],
['lepDR_minBBdr','#DeltaR(l,bb) with min[#DeltaR(b,b)]',''],
['centrality','Centrality',''],
['deltaEta_maxBB','max[#Delta#eta(b,b)]',''],
['aveCSVpt','p_{T} weighted CSVv2',''],
['aveBBdr','ave[#DeltaR(b,b)]',''],
['FW_momentum_0','0^{th} FW moment','GeV'],
['FW_momentum_1','1^{st} FW moment','GeV'],
['FW_momentum_2','2^{nd} FW moment','GeV'],
['FW_momentum_3','3^{rd} FW moment','GeV'],
['FW_momentum_4','4^{th} FW moment','GeV'],
['FW_momentum_5','5^{th} FW moment','GeV'],
['FW_momentum_6','6^{th} FW moment','GeV'],
['mass_maxJJJpt','M(jjj) with max[p_{T}(jjj)]','GeV'],
['BJetLeadPt','p_{T}(b_{1})','GeV'],
['deltaR_minBB','min[#DeltaR(b,b)]',''],
['minDR_lepBJet','min[#DeltaR(l,b)]',''],
['MT_lepMet','M_{T}(lep,E_{T}^{miss})','GeV'],
['AK4HT','H_{T}','GeV'],
['hemiout','Hemiout','GeV'],
['theJetLeadPt','p_{T}(j_{1})','GeV'],
['corr_met_singleLepCalc','E_{T}^{miss}','GeV'],
['leptonPt_singleLepCalc','p_{T}(lep)','GeV'],
['mass_lepJets0','M(l,j_{1})','GeV'], 
['mass_lepJets1','M(l,j_{2})','GeV'],
['mass_lepJets2','M(l,j_{3})','GeV'],
['MT2bb','MT2bb','GeV'],
['mass_lepBJet0','M(l,b_{1})','GeV'],
['mass_lepBJet_mindr','M(l,b) with min[#DeltaR(l,b)]','GeV'],
['secondJetPt','second leading jet p_{T}','GeV'],
['fifthJetPt','fifth leading jet p_{T}','GeV'],
['sixthJetPt','sixth leading jet p_{T}','GeV'],
['PtFifthJet','5^{th} jet p_{T}','GeV'],
['mass_minLLdr','M(j,j) with min[#DeltaR(j,j)], j #neq b','GeV'],
['mass_maxBBmass','max[M(b,b)]','GeV'],


['deltaR_lepJetInMinMljet','#DeltaR(l,j) with jet in min[M(l,j)]',''],
['deltaPhi_lepJetInMinMljet','#DeltaPhi(l,j) with jet in min[M(l,j)]',''],
['deltaR_lepbJetInMinMlb','#DeltaR(l,b) with bjet in min[M(l,b)]',''],
['deltaPhi_lepbJetInMinMlb','#DeltaPhi(l,b) with bjet in min[M(l,b)]',''],
['deltaR_lepbJetInMinMlb','#DeltaR(l,b) with bjet not in min[M(l,b)]',''],
['M_allJet_W','M(all,leptonic W)',''],
['HT_bjets','H_{T} of all bjet','GeV'],
# HT(leading 4 jets)['HT_bjets','H_{T} of all bjet','GeV'],
['ratio_HTdHT4leadjets','H_{T}/H_{T} leading 4jets','GeV'],
['csvJet3', 'csvJet3','DeepCSV'],
['csvJet4', 'csvJet3','DeepCSV'],
['thirdcsvb_bb','thirdcsvb_bb','DeepCSV'],
['fourthcsvb_bb','fourthcsvb_bb','DeepCSV'],
['NJets_JetSubCalc','AK4 jet multiplicity',''],
# ['HT_bjets','H_{T} of all bjet','GeV'],
['HT_2m','H_{T} minus two highest p_{T} bjets','GeV'],
['Sphericity','Sphericity','Sphericity'],
['Aplanarity','Aplanarity','Aplanarity'],


# ['mass_maxBBpt','M(b,b) with max[p_{T}(b,b)]','GeV'],
# ['mass_lepJJ_minJJdr','M(l,jj) with min[#DeltaR(j,j)], j #neq b','GeV'],
# ['mass_lepBB_minBBdr','M(l,bb) with min[#DeltaR(b,b)]','GeV'],

]



