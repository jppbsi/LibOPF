#!/bin/sh

echo "This is an example of how to use the OPF classifier without learning procedure."

#splitting dataset into training and test sets with 50% of the samples each one without features normalization
../bin/opf_split  ../data/boat.dat 0.5 0 0.5 0

#training OPF classifier
../bin/opf_train training.dat

#classifying the test set
../bin/opf_classify testing.dat

# computing the accuracy over the test set
../bin/opf_accuracy testing.dat
