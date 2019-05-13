#include "OPF.h"

int main(int argc, char **argv)
{
	fflush(stdout);
	fprintf(stdout, "\nProgram that executes the training phase of the OPF classifier with knn adjacency\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n");
	fflush(stdout);

	if ((argc != 5) && (argc != 4))
	{
		fprintf(stderr, "\nusage opf_train <P1> <P2>");
		fprintf(stderr, "\nP1: training set in the OPF file format");
		fprintf(stderr, "\nP2: evaluating set in the OPF file format (used to learn k)");
		fprintf(stderr, "\nP3: kmax");
		fprintf(stderr, "\nP4: precomputed distance file (leave it in blank if you are not using this resource)\n");
		exit(-1);
	}

	int n, i, kmax = atoi(argv[3]);
	char fileName[256];
	FILE *f = NULL;
	timer tic, toc;
	double time;

	if (argc == 5)
		opf_PrecomputedDistance = 1;

	fprintf(stdout, "\nReading data file ...");
	fflush(stdout);
	Subgraph *Train = ReadSubgraph(argv[1]);
	Subgraph *Eval = ReadSubgraph(argv[2]);
	fprintf(stdout, " OK");
	fflush(stdout);

	if (opf_PrecomputedDistance)
		opf_DistanceValue = opf_ReadDistances(argv[4], &n);

	fprintf(stdout, "\nTraining OPF classifier ...");
	fflush(stdout);
	gettimeofday(&tic, NULL);
	opf_OPFknnTraining(Train, Eval, kmax);
	gettimeofday(&toc, NULL);
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nWriting classifier's model file ...");
	fflush(stdout);
	opf_WriteModelFile(Train, "classifier.opf");
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nWriting output file ...");
	fflush(stdout);
	sprintf(fileName, "%s.out", argv[1]);
	opf_WriteOutputFile(Train, fileName);
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	fflush(stdout);
	DestroySubgraph(&Train);
	DestroySubgraph(&Eval);
	if (opf_PrecomputedDistance)
	{
		for (i = 0; i < n; i++)
			free(opf_DistanceValue[i]);
		free(opf_DistanceValue);
	}
	fprintf(stdout, " OK\n");

	time = ((toc.tv_sec - tic.tv_sec) * 1000.0 + (toc.tv_usec - tic.tv_usec) * 0.001) / 1000.0;
	fprintf(stdout, "\nTraining time: %f seconds\n", time);
	fflush(stdout);

	sprintf(fileName, "%s.time", argv[1]);
	f = fopen(fileName, "a");
	fprintf(f, "%f\n", time);
	fclose(f);

	return 0;
}
