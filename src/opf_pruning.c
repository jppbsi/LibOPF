#include "OPF.h"

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that executes the pruning algorithm of the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if((argc != 5) && (argc != 4)){
		fprintf(stderr, "\nusage opf_classify <P1> <P2>");
		fprintf(stderr, "\nP1: training set in the OPF file format");
		fprintf(stderr, "\nP2: evaluating set in the OPF file format");
		fprintf(stderr, "\nP3: percentage of accuracy");
		fprintf(stderr, "\nP4: precomputed distance file (leave it in blank if you are not using this resource\n");
		exit(-1);
	}

	int n,i,isize,fsize;
	float time, desiredAcc = atof(argv[3]), prate;
	char fileName[256];
	FILE *f = NULL;
	timer tic, toc;
	size_t result;

	if(argc == 5) opf_PrecomputedDistance = 1;
	fprintf(stdout, "\nReading data files ..."); fflush(stdout);
	Subgraph *gTrain = ReadSubgraph(argv[1]), *gEval = ReadSubgraph(argv[2]);
	fprintf(stdout, " OK"); fflush(stdout);

	if(opf_PrecomputedDistance)
		opf_DistanceValue = opf_ReadDistances(argv[2], &n);

	isize = gTrain->nnodes;
	fprintf(stdout, "\nPruning training set ..."); fflush(stdout);
	gettimeofday(&tic,NULL); opf_OPFPruning(&gTrain, &gEval, desiredAcc); gettimeofday(&toc,NULL);
	fprintf(stdout, " OK"); fflush(stdout);
	fsize = gTrain->nnodes;

	prate = (1-fsize/(float)isize)*100; fprintf(stdout, "\nFinal pruning rate: %.2f%%", prate); fflush(stdout);

	fprintf(stdout, "\n\nWriting classifier's model file ..."); fflush(stdout);
	opf_WriteModelFile(gTrain, "classifier.opf"); fprintf(stdout, " OK"); fflush(stdout);
	fprintf(stdout, " OK"); fflush(stdout);

	f = fopen("prate.pr","a");
	result = fprintf(f,"%f\n",prate);
	fclose(f);

	time = ((toc.tv_sec-tic.tv_sec)*1000.0 + (toc.tv_usec-tic.tv_usec)*0.001)/1000.0;
	fprintf(stdout, "\nPruning time: %f seconds\n", time); fflush(stdout);
	sprintf(fileName,"%s.time",argv[1]);
	f = fopen(fileName,"a");
	result = fprintf(f,"%f\n",time);
	fclose(f);

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&gTrain);
	DestroySubgraph(&gEval);
	if(opf_PrecomputedDistance){
		for (i = 0; i < n; i++)
			free(opf_DistanceValue[i]);
		free(opf_DistanceValue);
	}
	fprintf(stdout, " OK\n");

	return 0;
}
