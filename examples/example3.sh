#!/bin/sh

echo "This is an example of how to use the OPF classifier without learning procedure and with precomputed distances."

# Generating the precomputed distances for cone-torus dataset, with Manhattan distance (ID 3) and without
# distance normalization (parameter 0 at the final of the command line)
../bin/opf_distance ../data/cone-torus.dat 3 0

#splitting dataset into training, evaluating and test sets with, respectively, 30%, 20% and 50% of the samples each one without features normalization
../bin/opf_split  ../data/cone-torus.dat 0.5 0 0.5 0

#executing the OPF learning procedure
../bin/opf_train training.dat distances.dat

#classifying the test set
../bin/opf_classify testing.dat distances.dat

# computing the accuracy over the test set
../bin/opf_accuracy testing.dat
