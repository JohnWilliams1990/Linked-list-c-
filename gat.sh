#!/bin/bash
#  John Williams
#  105201054
#  Date: Sat. Oct. 6, 2018
#  Program: gat.sh


echo "git add * ; git commit -m '$@' ; git pull origin pcb ; git push origin pcb"
git add * ; git commit -m '$@' ; git pull origin pcb ; git push origin pcb


