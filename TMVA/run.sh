#!/bin/bash
python doCondorApplication.py nominal $1 $2 $3 $4
sleep 1
python doCondorApplication.py JECup $1 $2 $3 $4
sleep 1
python doCondorApplication.py JECdown $1 $2 $3 $4
sleep 1
python doCondorApplication.py JERup $1 $2 $3 $4
sleep 1
python doCondorApplication.py JERdown $1 $2 $3 $4
