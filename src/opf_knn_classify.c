#include "OPF.h"

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that executes the test phase of the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if((argc != 3) && (argc != 2)){
		fprintf(stderr, "\nusage opf_knn_classify <P1> <P2>");
		fprintf(stderr, "\nP1: test set in the OPF file format");
		fprintf(stderr, "\nP2: precomputed distance file (leave it in blank if you are not using this resource\n");
		exit(-1);
	}

	int n,i;
	float time;
	char fileName[256];
	FILE *f = NULL;
	timer tic, toc;

	if(argc == 3) opf_PrecomputedDistance = 1;
	fprintf(stdout, "\nReading data files ..."); fflush(stdout);
	Subgraph *gTest = ReadSubgraph(argv[1]), *gTrain = opf_ReadModelFile("classifier.opf");
	fprintf(stdout, " OK"); fflush(stdout);

	if(opf_PrecomputedDistance)
		opf_DistanceValue = opf_ReadDistances(argv[2], &n);

	fprintf(stdout, "\nClassifying test set ..."); fflush(stdout);
	gettimeofday(&tic,NULL);
	opf_OPFKNNClassify(gTrain, gTest); gettimeofday(&toc,NULL);
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nWriting output file ..."); fflush(stdout);
	sprintf(fileName,"%s.out",argv[1]);
	f = fopen(fileName,"w");
	for (i = 0; i < gTest->nnodes; i++)
		fprintf(f,"%d\n",gTest->node[i].label);
	fclose(f);
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&gTrain);
	DestroySubgraph(&gTest);
	if(opf_PrecomputedDistance){
		for (i = 0; i < n; i++)
			free(opf_DistanceValue[i]);
		free(opf_DistanceValue);
	}
	fprintf(stdout, " OK\n");

	time = ((toc.tv_sec-tic.tv_sec)*1000.0 + (toc.tv_usec-tic.tv_usec)*0.001)/1000.0;
	fprintf(stdout, "\nTesting time: %f seconds\n", time); fflush(stdout);

	sprintf(fileName,"%s.time",argv[1]);
	f = fopen(fileName,"a");
	fprintf(f,"%f\n",time);
	fclose(f);

	return 0;
}
