#!/bin/sh

UNPARAMETRE="11 13 14 15"

for I in `ls instances` ; do
for J in $UNPARAMETRE ; do
qsub -cwd -pe param 1 run.sh $I $J
done;
done;
