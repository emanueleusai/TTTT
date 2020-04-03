#!/usr/bin/env python

#input variables
varList = {}

inputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2018_Oct2019_4t_03032020_step2/nominal/'

bkg = [
#TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root

#'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttbb_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttcc_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_1_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_2_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_3_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_4_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_5_hadd.root',

#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttbb_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttcc_hadd.root',
#'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttjj_hadd.root',
#'DYJetsToLL_M-50_HT-1200to2500_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'DYJetsToLL_M-50_HT-200to400_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'DYJetsToLL_M-50_HT-2500toInf_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'DYJetsToLL_M-50_HT-400to600_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'DYJetsToLL_M-50_HT-600to800_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'DYJetsToLL_M-50_HT-800to1200_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'QCD_HT1000to1500_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT1500to2000_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT2000toInf_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT200to300_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT300to500_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT500to700_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'QCD_HT700to1000_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'ST_s-channel_antitop_leptonDecays_13TeV-PSweights_powheg-pythia_hadd.root',
#'ST_s-channel_top_leptonDecays_13TeV-PSweights_powheg-pythia_hadd.root',
#'ST_t-channel_antitop_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
#'ST_t-channel_top_4f_InclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
#'ST_tW_antitop_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
#'ST_tW_top_5f_inclusiveDecays_TuneCP5_PSweights_13TeV-powheg-pythia8_hadd.root',
#'TTHH_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'ttHTobb_M125_TuneCP5_13TeV-powheg-pythia8_hadd.root',
#'ttHToNonbb_M125_TuneCP5_13TeV-powheg-pythia8_hadd.root',
#'TTTJ_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTTW_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTWH_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTWJetsToLNu_TuneCP5_PSweights_13TeV-amcatnloFXFX-madspin-pythia8_hadd.root',
#'TTWW_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTWZ_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTZH_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'TTZToLL_M-1to10_TuneCP5_13TeV-amcatnlo-pythia8_hadd.root',
#'TTZToLLNuNu_M-10_TuneCP5_PSweights_13TeV-amcatnlo-pythia8_hadd.root',
#'TTZZ_TuneCP5_13TeV-madgraph-pythia8_hadd.root',
#'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_1_hadd.root',
#'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_2_hadd.root',
#'WJetsToLNu_HT-1200To2500_TuneCP5_13TeV-madgraphMLM-pythia8_3_hadd.root',
#'WJetsToLNu_HT-200To400_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_1_hadd.root',
#'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_2_hadd.root',
#'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_3_hadd.root',
#'WJetsToLNu_HT-2500ToInf_TuneCP5_13TeV-madgraphMLM-pythia8_4_hadd.root',
#'WJetsToLNu_HT-400To600_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'WJetsToLNu_HT-600To800_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'WJetsToLNu_HT-800To1200_TuneCP5_13TeV-madgraphMLM-pythia8_hadd.root',
#'WW_TuneCP5_13TeV-pythia8_hadd.root',
#'WZ_TuneCP5_13TeV-pythia8_hadd.root',
#'ZZ_TuneCP5_13TeV-pythia8_hadd.root',

## 2018
'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttbb_hadd.root',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttcc_hadd.root',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttjj_1_hadd.root',
'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttjj_2_hadd.root',

 ]

#[<variable in trees>, <variable name for axes and titles>, <unit>]

varList['Comb61andtrij'] = [
['HOTGoodTrijet1_mass', 'HOTGoodTrijet1_mass', 'GeV'],
['HOTGoodTrijet1_dijetmass', 'HOTGoodTrijet1_dijetmass', 'GeV'],
['HOTGoodTrijet1_pTratio', 'HOTGoodTrijet1_pTratio', ''],
['HOTGoodTrijet1_dRtridijet','HOTGoodTrijet1_dRtridijet',''],
['HOTGoodTrijet1_dRtrijetJetnotdijet', 'HOTGoodTrijet1_dRtrijetJetnotdijet',''],
['HOTGoodTrijet1_csvJetnotdijet','HOTGoodTrijet1_csvJetnotdijet',''],
['HOTGoodTrijet2_mass', 'HOTGoodTrijet2_mass', 'GeV'],
['HOTGoodTrijet2_dijetmass', 'HOTGoodTrijet2_dijetmass', 'GeV'],
['HOTGoodTrijet2_pTratio', 'HOTGoodTrijet2_pTratio', ''],
['HOTGoodTrijet2_dRtridijet','HOTGoodTrijet2_dRtridijet',''],
['HOTGoodTrijet2_dRtrijetJetnotdijet', 'HOTGoodTrijet2_dRtrijetJetnotdijet',''],
['HOTGoodTrijet2_csvJetnotdijet','HOTGoodTrijet2_csvJetnotdijet',''],
#['HOTBadTrijet1_mass', 'HOTBadTrijet1_mass', 'GeV'],
#['HOTBadTrijet1_dijetmass', 'HOTBadTrijet1_dijetmass', 'GeV'],
#['HOTBadTrijet1_pTratio', 'HOTBadTrijet1_pTratio', ''],
#['HOTBadTrijet1_dRtridijet','HOTBadTrijet1_dRtridijet',''],
#['HOTBadTrijet1_dRtrijetJetnotdijet', 'HOTBadTrijet1_dRtrijetJetnotdijet',''],
#['HOTBadTrijet1_csvJetnotdijet','HOTBadTrijet1_csvJetnotdijet',''],
#['HOTBadTrijet2_mass', 'HOTBadTrijet2_mass', 'GeV'],
#['HOTBadTrijet2_dijetmass', 'HOTBadTrijet2_dijetmass', 'GeV'],
#['HOTBadTrijet2_pTratio', 'HOTBadTrijet2_pTratio', ''],
#['HOTBadTrijet2_dRtridijet','HOTBadTrijet2_dRtridijet',''],
#['HOTBadTrijet2_dRtrijetJetnotdijet', 'HOTBadTrijet2_dRtrijetJetnotdijet',''],
#['HOTBadTrijet2_csvJetnotdijet','HOTBadTrijet2_csvJetnotdijet',''],
]


varList['Comb20top'] = [
['csvJet3','DeepCSV(3rdPtJet)',''],
['csvJet4','DeepCSV(4thPtJet)',''],
['NJetsCSVwithSF_JetSubCalc', 'bjet multiplicity', ''],
['NJets_JetSubCalc','AK4 jet multiplicity',''],
['sixthJetPt','p_{T}(j_{6})','GeV'],
['BDTtrijet2','trijet2 discriminator',''],
['fifthJetPt','p_{T}(j_{5})','GeV'],
['PtFifthJet','5^{th} jet p_{T}','GeV'],
['ratio_HTdHT4leadjets','HT/HT(4 leading jets)',''],
['AK4HTpMETpLepPt','S_{T}','GeV'],
['AK4HT','H_{T}','GeV'],
['hemiout','Hemiout','GeV'],
['BDTtrijet3','trijet3 discriminator',''],
['HT_bjets','HT(bjets)','GeV'],
# top14 in Importance
['MT_lepMet','M_{T}(lep,E_{T}^{miss})','GeV'],
['corr_met_MultiLepCalc','E_{T}^{miss}','GeV'],
['BDTtrijet1','trijet1 discriminator',''],
['MT2bb','MT2bb','GeV'],
['minMleppBjet','min[M(l,b)]','GeV'],
['mass_maxJJJpt','M(jjj) with max[p_{T}(jjj)]','GeV'],
]


varList['CombIpRank'] = [  # 61 var importance ranking 
['BDTtrijet2','trijet2 discriminator',''],
['thirdcsvb_bb','DeepCSV(3rdDeepCSVJet)',''],
['fourthcsvb_bb','DeepCSV(4thDeepCSVJet)',''],
['NJetsCSVwithSF_JetSubCalc', 'bjet multiplicity', ''],
['MT_lepMet','M_{T}(lep,E_{T}^{miss})','GeV'],
['fifthJetPt','p_{T}(j_{5})','GeV'],
['BDTtrijet3','trijet3 discriminator',''],
['NJets_JetSubCalc','AK4 jet multiplicity',''],
['sixthJetPt','p_{T}(j_{6})','GeV'],
['corr_met_MultiLepCalc','E_{T}^{miss}','GeV'],
['BDTtrijet1','trijet1 discriminator',''],
['MT2bb','MT2bb','GeV'],
['minMleppBjet','min[M(l,b)]','GeV'],
['mass_maxJJJpt','M(jjj) with max[p_{T}(jjj)]','GeV'],
['hemiout','Hemiout','GeV'],
['Aplanarity','Aplanarity','Aplanarity'],
['AK4HTpMETpLepPt','S_{T}','GeV'],
['NJetsTtagged', 'top multiplicity', ''],
['centrality','Centrality',''],
['HT_bjets','HT(bjets)','GeV'],
['FW_momentum_1','1^{st} FW moment','GeV'],
['mass_lepBJet0','M(l,b_{1})','GeV'],
['mass_lepBJet_mindr','M(l,b) with min[#DeltaR(l,b)]','GeV'],
['deltaR_lepBJet_maxpt','#DeltaR(l,b)] with max[p_{T}(l,b)]',''],
['Sphericity','Sphericity','Sphericity'],
['deltaR_lepbJetInMinMlb','#DeltaR(l,b) with min M(l, b)',''],
['minDR_lepBJet','min[#DeltaR(l,b)]',''],
['mass_maxBBmass','max[M(b,b)]','GeV'],
['deltaR_minBB','min[#DeltaR(b,b)]',''],
['aveBBdr','ave[#DeltaR(b,b)]',''],
['ratio_HTdHT4leadjets','HT/HT(4 leading jets)',''],
['aveCSVpt','p_{T} weighted CSVv2',''],
['mass_lepJets0','M(l,j_{1})','GeV'],
['leptonPt_MultiLepCalc','p_{T}(lep)','GeV'],
['mass_minBBdr','M(b,b) with min[#DeltaR(b,b)]','GeV'],
['mass_minLLdr','M(j,j) with min[#DeltaR(j,j)], j #neq b','GeV'],
['theJetLeadPt','p_{T}(j_{1})','GeV'],
['AK4HT','H_{T}','GeV'],
['FW_momentum_5','5^{th} FW moment','GeV'],
['deltaR_lepJetInMinMljet','#DeltaR(l,j) with min M(l, j)',''],
['secondJetPt','p_{T}(j_{2})','GeV'],
['BJetLeadPt','p_{T}(b_{1})','GeV'],
['csvJet4','DeepCSV(4thPtJet)',''],
['lepDR_minBBdr','#DeltaR(l,bb) with min[#DeltaR(b,b)]',''],
['deltaEta_maxBB','max[#Delta#eta(b,b)]',''],
['FW_momentum_0','0^{th} FW moment','GeV'],
['FW_momentum_2','2^{nd} FW moment','GeV'],
['FW_momentum_3','3^{rd} FW moment','GeV'],
['FW_momentum_4','4^{th} FW moment','GeV'],
['FW_momentum_6','6^{th} FW moment','GeV'],
['mass_lepJets1','M(l,j_{2})','GeV'],
['mass_lepJets2','M(l,j_{3})','GeV'],
['PtFifthJet','5^{th} jet p_{T}','GeV'],
['deltaPhi_lepJetInMinMljet','#DeltaPhi(l,j) with min M(l, j)',''],
['deltaPhi_lepbJetInMinMlb','#DeltaPhi(l,b) with min M(l, b)',''],
['M_allJet_W','M(allJets, leptoninc W)','GeV'],
['csvJet3','DeepCSV(3rdPtJet)',''],
['HT_2m','HTwoTwoPtBjets','GeV'],
['BDTtrijet4','trijet4 discriminator',''],
['NresolvedTops1pFake','resolvedTop multiplicity', ''],
['NJetsWtagged', 'W multiplicity',''],

]

for ind in range(20, 61, 2):
  varList['CombIpRank'+ str(ind)+ 'top'] = varList['CombIpRank'][:ind]

varList['Comb61andtrij'] += varList['CombIpRank']
