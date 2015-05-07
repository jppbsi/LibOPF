LibOPF is a library of functions and programs for free usage in the
design of optimum-path forest classifiers. This second version 
contains some additional resources related to the supervised
OPF classifier reported in reference [PapaIJIST09,PapaPR12], and also
contains the unsupervised version of OPF reported in reference
[RochaIJIST09].

A short explanation about the method can be found in
http://www.ic.unicamp.br/~afalcao/LibOPF. Please read the COPYRIGHT
file before using LibOPF.

For large datasets (thousands/millions of samples), it is usually
desirable to keep some maximum size for the training set. However, an
evaluation set can improve the training samples during pseudo tests
(learning procedure). Therefore, LibOPF provides a program to randomly
split the dataset into training, evaluation and test sets (opf_split).

One can project an OPF classifier by using the program 'opf_train' and
test it by using the program 'opf_classify'. However, for large
datasets, the program 'opf_learn' substitutes the 'opf_train' by
learning from classification errors in the evaluation set without
increasing the training set size. Afterwards, the classifier is tested
by using 'opf_classify'.

In the case of time-consuming distance functions, one can generate a
precomputed distance file in the format specified in section
'opf_distance' Usage. LibOPF also provides a program (opf_distance)
with some options of distance functions, which generates a precomputed
distance file.


Table of Contents
=================
- Installation
- OPF file format for datasets
- Programs included
	SUPERVISED OPF
		- 'opf_split' Usage
		- 'opf_train' Usage
		- 'opf_learn' Usage
		- 'opf_classify' Usage
		- 'opf_accuracy' Usage
	UNSUPERVISED OPF
		- 'opf_cluster' Usage
		- 'opf_knn_classify' Usage
	COMMON (Auxiliary functions)
		- 'opf_distance' Usage
		- 'opf_normalize' Usage	
		- 'opf_info' Usage
		- 'opf_fold' Usage
		- 'opf_merge' Usage
- Datasets
- Examples of scripts
- Tools
- Accuracy computation
- Fixed bugs
- Additional Information

Installation
============

On Unix systems, decompress the LibOPF.tar.bz2 file (use tar -xvjf
LibOPF.tar.bz2) into a directory. The system will create a directory
named 'LibOPF'. Type 'cd LibOPF', and then type `make' to build the
programs 'opf_split', 'opf_accuracy', 'opf_train', 'opf_learn', 'opf_distance', and
'opf_classify' into the /bin directory. Run them without arguments to
show their usage. 

OPF file format for datasets
============================

The original dataset and its parts training, evaluation and test sets
must be in the following BINARY file format:

<# of samples> <# of labels> <# of features> 
<0> <label> <feature 1 from element 0> <feature 2 from element 0> ...
<1> <label> <feature 1 from element 1> <feature 2 from element 1> ...
.
.
<i> <label> <feature 1 from element i> <feature 2 from element i> ...
<i+1> <label> <feature 1 from element i+1> <feature 2 from element i+1> ...
.
.
<n-1> <label> <feature 1 from element n-1> <feature 2 from element n-1> ... 

The first number of each line, <0>, <1>, ... <n-1>, is a sample
identifier (for n samples in the dataset), which is used in the case
of precomputed distances. However, the identifier must be specified
anyway. For unlabeled datasets, please use label 0 for all samples
(unsupervised OPF).

Example: Suppose that you have a dataset with 5 samples, distributed
into 3 classes, with 2 elements from label 1, 2 elements from label 2
and 1 element from label 3. Each sample is represented by a feature
vector of size 2. So, the OPF file format should look like as below:

5	3	2
0	1	0.21	0.45
1	1	0.22	0.43
2	2	0.67	1.12
3	2	0.60	1.11
4	3	0.79	0.04

Comment #1: Note that, the file must be binary with no blank
spaces. This ASCII representation is just for illustration.

Comment #2: The first line of the file, 5 3 2, contains, respectively,
the dataset size, the number of labels (classes) and the number of
features in the feature vectors. The remaining lines contain the
sample identifier (integer from 0 to n-1, in which n is the dataset
size), its label and the feature values for each sample.

Programs included
=================

In this package, we have the following programs:

SUPERVISED OPF -------------

opf_split:

	This is a program to randomly split the dataset into training,
evaluation and test sets.

opf_train:

	This is a program to execute the training phase.

opf_learn:

	This is a program to execute the learning phase from
	classification errors in the evaluation set. It substitutes
	'opf_train'.

opf_classify:

	This is a program to execute the test phase by classifying the test set. 

opf_accuracy:

	This is a program to compute the accuracy over training and/or test set.

UNSUPERVISED OPF -------------
opf_cluster:

	This is a program to compute clusters by OPF. It assigns a
	consecutive number starting from 1 to N for N clusters, when
        the training set is unlabeled. Otherwise, it propagates the
        true labels of the roots to the labels of the nodes in their
        respective trees in order to evaluate the quality of the
        clustering. The resulting classifier is written in classifier.opf

opf_knn_classify:

	This program uses the classifier from opf_cluster to assign
labels to a test or training set. The accuracy of the process makes
sense only when these sets have true labels. This accuracy can be
measured by opf_accuracy and it represents the quality of the
clustering process.

COMMON (Auxiliary functions) -------------
opf_distance:

	This is a program to compute distance functions and store them
	into a precomputed distance file.

opf_normalize:

	This is a program to normalise datasets.

opf_info:

	This is a program that retrieves basic information about OPF files, such as the dataset size, number of labels and features.

opf_fold:

	This program partitions the datasets in k folds.


opf_merge:

	This program merges the folds, and it can be used together with 'opf_fold' program.


'opf_split' Usage
=================

Usage: opf_split <P1> <P2> <P3> <P4> <P5>

	P1: dataset in the OPF file format
	P2: percentage of the training set size [0,1]
	P3: percentage of the evaluation set size [0,1] 
	(leave 0 in the case of no learning)
	P4: percentage of the test set size [0,1]"
	P5: normalize features? 1 - Yes  0 - No

The sum P2+P3+P4 must be 1.

The features are normalized with the following equation: 

N_i = (F_i - M_i)/S_i, 

where F_i, M_i and S_i are, respectively, the feature i, the average
of F_i and the standard deviation of F_i in the dataset.

The program splits the dataset into two new files, training.opf and
testing.opf, when P3=0, and it splits the dataset into three files,
training.opf, evaluating.opf and testing.opf, otherwise.

'opf_train' Usage
=================

Usage: opf_train <P1> <P2>

	P1: training set in the OPF file format
	P2: precomputed distance file 
	(leave it in blank if you are not using this resource)

The program designs a classifier from training.opf and outputs it in a
file named classifier.opf, which is used by 'opf_classify' for
testing.

The opf_train also outputs the following files:
-> .out: it contains the predicted labels (training phase)
-> .time: it contains the execution time in seconds (training phase)
-> .acc: it contains the accuracy (training phase)

'opf_learn' Usage
=================

Usage: opf_learn <P1> <P2> <P3>

	P1: training set in the OPF file format
	P2: evaluation set in the OPF file format
	P3: precomputed distance file 
	(leave it in blank if you are not using this resource)

The program substitutes 'opf_learn' when there is evaluation set. It
learns from the classification errors in the evaluation set without
increasing the training set size, and outputs a final classifier in a
file named classifier.opf, which is used for testing by the program
'opf_classify'.

The opf_learning outputs the following file:
-> .time: it contains the execution time in seconds (learning phase)

'opf_classify' Usage
====================

Usage: opf_classify <P1> <P2>
	P1: test/training set in the OPF file format
	P2: precomputed distance file 
	(leave it in blank if you are not using this resource)


The opf_classify outputs the following files:
-> .out: it contains the predicted labels (test phase)
-> .time: it contains the execution time in seconds (test phase)

'opf_accuracy' Usage
====================

Usage: opf_accuracy <P1> 
	P1: data set in the OPF file format

The opf_accuracy will look for a classified file with the same name of
the data set file in P1 and extension ".out" in order to compute the
accuracy of that classification. It outputs a text file with the same
name and extension ".acc".

'opf_cluster' Usage
====================

Usage: opf_cluster <P1> <P2> <P3> <P4> <P5>
	P1: unlabeled data set in the OPF file format
	P2: kmax(maximum degree for the knn graph)
	P3: 0 (height), 1(area) and 2(volume)
	P4: value of parameter P3 (integer) in (0-1)
	P5: precomputed distance file (leave it in blank if you are not using this resource

P3: allows to remove maxima from the pdf based on height, area or
volume criteria.

note: the opf_cluster outputs the k value that minimized the cut in
the graph as well as the number of obtained clusters and a classifier
written in a file classifier.opf. The labeled samples (predicted) are
also outputed in a ".out file"

'opf_knn_classify' Usage
========================

Usage: opf_knn_classify <P1> <P2>
	P1: test/training set in the OPF file format
	P2: precomputed distance file 
	(leave it in blank if you are not using this resource)

The opf_knn_classify outputs the following files:
-> .out: it contains the predicted labels (test phase)
-> .time: it contains the execution time in seconds (test phase)


'opf_distance' Usage
====================

One of the most important characteristic of the OPF classifier is the
possibility of working with any distance function. Its default is the
Euclidean metric. The user can execute the program 'opf_distance' with
the following options of distance functions.

Usage: opf_distance <P1> <P2> <P3>
P1: Dataset in the OPF file format
P2: Distance ID

	1 - Euclidean
	2 - Chi-Square
	3 - Manhattan (L1)
	4 - Canberra
	5 - Squared Chord
	6 - Squared Chi-Squared
	7 - BrayCurtis
P3: Distance normalization? 1- yes 0 - no

The program computes the selected distance function between every pair
of samples in the dataset and outputs a precomputed distance file
(distances.dat). The sample identifier in the dataset is used
here. The distance values may be or not be normalized with P3. The
user can also create his/her own distance file. The file BINARY format
is:

<# of samples>
<Distance from sample 0 to sample 0> <Distance from sample 0 to sample 1> ...
<Distance from sample 1 to sample 0> <Distance from sample 1 to sample 1> ...
.
.
<Distance from sample n-1 to sample 0> <Distance from sample n-1 to sample 1> ...

Comment #1: Note that, the file is an N x N matrix of distance
values. It must be binary with no blank spaces. This ASCII
representation is just for illustration.


'opf_normalize' Usage
====================

If the user has its own datasets and does not need to use 'opf_split', he/her may need to normalise the dataset. Therefore, the user can use the 'opf_normalize' program, which employes the same normalisation process used by 'opf_split'.

usage opf_normalize <P1> <P2>
P1: input dataset in the OPF file format
P2: normalized output dataset in the OPF file format


'opf_info' Usage
====================

It retrieves basic information about OPF files, such as dataset size, and number of labels and features.

usage opf_info <P1>
P1: OPF file


'opf_fold' Usage
====================

If the user needs to employ a k-fold cross validation, he/she can use the  'opf_fold'program, which partitions the dataset in k folds. The user can merge folds with 'opf_merge' program.

usage opf_fold <P1> <P2> <P3>
P1: input dataset in the OPF file format
P2: k
P3: normalize features? 1 - Yes  0 - No


'opf_merge' Usage
====================

If merges n folds for a k-fold cross validation.

usage opf_merge <P1> <P2> ... <Pn>
P1: input dataset 1 in the OPF file format
P2: input dataset 2 in the OPF file format
Pn: input dataset n in the OPF file format


Datasets
=================

In directory 'LibOPF/data', the user can find several artificial and synthetic datasets, which are 
divided into:
	Synthetic: datasets obtained from [Kuncheva]
		-> cone-torus.dat: dataset containg 400 samples distributed into 3 classes. Each
		sample is represented by 2 features
		-> petals.dat: dataset containg 100 samples distributed into 4 classes. Each
		 sample is represented by 2 features
		-> boat.dat: dataset containing 100 samples distributed into 3 classes. Each
		sample is represented by 2 features
		-> saturn.dat: dataset containing 200 samples distributed into 2 classes. Each
		sample is represented by 2 features

	Artificial: MPEG-7 shape dataset [MPEG-7]. The MPEG-7 shape dataset contains 1400 samples
	distributed into 70 classes
		->  mpeg7_FOURIER.dat: Fourier shape descritor extracted from the whole dataset (126 features)
		->  mpeg7_BAS.dat: BAS (Beam Angle Statistics) shape descritor extracted from the whole dataset (180 features)
		Details about the features extraction procedure can be found in [PapaIJIST09]

Examples of scripts
=================

The LibOPF package contains a directory 'LibOPF/examples', in which
you can find some scripts. To run a simple example, type

# This command will split the cone-torus dataset into a training set
# with 40% of the samples (training.dat) and a test set (testing.dat)
# with 60% of the samples

> bin/opf_split data/cone-torus.dat 0.4 0 0.6 0

# This command will execute the training phase and generates an output
# file named classifier.opf, which represents the OPF classifier.

> bin/opf_train training.dat 

# This command will execute the test phase using classifier.opf

> bin/opf_classify testing.dat

# This command will compute the accuracy over the test set

> bin/opf_accuracy testing.dat testing.dat.out

You can also execute the following scripts inside the directory
LibOPF/examples:

example1.sh:
	
	A script to train and test the classifier without the learning
	procedure.

example2.sh:

	A script to learn and test the classifier.

example3.sh:

	A script to train and test the classifier without the learning
	procedure and with precomputed distances.

example4.sh:

	A script to learn and test the classifier with precomputed distances.

example5.sh:

	A script to run the unsupervised OPF.


Tools
=================

The LibOPF package contains a directory 'LibOPF/tools', in which you
can find some useful tools. At this moment, we have available: 

-> runOPF.sh: a script that executes the supervised OPF several times
(defined by the user) and outputs the mean accuracy and the mean
training and test execution times (seconds), with their respectively
standard deviations.

'runOPF.sh' Usage
====================

Usage: run_sh <P1> <P2> <P3> <P4> <P5>

P1: dataset file name
P2: percentage for the training set size [0,1]
P3: percentage for the test set size [0,1]
P4: normalize features? 1 - Yes  0 - No
P5: running times

-> runLearning.sh: a script that executes the supervised OPF with and without
learning several times (defined by the user) and outputs the mean accuracy and the mean
training and test execution times (seconds), with their respectively
standard deviations. This script allow you to compare the OPF performance with and without
learning algorithm.

'runLearning.sh' Usage
====================

Usage: run_sh <P1> <P2> <P3> <P4> <P5>

P1: dataset file name
P2: percentage for the training set size [0,1]
P3: percentage for the evaluating set size [0,1]
P4: percentage for the test set size [0,1]
P5: normalize features? 1 - Yes  0 - No
P6: running times

-> txt2opf: a program to convert OPF files written in ASCII format to binary format.

Usage of 'txt2opf' 
====================

Usage: txt2opf <P1> <P2>

P1: input OPF file name in the ASCII format
P2: output OPF file name in the binary format

-> opf2txt: a program to convert OPF files written in binary format to ASCII format.

Usage of 'opf2txt' 
====================

Usage: opf2txt <P1> <P2>

P1: input OPF file name in the binary format
P2: output OPF file name in the ASCII format

-> opf_check: a program to check whether a file is in the OPF required format.

Usage of 'opf_check' 
====================

Usage: opf_check <P1>

P1: input OPF file name in the ASCII format

Notice the input to opf_check is a txt file.

-> statistics: a program that computes basic information such as mean average and standard deviation. The user can output the accuracies in a TEXT file and then use 'statistics' to compute the mean accuracy and standard deviation of the results.

Usage of 'statistics' 
====================

usage statistics <P1> <P2> <P3>

P1: file name
P2: running times
P3: message (the user may need to output some message in the screen)

Therefore, a recommended pipeline to create and to check the correctness of your OPF file can performed as follows:
(1) create your txt file in the LibOPF required format;
(2) use tools/opf_check to check if it is in the proper format; and
(3) if your file format has passed through opf_check requirements, use tools/txt2opf to convert your txt file to a binary version to be used in LibOPF.

Accuracy computation
====================

If you intend to compare the OPF classifier using LibOPF with others
in the literature, you need to pay attention to our measure of
accuracy. The accuracy of a classifier can be measured in any set:
training, evaluation, and test. The accuracy in LibOPF is measured by
taking into account that the classes may have different sizes. If
there are two classes, for example, with very different sizes and a
classifier always assigns the label of the largest class, its accuracy
will fall drastically due to the high error rate on the smallest
class. The details about the formula of accuracy are given in
http://www.ic.unicamp.br/~afalcao/LibOPF.

Fixed bugs 
======================
- division by zero in "NormalizeFeatures" function used in "opf_split" program. Thanks to Ishihara Takashi - University of Electro-Communications, Tokyo, Japan.
- removal of include <malloc.h> in OPF.h for OSX compatibilities. Thanks to Bob L. Sturm - Aalborg University Copenhagen.

Additional Information 
======================

If you find LibOPF helpful, please cite the references

@Manual{LibOPF09,
  author =	 {J.P. Papa and A.X. Falc{\~{a}}o and C.T.N. Suzuki},
  title =	 {{LibOPF}: {A} library for the design of 
                   optimum-path forest classifiers},
  institution = {Institute of Computing, University of Campinas},
  year =	 {2009},
  note =	 {Software version 2.0 available at 
                 \url{http://www.ic.unicamp.br/\~{}afalcao/LibOPF}}
}

@article{PapaIJIST09,
	author = {J. P. Papa and A. X. Falc{\~{a}}o and Celso T. N. Suzuki},
	title = {Supervised Pattern Classification based on Optimum-Path Forest},
	journal = {International Journal of Imaging Systems and Technology},
	volume = {19},
	issue = {2},
	pages = {120--131},
	publisher = {Wiley-Interscience},
	year = {2009},
}

@article{PapaPR12,
	author = {J. P. Papa and A. X. Falc{\~{a}}o and V. H. C. Albuquerque and J. M. R. S. Tavares},
	title = {Efficient supervised optimum-path forest classification for large datasets},
	journal = {Pattern Recognition},
	volume = {45},
	number = {1},
	year = {2012},
	pages = {512--520},
	publisher = {Elsevier Science Inc.},
	address = {New York, NY, USA},
} 


@article{RochaIJIST09,
	author = {L.M. Rocha and F.A.M. Cappabianco and A.X. Falc{\~{a}}o},
	title =  {Data clustering as an optimum-path forest problem with applications in image analysis},
	journal = {International Journal of Imaging Systems and Technology}, 
	publisher = {Wiley Periodicals},
	volume = {19},
	number = {2},
	pages = {50--68},
	year = {2009}
}

If you used some synthetic dataset from LibOPF, please cite:

@article{Kuncheva,
	Author = {L. Kuncheva},
	title= {Artificial Data},
	Journal = {School of Informatics, University of Wales, Bangor},
	url = {http://www.informatics.bangor.ac.uk/{\~{}}kuncheva};
	year = {1996}
}

If you used MPEG-7 dataset from LibOPF, please cite:

@article{MPEG-7,
	author = {MPEG-7},
	title = {MPEG-7: The Generic Multimedia Content Description Standard, Part 1},
	journal = {IEEE MultiMedia},
	volume = {09},
	number = {2},
	issn = {1070-986X},
	pages = {78-87},
	doi = {http://doi.ieeecomputersociety.org/10.1109/MMUL.2002.10016},
	publisher = {IEEE Computer Society},
	address = {Los Alamitos, CA, USA},
	year = {2002}
}

For any questions and comments, please send your email to
papa.joaopaulo@gmail.com or afalcao@ic.unicamp.br.
