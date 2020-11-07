#!/bin/bash
python doCondorApplication.py nominal $1 $2 $3
sleep 60
python doCondorApplication.py JECup $1 $2 $3
sleep 60
python doCondorApplication.py JECdown $1 $2 $3
sleep 60
python doCondorApplication.py JERup $1 $2 $3
sleep 60
python doCondorApplication.py JERdown $1 $2 $3
