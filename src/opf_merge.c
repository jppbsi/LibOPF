#include "OPF.h"
#include <stdio.h>

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that merge subgraphs\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2010)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if((argc == 2) || (argc <= 1)){
		fprintf(stderr, "\nusage opf_merge <P1> <P2> ... <Pn>");
		fprintf(stderr, "\nP1: input dataset 1 in the OPF file format");
		fprintf(stderr, "\nP2: input dataset 2 in the OPF file format");
		fprintf(stderr, "\nPn: input dataset n in the OPF file format\n");
		exit(-1);
	}
	Subgraph **g = (Subgraph **)malloc(sizeof(Subgraph **)*(argc-1)), *merged = NULL, *aux = NULL;
	int i;

	fprintf(stdout, "\nReading data sets ..."); fflush(stdout);
	for (i = 0; i < argc-1; i++)
		g[i] = ReadSubgraph(argv[i+1]);
	fprintf(stdout, " OK"); fflush(stdout);

	aux = CopySubgraph(g[0]);
	for (i = 1; i < argc-1; i++){
		merged = opf_MergeSubgraph(aux,g[i]);
		DestroySubgraph(&aux);
		aux = CopySubgraph(merged);
		DestroySubgraph(&merged);
	}
	
	fprintf(stdout, "\nWriting data set to disk ..."); fflush(stdout);
	WriteSubgraph(aux, "merged.dat");
	fprintf(stdout, " OK"); fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	for (i = 0; i < argc-1; i++)
			DestroySubgraph(&g[i]);
	DestroySubgraph(&aux);
	free(g);
	fprintf(stdout, " OK\n");

	return 0;
}
