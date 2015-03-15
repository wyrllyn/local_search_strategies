#!/bin/sh

for var in $(seq 96 100);
do 
	echo $var
	time ./program qapdata/tai50b.dat

done


exit 0;