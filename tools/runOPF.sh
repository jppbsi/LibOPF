#!/bin/bash

#P1: dataset file name
#P2: percentage for the training set size [0,1]
#P3: percentage for the test set size [0,1]
#P4: normalize features? 1 - Yes  0 - No
#P5: running times

if [ "$#" -eq "5" ]; then
	clear

	for ((it = 1; it <= $5; it++))
	do
		echo "Running iteration "$it

		sleep 4

		#generating sets *****
		../bin/opf_split $1 $2 0 $3 $4

		#executing supervised OPF
		../bin/opf_train training.dat
		../bin/opf_classify testing.dat
		../bin/opf_accuracy testing.dat

	done

	./statistics  testing.dat.acc $5 "Supervised OPF mean accuracy"
	./statistics  training.dat.time $5 "Supervised OPF mean training phase execution time (s)"
	./statistics  testing.dat.time $5 "Supervised OPF mean test phase execution time (s)"

	rm training.dat testing.dat classifier.opf *.acc *.time
else
	echo "Script that executes the supervised OPF"
	echo "P1: dataset file name"
	echo "P2: percentage for the training set size [0,1]"
	echo "P3: percentage for the test set size [0,1]"
	echo "P4: normalize features? 1 - Yes  0 - No"
	echo "P5: running times"
fi
