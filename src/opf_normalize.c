#include "OPF.h"
#include <stdio.h>

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that normalizes data for the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 3.0 (2013)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if(argc != 3){
		fprintf(stderr, "\nusage opf_normalize <P1> <P2>");
		fprintf(stderr, "\nP1: input dataset in the OPF file format");
		fprintf(stderr, "\nP2: normalized output dataset in the OPF file format\n");
		exit(-1);
	}
	Subgraph *g = NULL;

	fprintf(stdout, "\nReading data set ..."); fflush(stdout);
	g = ReadSubgraph(argv[1]);
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nNormalizing data set ..."); fflush(stdout);
    opf_NormalizeFeatures(g);
	fprintf(stdout, " OK"); fflush(stdout);
    
	fprintf(stdout, "\nWriting normalized data set to disk ..."); fflush(stdout);
    WriteSubgraph(g, argv[2]);
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	DestroySubgraph(&g);
	fprintf(stdout, " OK\n");

	return 0;
}
