#include "OPF.h"
#include <stdio.h>

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that generates k folds (files) for the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if(argc != 4){
		fprintf(stderr, "\nusage opf_fold <P1> <P2> <P3>");
		fprintf(stderr, "\nP1: input dataset in the OPF file format");
		fprintf(stderr, "\nP2: k");
		fprintf(stderr, "\nP3: normalize features? 1 - Yes  0 - No\n\n"); 
		exit(-1);
	}
	Subgraph *g = NULL, **fold = NULL;
	int k = atoi(argv[2]), i, op = atoi(argv[3]);
	char fileName[16];
	
	fprintf(stdout, "\nReading data set ..."); fflush(stdout);
	g = ReadSubgraph(argv[1]);
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nCreating %d folds ...",k); fflush(stdout);	
	fold = opf_kFoldSubgraph(g,k);
	fprintf(stdout, " OK\n");

	for (i = 0; i < k; i++){
		fprintf(stdout, "\nWriting fold %d ...",i+1); fflush(stdout);	
		sprintf(fileName,"fold_%d.dat",i+1);
		if(op) opf_NormalizeFeatures(fold[i]);
		WriteSubgraph(fold[i],fileName);
	}
	fprintf(stdout, " OK\n");

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&g);
	for (i = 0; i < k; i++)
		DestroySubgraph(&fold[i]);
	free(fold);
	fprintf(stdout, " OK\n");

	return 0;
}
