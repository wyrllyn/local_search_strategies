#!bin/bash/

#for each instances
#for I in `ls instances` ; do
	#for each methods
	for J in $(seq 10 13); do 
		for K in `ls res/$J/` ; do
			echo $K
			#get last line
			#$tmp tail -2 $I/$J/$K
			for line in $(cat res/$J/$K); do 
				echo $line
			done 
			echo $line >> /home/aku/Dropbox/stage/tai10a.dat.$J.res.txt
			#get cost into line
			#add into file (into z-results_files)
			done;
	done;	
#done;

