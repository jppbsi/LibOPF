#include <stdio.h>
#include <stdlib.h>
#include "OPF.h"

int main(int argc, char **argv)
{

	if (argc != 4)
	{
		fprintf(stderr, "\nusage kmeans <P1> <P2> <P3>\n");
		fprintf(stderr, "\nP1: input file name in the OPF binary format");
		fprintf(stderr, "\nP2: number of clusters (k)");
		fprintf(stderr, "\nP3: output file name containing cluster centroids\n");
		exit(-1);
	}

	fprintf(stderr, "\nProgram to calculate cluster centroids using K-means.\n");

	int i, j, k = atoi(argv[2]);
	double **mean = NULL;
	Subgraph *g = NULL;
	FILE *fp = NULL;

	fflush(stderr);
	fprintf(stderr, "\nReading dataset ... ");
	g = ReadSubgraph(argv[1]);
	fprintf(stderr, "OK");

	mean = (double **)calloc(k, sizeof(double *));
	for (i = 0; i < k; i++)
		mean[i] = (double *)calloc(g->nfeats, sizeof(double *));

	fflush(stderr);
	fprintf(stderr, "\nRunning k-means ... ");
	kMeans(g, mean, k);
	fprintf(stderr, "OK");

	fprintf(stderr, "\nPurity of clustering: %lf", Purity(g));

	fprintf(stdout, "\nWriting output file ...");
	fflush(stdout);
	fp = fopen(argv[3], "w");
	for (i = 0; i < k; i++)
	{
		for (j = 0; j < g->nfeats; j++)
			fprintf(fp, "%lf ", mean[i][j]);
		fprintf(fp, "\n");
	}
	fclose(fp);
	fprintf(stdout, " OK");
	fflush(stdout);

	fflush(stderr);
	fprintf(stderr, "\nDeallocating memory ... ");
	for (i = 0; i < k; i++)
		free(mean[i]);
	free(mean);
	DestroySubgraph(&g);
	fprintf(stderr, "OK\n");

	return 0;
}