 #!/bin/bash
 # nominal 2017 73 4
#  /mnt/hadoop/store/group/bruxljm/FWLJMET102X_1lep2017_Oct2019_4t_04082021_step3_40vars_6j_NJetsCSV_v1
tag3=FWLJMET102X_1lep$1_Oct2019_4t_04082021_step3_$2vars_$3j_NJetsCSV_v1
tag2=FWLJMET102X_1lep$1_Jan2021_4t_051321_step2
tag1=FWLJMET102X_1lep$1_Jan2021_4t_051321_step1hadds/
ls -lh /mnt/hadoop/store/group/bruxljm/$tag1/nominal/ | wc -l
ls -lh /mnt/hadoop/store/group/bruxljm/$tag1/JECup/ | wc -l
ls -lh /mnt/hadoop/store/group/bruxljm/$tag1/JECdown/ | wc -l
ls -lh /mnt/hadoop/store/group/bruxljm/$tag1/JERup/ | wc -l
ls -lh /mnt/hadoop/store/group/bruxljm/$tag1/JERdown/ | wc -l
