#!/bin/sh

echo "This is an example of how to use the OPF classifier with learning procedure."

#splitting dataset into training, evaluating and test sets with, respectively, 30%, 20% and 50% of the samples each one without features normalization
../bin/opf_split  ../data/boat.dat 0.3 0.2 0.5 0

#executing the OPF learning procedure
../bin/opf_learn training.dat evaluating.dat

#classifying the test set
../bin/opf_classify testing.dat

# computing the accuracy over the test set
../bin/opf_accuracy testing.dat
