#!/bin/sh

UNPARAMETRE="8 9 11 12 13"

for I in `ls instances` ; do
for J in $UNPARAMETRE ; do
qsub -cwd -pe param 1 run.sh $I $J
done;
done;
