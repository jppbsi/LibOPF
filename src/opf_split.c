#include "OPF.h"
#include <stdio.h>

void CheckInputData(float TrPercentage, float EvalPercentage, float TestPercentage){
	fprintf(stderr, "\nSummation of set percentages = %.1f ...",TrPercentage+EvalPercentage+TestPercentage);
	if((float)(TrPercentage+EvalPercentage+TestPercentage) != (float)1.0)
		Error("Percentage summation is not equal to 1","CheckInputData");
	fprintf(stderr, " OK");

	fprintf(stderr, "\nChecking set percentages ...");
	if(TrPercentage == 0.0f || TestPercentage == 0.0f)
		Error("Percentage of either training set or test set is equal to 0", "CheckInputData");
	printf(" OK");
}

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that generates training, evaluation and test sets for the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if(argc != 6){
		fprintf(stderr, "\nusage opf_split <P1> <P2> <P3> <P4> <P5>");
		fprintf(stderr, "\nP1: input dataset in the OPF file format");
		fprintf(stderr, "\nP2: percentage for the training set size [0,1]");
		fprintf(stderr, "\nP3: percentage for the evaluation set size [0,1] (leave 0 in the case of no learning)");
		fprintf(stderr, "\nP4: percentage for the test set size [0,1]");
		fprintf(stderr, "\nP5: normalize features? 1 - Yes  0 - No\n\n");
		exit(-1);
	}
	Subgraph *g = NULL, *gAux = NULL, *gTraining = NULL, *gEvaluating = NULL, *gTesting = NULL;
	float training_p = atof(argv[2]), evaluating_p = atof(argv[3]), testing_p = atof(argv[4]);
	int normalize = atoi(argv[5]);

	CheckInputData(training_p, evaluating_p, testing_p);

	fprintf(stdout, "\nReading data set ..."); fflush(stdout);
	g = ReadSubgraph(argv[1]);
	fprintf(stdout, " OK"); fflush(stdout);

	if(normalize) opf_NormalizeFeatures(g);

	fprintf(stdout, "\nSplitting data set ..."); fflush(stdout);
	opf_SplitSubgraph(g, &gAux, &gTesting, training_p+evaluating_p);

	if (evaluating_p > 0)
	  opf_SplitSubgraph(gAux, &gTraining, &gEvaluating, training_p/(training_p+evaluating_p));
	else gTraining = CopySubgraph(gAux);

	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nWriting data sets to disk ..."); fflush(stdout);
	WriteSubgraph(gTraining, "training.dat");
	if (evaluating_p > 0) WriteSubgraph(gEvaluating, "evaluating.dat");
	WriteSubgraph(gTesting, "testing.dat");
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&g);
	DestroySubgraph(&gAux);
	DestroySubgraph(&gTraining);
	DestroySubgraph(&gEvaluating);
	DestroySubgraph(&gTesting);
	fprintf(stdout, " OK\n");

	return 0;
}
