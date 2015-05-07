#!/bin/bash

#P1: dataset file name
#P2: percentage for the training set size [0,1]
#P3: percentage for the evaluation set size [0,1]
#P4: percentage for the test set size [0,1]
#P5: normalize features? 1 - Yes  0 - No
#P6: running times

if [ "$#" -eq "6" ]; then
	clear

	for ((it = 1; it <= $6; it++))
	do
		echo "Running iteration "$it

		sleep 1

		#generating sets *****
		../bin/opf_split $1 $2 $3 $4 $5

		#executing supervised OPF without learning
		../bin/opf_train training.dat
		../bin/opf_classify testing.dat
		../bin/opf_accuracy testing.dat

		#renaming files
		cp training.dat training.learning.dat
		cp testing.dat testing.learning.dat

		#executing supervised OPF with learning
		../bin/opf_learn training.learning.dat evaluating.dat
		../bin/opf_classify testing.learning.dat
		../bin/opf_accuracy testing.learning.dat

	done

	echo -e "\n\nOPF results without learning ----------------------------"
	./statistics  testing.dat.acc $6 "Supervised OPF mean accuracy"
	./statistics  training.dat.time $6 "Supervised OPF mean training phase execution time (s)"
	./statistics  testing.dat.time $6 "Supervised OPF mean test phase execution time (s)"

	echo -e "\n\nOPF results with learning ----------------------------"
	./statistics  testing.learning.dat.acc $6 "Supervised OPF mean accuracy"
	./statistics  training.learning.dat.time $6 "Supervised OPF mean learning phase execution time (s)"
	./statistics  testing.learning.dat.time $6 "Supervised OPF mean test phase execution time (s)"

	rm training.dat evaluating.dat testing.dat training.learning.dat testing.learning.dat classifier.opf #*.acc *.time
else
	echo "Script that executes the supervised OPF"
	echo "P1: dataset file name"
	echo "P2: percentage for the training set size [0,1]"
	echo "P3: percentage for the evaluation set size [0,1]"
	echo "P4: percentage for the test set size [0,1]"
	echo "P5: normalize features? 1 - Yes  0 - No"
	echo "P6: running times"
fi
