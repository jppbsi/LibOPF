#include "OPF.h"

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that executes the learning phase for the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if((argc != 3) && (argc != 4)){
		fprintf(stderr, "\nusage opf_learn <P1> <P2> <P3>");
		fprintf(stderr, "\nP1: training set in the OPF file format");
		fprintf(stderr, "\nP2: evaluation set in the OPF file format");
		fprintf(stderr, "\nP3: precomputed distance file (leave it in blank if you are not using this resource\n");
		exit(-1);
	}

	float Acc, time;
	char fileName[512];
	int i,n;
	timer tic, toc;
	FILE *f = NULL;

	if(argc == 4) opf_PrecomputedDistance = 1;
	fprintf(stdout, "\nReading data file ..."); fflush(stdout);
	Subgraph *gTrain = ReadSubgraph(argv[1]), *gEval = ReadSubgraph(argv[2]);
	fprintf(stdout, " OK"); fflush(stdout);

	if(opf_PrecomputedDistance)
		opf_DistanceValue = opf_ReadDistances(argv[3], &n);

	fprintf(stdout, "\nLearning from errors in the evaluation set..."); fflush(stdout);
	gettimeofday(&tic,NULL); opf_OPFLearning(&gTrain, &gEval); gettimeofday(&toc,NULL);
	time = ((toc.tv_sec-tic.tv_sec)*1000.0 + (toc.tv_usec-tic.tv_usec)*0.001)/1000.0;
	Acc = opf_Accuracy(gTrain);
	fprintf(stdout, "\nFinal opf_Accuracy in the training set: %.2f%%", Acc*100); fflush(stdout);
	Acc = opf_Accuracy(gEval);
	fprintf(stdout, "\nFinal opf_Accuracy in the evaluation set: %.2f%%", Acc*100); fflush(stdout);

	fprintf(stdout, "\n\nWriting classifier's model file ..."); fflush(stdout);
	opf_WriteModelFile(gTrain, "classifier.opf"); fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&gTrain);
	DestroySubgraph(&gEval);
	if(opf_PrecomputedDistance){
		for (i = 0; i < n; i++)
			free(opf_DistanceValue[i]);
		free(opf_DistanceValue);
	}
	fprintf(stdout, " OK\n"); fflush(stdout);

	sprintf(fileName,"%s.time",argv[1]);
	f = fopen(fileName,"a");
	fprintf(f,"%f\n",time);
	fclose(f);

	return 0;
}
