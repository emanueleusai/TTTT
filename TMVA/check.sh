 #!/bin/bash
 # nominal 2017 73 4
 tag=FWLJMET102X_1lep$1_Oct2019_4t_11072020_step3_$2vars_$3j
 ls -lh /mnt/hadoop/store/group/bruxljm/$tag/nominal/ | wc -l
 ls -lh /mnt/hadoop/store/group/bruxljm/$tag/JECup/ | wc -l
 ls -lh /mnt/hadoop/store/group/bruxljm/$tag/JECdown/ | wc -l
 ls -lh /mnt/hadoop/store/group/bruxljm/$tag/JERup/ | wc -l
 ls -lh /mnt/hadoop/store/group/bruxljm/$tag/JERdown/ | wc -l
