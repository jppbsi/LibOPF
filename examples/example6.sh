#!/bin/sh

echo "This is an example of how to use the OPF classifier with semi supervised learning procedure."

#splitting dataset into training, evaluating and test sets with, respectively, 30%, 20% and 50% of the samples each one without features normalization
../bin/opf_split  ../data/saturn.dat 0.6 0.2 0.2 0
cp training.dat Z1.dat
cp testing.dat Z3.dat
rm training.dat
rm testing.dat

../bin/opf_split  Z1.dat 0.4 0.0 0.6 0
cp training.dat Z1LINE.dat #labeled samples
cp testing.dat Z1DOUBLELINE.dat #unlabeled samples
rm training.dat
rm testing.dat

#executing the classifier with semi supervised training procedure without evaluating
#-----------------------------------------------------------------------------------
../bin/opf_semi Z1LINE.dat Z1DOUBLELINE.dat
#classifying the test set
../bin/opf_classify Z3.dat
# computing the accuracy over the test set
echo ---------------------------------
echo Semi Supervised OPF mean accuracy
echo ---------------------------------
../bin/opf_accuracy Z3.dat
rm *.acc *.time *.out *.opf
#-----------------------------------------------------------------------------------


#executing the classifier with semi supervised training procedure with evaluating
#-----------------------------------------------------------------------------------
../bin/opf_semi Z1LINE.dat Z1DOUBLELINE.dat evaluating.dat
#classifying the test set
../bin/opf_classify Z3.dat
# computing the accuracy over the test set
echo ---------------------------------
echo Semi Supervised OPF mean accuracy with Evaluating
echo ---------------------------------
../bin/opf_accuracy Z3.dat
#-----------------------------------------------------------------------------------


rm Z1.dat Z3.dat Z1LINE.dat Z1DOUBLELINE.dat evaluating.dat classifier.opf *.acc *.time *.out 
