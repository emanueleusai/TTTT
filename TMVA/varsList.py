#!/usr/bin/env python

#input variables
varList = {}

inputDir = '/mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_10072020_step2/nominal/'

bkg = [
### 2017 
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_tt1b_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_tt2b_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTTo2L2Nu_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_tt1b_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_tt2b_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTToHadronic_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_tt1b_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_tt2b_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttbb_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttcc_hadd.root',
'TTToSemiLepton_HT500Njet9_TuneCP5_PSweights_13TeV-powheg-pythia8_ttjj_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_tt1b_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_tt2b_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttbb_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttcc_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_1_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_2_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_3_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_4_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT0Njet0_ttjj_5_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_tt1b_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_tt2b_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttbb_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttcc_hadd.root',
'TTToSemiLeptonic_TuneCP5_PSweights_13TeV-powheg-pythia8_HT500Njet9_ttjj_hadd.root',


## 2018
#'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_tt1b_hadd.root',
#'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_tt2b_hadd.root',
#'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTTo2L2Nu_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_tt1b_hadd.root',
#'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_tt2b_hadd.root',
#'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTToHadronic_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_tt1b_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_tt2b_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttbb_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttcc_hadd.root',
#'TTToSemiLepton_HT500Njet9_TuneCP5_13TeV-powheg-pythia8_ttjj_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_tt1b_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_tt2b_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttbb_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttcc_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttjj_1_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT0Njet0_ttjj_2_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT500Njet9_tt1b_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT500Njet9_tt2b_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT500Njet9_ttbb_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT500Njet9_ttcc_hadd.root',
#'TTToSemiLeptonic_TuneCP5_13TeV-powheg-pythia8_HT500Njet9_ttjj_hadd.root',


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
['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
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
['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
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

varList['SepRank4j73vars2017year'] = [ # Mar30 run
]

varList['SepRank4j61vars2017year'] = [ # Mar30 run
]

varList['SepRank6j73vars2017year'] = [ # May07 run 
#['thirdcsvb_bb', 'DeepCSV(3rdDeepCSVJet)', ''],
#['fourthcsvb_bb', 'DeepCSV(4thDeepCSVJet)', ''],
##['NJetsCSV_MultiLepCalc', 'bjet multiplicity', ''],
['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
['NJets_JetSubCalc', 'AK4 jet multiplicity', ''],
['BDTtrijet2', 'trijet2 discriminator', ''],
['AK4HTpMETpLepPt', 'S_{T}', 'GeV'],
['sixthJetPt', 'p_{T}(j_{6})', 'GeV'],
['PtFifthJet', '5^{th} jet p_{T}', 'GeV'],
['hemiout', 'Hemiout', 'GeV'],
['AK4HT', 'H_{T}', 'GeV'],
['HT_bjets', 'HT(bjets)', 'GeV'],
['BDTtrijet3', 'trijet3 discriminator', ''],
['fifthJetPt', 'p_{T}(j_{5})', 'GeV'],
['ratio_HTdHT4leadjets', 'HT/HT(4 leading jets)', ''],
['MT_lepMet', 'M_{T}(lep,E_{T}^{miss})', 'GeV'],
['HT_2m', 'HTwoTwoPtBjets', 'GeV'],
['mass_maxBBmass', 'max[M(b,b)]', 'GeV'],
['deltaR_minBB', 'min[#DeltaR(b,b)]', ''],
['mass_lepBJet0', 'M(l,b_{1})', 'GeV'],
['NresolvedTops1pFake', 'resolvedTop multiplicity', ''],
['HOTGoodTrijet2_pTratio', 'HOTGoodTrijet2_pTratio', ''],
['HOTGoodTrijet2_mass', 'HOTGoodTrijet2_mass', 'GeV'],
['HOTGoodTrijet2_dijetmass', 'HOTGoodTrijet2_dijetmass', 'GeV'],
['HOTGoodTrijet2_dRtridijet', 'HOTGoodTrijet2_dRtridijet', ''],
['HOTGoodTrijet2_dRtrijetJetnotdijet', 'HOTGoodTrijet2_dRtrijetJetnotdijet', ''],
['mass_lepBJet_mindr', 'M(l,b) with min[#DeltaR(l,b)]', 'GeV'],
['M_allJet_W', 'M(allJets, leptoninc W)', 'GeV'],
['minMleppBjet', 'min[M(l,b)]', 'GeV'],
['corr_met_MultiLepCalc', 'E_{T}^{miss}', 'GeV'],
['BJetLeadPt', 'p_{T}(b_{1})', 'GeV'],
['NJetsTtagged', 'top multiplicity', ''],
['secondJetPt', 'p_{T}(j_{2})', 'GeV'],
['aveBBdr', 'ave[#DeltaR(b,b)]', ''],
['FW_momentum_6', '6^{th} FW moment', 'GeV'],
['deltaEta_maxBB', 'max[#Delta#eta(b,b)]', ''],
#['HOTGoodTrijet2_csvJetnotdijet', 'HOTGoodTrijet2_csvJetnotdijet', ''],
['centrality', 'Centrality', ''],
['Aplanarity', 'Aplanarity', 'Aplanarity'],
['MT2bb', 'MT2bb', 'GeV'],
['Sphericity', 'Sphericity', 'Sphericity'],
['BDTtrijet1', 'trijet1 discriminator', ''],
['FW_momentum_5', '5^{th} FW moment', 'GeV'],
['FW_momentum_4', '4^{th} FW moment', 'GeV'],
['HOTGoodTrijet1_dijetmass', 'HOTGoodTrijet1_dijetmass', 'GeV'],
['HOTGoodTrijet1_dRtridijet', 'HOTGoodTrijet1_dRtridijet', ''],
['HOTGoodTrijet1_mass', 'HOTGoodTrijet1_mass', 'GeV'],
['HOTGoodTrijet1_pTratio', 'HOTGoodTrijet1_pTratio', ''],
['theJetLeadPt', 'p_{T}(j_{1})', 'GeV'],
['HOTGoodTrijet1_dRtrijetJetnotdijet', 'HOTGoodTrijet1_dRtrijetJetnotdijet', ''],
['deltaR_lepBJet_maxpt', '#DeltaR(l,b)] with max[p_{T}(l,b)]', ''],
['FW_momentum_2', '2^{nd} FW moment', 'GeV'],
['mass_lepJets2', 'M(l,j_{3})', 'GeV'],
['lepDR_minBBdr', '#DeltaR(l,bb) with min[#DeltaR(b,b)]', ''],
#['csvJet3', 'DeepCSV(3rdPtJet)', ''],
['mass_lepJets1', 'M(l,j_{2})', 'GeV'],
['BDTtrijet4', 'trijet4 discriminator', ''],
['deltaR_lepbJetInMinMlb', '#DeltaR(l,b) with min M(l, b)', ''],
#['csvJet4', 'DeepCSV(4thPtJet)', ''],
#['aveCSVpt', 'p_{T} weighted CSVv2', ''], #csv
#['HOTGoodTrijet1_csvJetnotdijet', 'HOTGoodTrijet1_csvJetnotdijet', ''],
['FW_momentum_3', '3^{rd} FW moment', 'GeV'],
['FW_momentum_0', '0^{th} FW moment', 'GeV'],
['mass_minBBdr', 'M(b,b) with min[#DeltaR(b,b)]', 'GeV'],
['mass_maxJJJpt', 'M(jjj) with max[p_{T}(jjj)]', 'GeV'],
['minDR_lepBJet', 'min[#DeltaR(l,b)]', ''],
['leptonPt_MultiLepCalc', 'p_{T}(lep)', 'GeV'],
['deltaPhi_lepbJetInMinMlb', '#DeltaPhi(l,b) with min M(l, b)', ''],
['NJetsWtagged', 'W multiplicity', ''],
['mass_minLLdr', 'M(j,j) with min[#DeltaR(j,j)], j #neq b', 'GeV'],
['FW_momentum_1', '1^{st} FW moment', 'GeV'],
['deltaR_lepJetInMinMljet', '#DeltaR(l,j) with min M(l, j)', ''],
['mass_lepJets0', 'M(l,j_{1})', 'GeV'],
['deltaPhi_lepJetInMinMljet', '#DeltaPhi(l,j) with min M(l, j)', '']
]

varList['SepRank6j73vars2017yearother'] = [ # May07 run 
['thirdcsvb_bb', 'DeepCSV(3rdDeepCSVJet)', ''],
['fourthcsvb_bb', 'DeepCSV(4thDeepCSVJet)', ''],
['NJetsCSV_MultiLepCalc', 'bjet multiplicity', ''],
# ['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
['NJets_JetSubCalc', 'AK4 jet multiplicity', ''],
['BDTtrijet2', 'trijet2 discriminator', ''],
['AK4HTpMETpLepPt', 'S_{T}', 'GeV'],
['sixthJetPt', 'p_{T}(j_{6})', 'GeV'],
['PtFifthJet', '5^{th} jet p_{T}', 'GeV'],
['hemiout', 'Hemiout', 'GeV'],
['AK4HT', 'H_{T}', 'GeV'],
['HT_bjets', 'HT(bjets)', 'GeV'],
['BDTtrijet3', 'trijet3 discriminator', ''],
['fifthJetPt', 'p_{T}(j_{5})', 'GeV'],
['ratio_HTdHT4leadjets', 'HT/HT(4 leading jets)', ''],
['MT_lepMet', 'M_{T}(lep,E_{T}^{miss})', 'GeV'],
['HT_2m', 'HTwoTwoPtBjets', 'GeV'],
['mass_maxBBmass', 'max[M(b,b)]', 'GeV'],
['deltaR_minBB', 'min[#DeltaR(b,b)]', ''],
['mass_lepBJet0', 'M(l,b_{1})', 'GeV'],
['NresolvedTops1pFake', 'resolvedTop multiplicity', ''],
['HOTGoodTrijet2_pTratio', 'HOTGoodTrijet2_pTratio', ''],
['HOTGoodTrijet2_mass', 'HOTGoodTrijet2_mass', 'GeV'],
['HOTGoodTrijet2_dijetmass', 'HOTGoodTrijet2_dijetmass', 'GeV'],
['HOTGoodTrijet2_dRtridijet', 'HOTGoodTrijet2_dRtridijet', ''],
['HOTGoodTrijet2_dRtrijetJetnotdijet', 'HOTGoodTrijet2_dRtrijetJetnotdijet', ''],
['mass_lepBJet_mindr', 'M(l,b) with min[#DeltaR(l,b)]', 'GeV'],
['M_allJet_W', 'M(allJets, leptoninc W)', 'GeV'],
['minMleppBjet', 'min[M(l,b)]', 'GeV'],
['corr_met_MultiLepCalc', 'E_{T}^{miss}', 'GeV'],
['BJetLeadPt', 'p_{T}(b_{1})', 'GeV'],
['NJetsTtagged', 'top multiplicity', ''],
['secondJetPt', 'p_{T}(j_{2})', 'GeV'],
['aveBBdr', 'ave[#DeltaR(b,b)]', ''],
['FW_momentum_6', '6^{th} FW moment', 'GeV'],
['deltaEta_maxBB', 'max[#Delta#eta(b,b)]', ''],
['HOTGoodTrijet2_csvJetnotdijet', 'HOTGoodTrijet2_csvJetnotdijet', ''],
['centrality', 'Centrality', ''],
['Aplanarity', 'Aplanarity', 'Aplanarity'],
['MT2bb', 'MT2bb', 'GeV'],
['Sphericity', 'Sphericity', 'Sphericity'],
['BDTtrijet1', 'trijet1 discriminator', ''],
['FW_momentum_5', '5^{th} FW moment', 'GeV'],
['FW_momentum_4', '4^{th} FW moment', 'GeV'],
['HOTGoodTrijet1_dijetmass', 'HOTGoodTrijet1_dijetmass', 'GeV'],
['HOTGoodTrijet1_dRtridijet', 'HOTGoodTrijet1_dRtridijet', ''],
['HOTGoodTrijet1_mass', 'HOTGoodTrijet1_mass', 'GeV'],
['HOTGoodTrijet1_pTratio', 'HOTGoodTrijet1_pTratio', ''],
['theJetLeadPt', 'p_{T}(j_{1})', 'GeV'],
['HOTGoodTrijet1_dRtrijetJetnotdijet', 'HOTGoodTrijet1_dRtrijetJetnotdijet', ''],
['deltaR_lepBJet_maxpt', '#DeltaR(l,b)] with max[p_{T}(l,b)]', ''],
['FW_momentum_2', '2^{nd} FW moment', 'GeV'],
['mass_lepJets2', 'M(l,j_{3})', 'GeV'],
['lepDR_minBBdr', '#DeltaR(l,bb) with min[#DeltaR(b,b)]', ''],
['csvJet3', 'DeepCSV(3rdPtJet)', ''],
['mass_lepJets1', 'M(l,j_{2})', 'GeV'],
['BDTtrijet4', 'trijet4 discriminator', ''],
['deltaR_lepbJetInMinMlb', '#DeltaR(l,b) with min M(l, b)', ''],
['csvJet4', 'DeepCSV(4thPtJet)', ''],
['aveCSVpt', 'p_{T} weighted CSVv2', ''], #csv
['HOTGoodTrijet1_csvJetnotdijet', 'HOTGoodTrijet1_csvJetnotdijet', ''],
['FW_momentum_3', '3^{rd} FW moment', 'GeV'],
['FW_momentum_0', '0^{th} FW moment', 'GeV'],
['mass_minBBdr', 'M(b,b) with min[#DeltaR(b,b)]', 'GeV'],
['mass_maxJJJpt', 'M(jjj) with max[p_{T}(jjj)]', 'GeV'],
['minDR_lepBJet', 'min[#DeltaR(l,b)]', ''],
['leptonPt_MultiLepCalc', 'p_{T}(lep)', 'GeV'],
['deltaPhi_lepbJetInMinMlb', '#DeltaPhi(l,b) with min M(l, b)', ''],
['NJetsWtagged', 'W multiplicity', ''],
['mass_minLLdr', 'M(j,j) with min[#DeltaR(j,j)], j #neq b', 'GeV'],
['FW_momentum_1', '1^{st} FW moment', 'GeV'],
['deltaR_lepJetInMinMljet', '#DeltaR(l,j) with min M(l, j)', ''],
['mass_lepJets0', 'M(l,j_{1})', 'GeV'],
['deltaPhi_lepJetInMinMljet', '#DeltaPhi(l,j) with min M(l, j)', '']
]


varList['ImpRank6j73vars2017year'] = [
]

varList['SepRank6j61vars2017year'] = [ # Mar30 run 

]

## 2018 
varList['SepRank6j73vars2018year'] = [ #Mar30 run
]

varList['ImpRank6j73vars2018year'] = [
]

varList['SepRank6j61vars2018year'] = [ #Mar30 run
]


varList['DNNRank6j73vars2017year'] = [ # Daniel Apr13 
['fourthcsvb_bb', 'DeepCSV(4thDeepCSVJet)', ''],
['MT_lepMet', 'M_{T}(lep,E_{T}^{miss})', 'GeV'],
['thirdcsvb_bb', 'DeepCSV(3rdDeepCSVJet)', ''],
['corr_met_MultiLepCalc', 'E_{T}^{miss}', 'GeV'],
['BDTtrijet2', 'trijet2 discriminator', ''],
['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
['MT2bb', 'MT2bb', 'GeV'],
['mass_lepBJet_mindr', 'M(l,b) with min[#DeltaR(l,b)]', 'GeV'],
['BDTtrijet3', 'trijet3 discriminator', ''],
['AK4HTpMETpLepPt', 'S_{T}', 'GeV'],
['hemiout', 'Hemiout', 'GeV'],
['FW_momentum_1', '1^{st} FW moment', 'GeV'],
['HT_bjets', 'HT(bjets)', 'GeV'],
['Sphericity', 'Sphericity', 'Sphericity'],
['centrality', 'Centrality', ''],
['theJetLeadPt', 'p_{T}(j_{1})', 'GeV'],
['minMleppBjet', 'min[M(l,b)]', 'GeV'],
['PtFifthJet', '5^{th} jet p_{T}', 'GeV'],
['Aplanarity', 'Aplanarity', 'Aplanarity'],
['HOTGoodTrijet2_dijetmass', 'HOTGoodTrijet2_dijetmass', 'GeV'],
['mass_maxJJJpt', 'M(jjj) with max[p_{T}(jjj)]', 'GeV'],
['NJetsTtagged', 'top multiplicity', ''],
['mass_lepBJet0', 'M(l,b_{1})', 'GeV'],
['sixthJetPt', 'p_{T}(j_{6})', 'GeV'],
['BDTtrijet1', 'trijet1 discriminator', ''],
['NJets_JetSubCalc', 'AK4 jet multiplicity', ''],
['minDR_lepBJet', 'min[#DeltaR(l,b)]', ''],
['aveBBdr', 'ave[#DeltaR(b,b)]', ''],
['deltaR_lepbJetInMinMlb', '#DeltaR(l,b) with min M(l, b)', ''],
['aveCSVpt', 'p_{T} weighted CSVv2', ''],
['FW_momentum_6', '6^{th} FW moment', 'GeV'],
['deltaR_lepBJet_maxpt', '#DeltaR(l,b)] with max[p_{T}(l,b)]', ''],
['HOTGoodTrijet2_dRtridijet', 'HOTGoodTrijet2_dRtridijet', ''],
['M_allJet_W', 'M(allJets, leptoninc W)', 'GeV'],
['mass_maxBBmass', 'max[M(b,b)]', 'GeV'],
['HT_2m', 'HTwoTwoPtBjets', 'GeV'],
['NresolvedTops1pFake', 'resolvedTop multiplicity', ''],
['BJetLeadPt', 'p_{T}(b_{1})', 'GeV'],
['HOTGoodTrijet2_dRtrijetJetnotdijet', 'HOTGoodTrijet2_dRtrijetJetnotdijet', ''],
['mass_lepJets0', 'M(l,j_{1})', 'GeV'],
['ratio_HTdHT4leadjets', 'HT/HT(4 leading jets)', ''],
['HOTGoodTrijet1_dRtrijetJetnotdijet', 'HOTGoodTrijet1_dRtrijetJetnotdijet', ''],
['BDTtrijet4', 'trijet4 discriminator', ''],
['mass_minBBdr', 'M(b,b) with min[#DeltaR(b,b)]', 'GeV'],
['HOTGoodTrijet1_dRtridijet', 'HOTGoodTrijet1_dRtridijet', ''],
['deltaR_lepJetInMinMljet', '#DeltaR(l,j) with min M(l, j)', ''],
['NJetsWtagged', 'W multiplicity', ''],
['secondJetPt', 'p_{T}(j_{2})', 'GeV'],
['lepDR_minBBdr', '#DeltaR(l,bb) with min[#DeltaR(b,b)]', ''],
['HOTGoodTrijet2_mass', 'HOTGoodTrijet2_mass', 'GeV'],
['HOTGoodTrijet2_csvJetnotdijet', 'HOTGoodTrijet2_csvJetnotdijet', ''],
['HOTGoodTrijet1_pTratio', 'HOTGoodTrijet1_pTratio', ''],
['HOTGoodTrijet1_mass', 'HOTGoodTrijet1_mass', 'GeV'],
['HOTGoodTrijet2_pTratio', 'HOTGoodTrijet2_pTratio', ''],
['deltaR_minBB', 'min[#DeltaR(b,b)]', ''],
['mass_minLLdr', 'M(j,j) with min[#DeltaR(j,j)], j #neq b', 'GeV'],
['fifthJetPt', 'p_{T}(j_{5})', 'GeV'],
['leptonPt_MultiLepCalc', 'p_{T}(lep)', 'GeV'],
['FW_momentum_5', '5^{th} FW moment', 'GeV'],
['csvJet3', 'DeepCSV(3rdPtJet)', ''],
['AK4HT', 'H_{T}', 'GeV'],
['FW_momentum_2', '2^{nd} FW moment', 'GeV'],
['deltaPhi_lepbJetInMinMlb', '#DeltaPhi(l,b) with min M(l, b)', ''],
['FW_momentum_4', '4^{th} FW moment', 'GeV'],
['mass_lepJets2', 'M(l,j_{3})', 'GeV'],
['HOTGoodTrijet1_csvJetnotdijet', 'HOTGoodTrijet1_csvJetnotdijet', ''],
['mass_lepJets1', 'M(l,j_{2})', 'GeV'],
['HOTGoodTrijet1_dijetmass', 'HOTGoodTrijet1_dijetmass', 'GeV'],
['deltaPhi_lepJetInMinMljet', '#DeltaPhi(l,j) with min M(l, j)', ''],
['FW_momentum_3', '3^{rd} FW moment', 'GeV'],
['deltaEta_maxBB', 'max[#Delta#eta(b,b)]', ''],
['csvJet4', 'DeepCSV(4thPtJet)', ''],
['FW_momentum_0', '0^{th} FW moment', 'GeV']
]

varList['DNNRank6j73vars2018year'] = [
['BJetLeadPt', 'p_{T}(b_{1})', 'GeV'],
['thirdcsvb_bb', 'DeepCSV(3rdDeepCSVJet)', ''],
['BDTtrijet2', 'trijet2 discriminator', ''],
['BDTtrijet3', 'trijet3 discriminator', ''],
['AK4HT', 'H_{T}', 'GeV'],
['NJetsCSVwithSF_MultiLepCalc', 'bjet multiplicity', ''],
['mass_lepJets2', 'M(l,j_{3})', 'GeV'],
['M_allJet_W', 'M(allJets, leptoninc W)', 'GeV'],
['minDR_lepBJet', 'min[#DeltaR(l,b)]', ''],
['mass_lepJets0', 'M(l,j_{1})', 'GeV'],
['sixthJetPt', 'p_{T}(j_{6})', 'GeV'],
['BDTtrijet1', 'trijet1 discriminator', ''],
['secondJetPt', 'p_{T}(j_{2})', 'GeV'],
['theJetLeadPt', 'p_{T}(j_{1})', 'GeV'],
['MT2bb', 'MT2bb', 'GeV'],
['lepDR_minBBdr', '#DeltaR(l,bb) with min[#DeltaR(b,b)]', ''],
['deltaPhi_lepbJetInMinMlb', '#DeltaPhi(l,b) with min M(l, b)', ''],
['HOTGoodTrijet2_pTratio', 'HOTGoodTrijet2_pTratio', ''],
['deltaR_minBB', 'min[#DeltaR(b,b)]', ''],
['AK4HTpMETpLepPt', 'S_{T}', 'GeV'],
['HOTGoodTrijet1_pTratio', 'HOTGoodTrijet1_pTratio', ''],
['mass_minBBdr', 'M(b,b) with min[#DeltaR(b,b)]', 'GeV'],
['HOTGoodTrijet2_csvJetnotdijet', 'HOTGoodTrijet2_csvJetnotdijet', ''],
['BDTtrijet4', 'trijet4 discriminator', ''],
['centrality', 'Centrality', ''],
['HOTGoodTrijet2_dRtrijetJetnotdijet', 'HOTGoodTrijet2_dRtrijetJetnotdijet', ''],
['FW_momentum_6', '6^{th} FW moment', 'GeV'],
['FW_momentum_4', '4^{th} FW moment', 'GeV'],
['MT_lepMet', 'M_{T}(lep,E_{T}^{miss})', 'GeV'],
['aveCSVpt', 'p_{T} weighted CSVv2', ''],
['HOTGoodTrijet1_dRtridijet', 'HOTGoodTrijet1_dRtridijet', ''],
['Sphericity', 'Sphericity', 'Sphericity'],
['mass_lepJets1', 'M(l,j_{2})', 'GeV'],
['HT_bjets', 'HT(bjets)', 'GeV'],
['HT_2m', 'HTwoTwoPtBjets', 'GeV'],
['NJetsTtagged', 'top multiplicity', ''],
['csvJet3', 'DeepCSV(3rdPtJet)', ''],
['deltaR_lepBJet_maxpt', '#DeltaR(l,b)] with max[p_{T}(l,b)]', ''],
['mass_maxJJJpt', 'M(jjj) with max[p_{T}(jjj)]', 'GeV'],
['FW_momentum_5', '5^{th} FW moment', 'GeV'],
['HOTGoodTrijet2_dRtridijet', 'HOTGoodTrijet2_dRtridijet', ''],
['csvJet4', 'DeepCSV(4thPtJet)', ''],
['HOTGoodTrijet1_csvJetnotdijet', 'HOTGoodTrijet1_csvJetnotdijet', ''],
['fifthJetPt', 'p_{T}(j_{5})', 'GeV'],
['HOTGoodTrijet1_dRtrijetJetnotdijet', 'HOTGoodTrijet1_dRtrijetJetnotdijet', ''],
['deltaR_lepbJetInMinMlb', '#DeltaR(l,b) with min M(l, b)', ''],
['HOTGoodTrijet2_mass', 'HOTGoodTrijet2_mass', 'GeV'],
['fourthcsvb_bb', 'DeepCSV(4thDeepCSVJet)', ''],
['FW_momentum_2', '2^{nd} FW moment', 'GeV'],
['ratio_HTdHT4leadjets', 'HT/HT(4 leading jets)', ''],
['mass_maxBBmass', 'max[M(b,b)]', 'GeV'],
['leptonPt_MultiLepCalc', 'p_{T}(lep)', 'GeV'],
['HOTGoodTrijet2_dijetmass', 'HOTGoodTrijet2_dijetmass', 'GeV'],
['mass_lepBJet_mindr', 'M(l,b) with min[#DeltaR(l,b)]', 'GeV'],
['FW_momentum_1', '1^{st} FW moment', 'GeV'],
['aveBBdr', 'ave[#DeltaR(b,b)]', ''],
['NJets_JetSubCalc', 'AK4 jet multiplicity', ''],
['minMleppBjet', 'min[M(l,b)]', 'GeV'],
['Aplanarity', 'Aplanarity', 'Aplanarity'],
['FW_momentum_3', '3^{rd} FW moment', 'GeV'],
['NresolvedTops1pFake', 'resolvedTop multiplicity', ''],
['HOTGoodTrijet1_mass', 'HOTGoodTrijet1_mass', 'GeV'],
['deltaEta_maxBB', 'max[#Delta#eta(b,b)]', ''],
['PtFifthJet', '5^{th} jet p_{T}', 'GeV'],
['mass_minLLdr', 'M(j,j) with min[#DeltaR(j,j)], j #neq b', 'GeV'],
['corr_met_MultiLepCalc', 'E_{T}^{miss}', 'GeV'],
['mass_lepBJet0', 'M(l,b_{1})', 'GeV'],
['deltaPhi_lepJetInMinMljet', '#DeltaPhi(l,j) with min M(l, j)', ''],
['NJetsWtagged', 'W multiplicity', ''],
['hemiout', 'Hemiout', 'GeV'],
['HOTGoodTrijet1_dijetmass', 'HOTGoodTrijet1_dijetmass', 'GeV'],
['FW_momentum_0', '0^{th} FW moment', 'GeV'],
['deltaR_lepJetInMinMljet', '#DeltaR(l,j) with min M(l, j)', '']
]


for ind in range(20, 73, 1):
  varList['SepRank6j73vars2017year'+ str(ind)+ 'top'] = varList['SepRank6j73vars2017year'][:ind]
  varList['SepRank6j73vars2018year'+ str(ind)+ 'top'] = varList['SepRank6j73vars2018year'][:ind]
  varList['SepRank4j73vars2017year'+ str(ind)+ 'top'] = varList['SepRank4j73vars2017year'][:ind]
  varList['DNNRank6j73vars2017year'+ str(ind)+ 'top'] = varList['DNNRank6j73vars2017year'][:ind]
  varList['DNNRank6j73vars2018year'+ str(ind)+ 'top'] = varList['DNNRank6j73vars2018year'][:ind]
  varList['ImpRank6j73vars2017year'+ str(ind)+ 'top'] = varList['ImpRank6j73vars2017year'][:ind]
  varList['ImpRank6j73vars2018year'+ str(ind)+ 'top'] = varList['ImpRank6j73vars2018year'][:ind]

for ind in range(20, 61, 1):
  varList['SepRank6j61vars2017year'+ str(ind)+ 'top'] = varList['SepRank6j61vars2017year'][:ind]
  varList['SepRank6j61vars2018year'+ str(ind)+ 'top'] = varList['SepRank6j61vars2018year'][:ind]
  varList['SepRank4j61vars2017year'+ str(ind)+ 'top'] = varList['SepRank4j61vars2017year'][:ind]

varList['Comb61andtrij'] += varList['CombIpRank']
