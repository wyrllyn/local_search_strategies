#!/bin/sh

UNPARAMETRE="1 2 3 4 5 6 7 8 9"

for I in `ls instances_50` ; do
for J in $UNPARAMETRE ; do
qsub -cwd -pe param 1 run.sh $I $J
done;
done;
