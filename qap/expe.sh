#!/bin/sh

UNPARAMETRE="5 6"

for I in `ls instances` ; do
for J in $UNPARAMETRE ; do
qsub -cwd -pe param 1 run.sh $I $J
done;
done;
