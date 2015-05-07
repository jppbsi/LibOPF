#!/bin/sh

echo "This is an example of how to use the unsupervised OPF classifier."

# executing and evaluating the unsupervised OPF

#splitting dataset into training and test sets with, respectively, 80%
#and 20% of the samples each one without features normalization. Then
#computing example for k=100, removing maxima whose dome area (P2=1) is
#below 20% of the total number of nodes. It also creates a classifier
#by assigning the true label of the root node to the remaining nodes
#of its optimum-path tree (cluster), then evaluates the accuracy of
#this classification on the test set.

../bin/opf_split   ../data/data1.dat 0.8 0.0 0.2 0
../bin/opf_cluster training.dat 100 1 0.2
../bin/opf_knn_classify testing.dat 
../bin/opf_accuracy testing.dat 

#splitting dataset into training and test sets with, respectively, 80%
#and 20% of the samples each one without features normalization. Then
#computing example using k=100, removing maxima whose dome volume (P2=2) is
#below 1% of the pdf volume. It also creates a classifier by assigning
#the true label of the root node to the remaining nodes of its
#optimum-path tree (cluster), then evaluates the accuracy of this
#classification.

../bin/opf_split   ../data/data2.dat 0.8 0.0 0.2 0
../bin/opf_cluster training.dat 100 2 0.01
../bin/opf_knn_classify testing.dat 
../bin/opf_accuracy testing.dat 

#splitting dataset into training and test sets with, respectively, 80%
#and 20% of the samples each one without features normalization. Then
#computing example using k=20, removing maxima whose dome volume (P2=2) is
#below 0.1% of the pdf volume. It also creates a classifier by
#assigning the true label of the root node to the remaining nodes of
#its optimum-path tree (cluster), then evaluates the accuracy of this
#classification.

../bin/opf_split   ../data/data3.dat 0.8 0.0 0.2 0
../bin/opf_cluster training.dat 20 2 0.001
../bin/opf_knn_classify testing.dat 
../bin/opf_accuracy testing.dat 

#splitting dataset into training and test sets with, respectively, 80%
#and 20% of the samples each one without features normalization. Then
#computing example using k=100, removing maxima whose dome volume (P2=2) is
#below 2% of the pdf volume. It also creates a classifier by assigning
#the true label of the root node to the remaining nodes of its
#optimum-path tree (cluster), then evaluates the accuracy of this
#classification.

../bin/opf_split   ../data/data4.dat 0.8 0.0 0.2 0
../bin/opf_cluster training.dat 100 2 0.02
../bin/opf_knn_classify testing.dat 
../bin/opf_accuracy testing.dat

#splitting dataset into training and test sets with, respectively, 80%
#and 20% of the samples each one without features normalization. Then
#computing example using k=50, removing maxima whose dome area (P2=1)
#is below 20% of the total number of nodes. It also creates a
#classifier by assigning the true label of the root node to the
#remaining nodes of its optimum-path tree (cluster), then evaluates
#the accuracy of this classification.

../bin/opf_split   ../data/data5.dat 0.8 0.0 0.2 0
../bin/opf_cluster training.dat 50 1 0.2
../bin/opf_knn_classify testing.dat 
../bin/opf_accuracy testing.dat 
