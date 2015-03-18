#!/bin/sh

UNPARAMETRE="1 2"

for I in `ls instances` ; do
for J in $UNPARAMETRE ; do
qsub -cwd -pe param 1 -t 100-199 run.sh $I $J
done;
done;
