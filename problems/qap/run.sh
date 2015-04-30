#!/bin/sh

for SEED in $(seq 100 199); do
./program instances/$1 $2 $SEED
done;
