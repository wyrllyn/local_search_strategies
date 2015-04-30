#!/bin/sh

for J in `ls instances` ; do
	#for I in $(seq 19); do
		for SEED in $(seq 100 199); do
		./program instances/$J 19 $SEED
	#	done;
	done;
done;