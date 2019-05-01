import sys, os

fileList =[
    'CorrelationMatrixB',
    'effBvsS',
    'mvaeffs_BDT',    
    'rejBvsS',          
    'variables_id_c2',  
    'variables_id_c4',  
    'variables_id_c6',  
    'variables_id_c8',
    'CorrelationMatrixS',  
    'mva_BDT',  
    'overtrain_BDT',  
    'variables_id_c1',  
    'variables_id_c3',  
    'variables_id_c5', 
    'variables_id_c7',  
    'variables_id_c9'
]

for list in fileList:
    os.system("convert -density 300 "+list+".eps -resize 1024x1024 "+list+".png")