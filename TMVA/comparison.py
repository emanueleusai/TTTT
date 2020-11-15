import ROOT as r, math as m #needs 6.14 or greater
r.gROOT.SetBatch()

intcolor=[r.TColor.GetColor(i) for i in ["#1f77b4", "#ff7f0e", "#2ca02c", "#d62728", "#9467bd", "#8c564b", "#e377c2", "#7f7f7f", "#bcbd22", "#17becf"]]
def compare(name,file_list,name_list,legend_list,normalize=False,drawoption='hE',xtitle='',ytitle='',minx=0,maxx=0,rebin=1,miny=0,maxy=0,textsizefactor=1,logy=False):
  c=r.TCanvas(name,'',600,600)
  c.SetLeftMargin(0.15)#
  c.SetRightMargin(0.05)#
  c.SetBottomMargin(0.11)
  c.SetTopMargin(0.25)
  legend=r.TLegend(0.0,0.76,0.99,1.04)
  legend.SetHeader('')
  legend.SetBorderSize(0)
  legend.SetTextFont(42)
  legend.SetLineColor(1)
  legend.SetLineStyle(1)
  legend.SetLineWidth(1)
  legend.SetFillColor(0)
  legend.SetFillStyle(0)
  histo_list=[]
  the_maxy=0
  for i in range(len(name_list)):
    histo_list.append(file_list[i].Get(name_list[i]).Clone(name_list[i]+'_'+str(i)))
    if normalize:
      histo_list[-1].Scale(1.0/(histo_list[-1].Integral()+0.00000001))
    histo_list[-1].SetStats(0)
    histo_list[-1].SetLineWidth(3)
    histo_list[-1].SetLineColor(intcolor[i])
    histo_list[-1].SetTitle('')
    if rebin!=1:
      histo_list[-1].Rebin(rebin)
    the_maxy=max(the_maxy,histo_list[-1].GetBinContent(histo_list[-1].GetMaximumBin())*1.05)
    legend.AddEntry(histo_list[-1],legend_list[i],'l')
  for i in range(len(name_list)):
    if i==0:
      if miny!=0 or maxy!=0:
        histo_list[i].SetMaximum(maxy)
        histo_list[i].SetMinimum(miny)
      else:
        histo_list[i].SetMaximum(the_maxy)
        #histo_list[i].SetMinimum(0.0001)
      histo_list[i].Draw(drawoption)
      charsize=0.05*textsizefactor
      histo_list[i].GetYaxis().SetLabelSize(charsize)
      histo_list[i].GetYaxis().SetTitleSize(charsize)
      histo_list[i].GetYaxis().SetTitleOffset(1.6)
      histo_list[i].GetXaxis().SetLabelSize(charsize)
      histo_list[i].GetXaxis().SetTitleSize(charsize)
      histo_list[i].GetXaxis().SetTitleOffset(0.95)
      if xtitle!='':
        histo_list[i].GetXaxis().SetTitle(xtitle)
      if ytitle!='':  
        histo_list[i].GetYaxis().SetTitle(ytitle)
      if maxx!=0 or minx!=0:
        histo_list[i].GetXaxis().SetRangeUser(minx,maxx)
    else:
      histo_list[i].Draw(drawoption+'SAME')
  if logy:
    c.SetLogy()
  legend.Draw()
  c.SaveAs('pdf/'+name+'.pdf')

outfile=r.TFile('comparison.root','recreate')

filenames={

'40v_4j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year40top_40vars_mDepth2_4j_year2017.root',
'40v_4j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year40top_40vars_mDepth2_4j_year2018.root',
'40v_6j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year40top_40vars_mDepth2_6j_year2017.root',
'40v_6j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year40top_40vars_mDepth2_6j_year2018.root',
'50v_4j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year50top_50vars_mDepth2_4j_year2017.root',
'50v_4j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year50top_50vars_mDepth2_4j_year2018.root',
'50v_6j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year50top_50vars_mDepth2_6j_year2017.root',
'50v_6j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year50top_50vars_mDepth2_6j_year2018.root',
'73v_4j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year_73vars_mDepth2_4j_year2017.root',
'73v_4j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year_73vars_mDepth2_4j_year2018.root',
'73v_6j_y17' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year_73vars_mDepth2_6j_year2017.root',
'73v_6j_y18' : 'dataset2020/weights/TMVA_BDT_SepRank6j73vars2017year_73vars_mDepth2_6j_year2018.root',
}

files={}
for key in filenames:
	files[key]=r.TFile(filenames[key],'r')

plots={

'effS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_effS',
'effB' : 'dataset2020/Method_BDT/BDT/MVA_BDT_effB',
'effBvsS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_effBvsS',
'rejBvsS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_rejBvsS',
'invBeffvsSeff' : 'dataset2020/Method_BDT/BDT/MVA_BDT_invBeffvsSeff',
'trainingRejBvsS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_trainingRejBvsS',
'trainingEffS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_trainingEffS',
'trainingEffB' : 'dataset2020/Method_BDT/BDT/MVA_BDT_trainingEffB',
'trainingEffBvsS' : 'dataset2020/Method_BDT/BDT/MVA_BDT_trainingEffBvsS',

}

U='_'
C=','
R='\n'

for key in files:
	compare(key+U+'TestVsTrain',textsizefactor=0.7,
		normalize= False,
		file_list=[files[key],files[key]],legend_list=['Test','Training'],name_list=[plots['rejBvsS'],plots['trainingRejBvsS']],
		drawoption= '')

print 'training'+C+"AUC"

keys=[k for k in files]
keys.sort()

for key in keys:
	tmp=files[key].Get(plots['rejBvsS']).Clone()
	print key+C+str(tmp.Integral())

for num in ['40v','50v','73v','y17','y18','4j','6j']:
	keys_num=[k for k in keys if num in k]
	# rm=''
	# if 'v' in num:
	# 	rm=num+U
	# if 'y' in num:
	# 	rm=U+num
	# if 'j' in num:
	# 	rm=num+U 
	compare(key+U+num,textsizefactor=0.7,
		normalize= False,
		file_list=[files[k] for k in keys_num],legend_list=keys_num,name_list=[plots['rejBvsS']]*len(keys_num),
		drawoption= '')



	# compare(name=i[0]+'_comp',textsizefactor=0.7,
	# 	normalize= (not (i[1]=='TProfile')) and ('rms' not in i[0]),
	# 	file_list=[f['fullsim'],f['delphes']],legend_list=['Full Sim','Delphes'],name_list=[i[0]]*2,
	# 	drawoption= 'hist' if 'over' in i[0] or 'rms' in i[0] else '')
