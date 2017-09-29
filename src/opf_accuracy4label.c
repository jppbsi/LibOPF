#include "OPF.h"

int main(int argc, char **argv)
{
	fflush(stdout);
	fprintf(stdout, "\nProgram that computes the OPF accuracy for each class of a given set\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n");
	fflush(stdout);

	if (argc != 2)
	{
		fprintf(stderr, "\nusage opf_accuracyforlabel <P1>");
		fprintf(stderr, "\nP1: data set in the OPF file format\n");
		exit(-1);
	}

	int i;
	float *Acc = NULL;
	FILE *f = NULL;
	char fileName[256];

	fprintf(stdout, "\nReading data file ...");
	fflush(stdout);
	Subgraph *g = ReadSubgraph(argv[1]);
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nReading output file ...");
	fflush(stdout);
	sprintf(fileName, "%s.out", argv[1]);
	f = fopen(fileName, "r");
	if (!f)
	{
		fprintf(stderr, "\nunable to open file %s", argv[2]);
		exit(-1);
	}

	for (i = 0; i < g->nnodes; i++)
	{
		if (fscanf(f, "%d", &g->node[i].label) != 1)
		{
			fprintf(stderr, "\nError reading node label");
			exit(-1);
		}
	}
	fclose(f);
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nComputing accuracy ...");
	fflush(stdout);
	Acc = opf_Accuracy4Label(g);
	for (i = 1; i <= g->nlabels; i++)
		fprintf(stdout, "\nClass %d: %.2f%%", i, Acc[i] * 100);
	fflush(stdout);

	fprintf(stdout, "\nWriting accuracy in output file ...");
	fflush(stdout);
	sprintf(fileName, "%s.acc", argv[1]);
	f = fopen(fileName, "a");
	fprintf(f, "%f", Acc[1]);
	for (i = 2; i <= g->nlabels; i++)
	{
		fprintf(f, " %f", Acc[i]);
		fprintf(f, "\n");
	}
	fclose(f);
	fprintf(stdout, " OK");
	fflush(stdout);

	fprintf(stdout, "\nDeallocating memory ...");
	fflush(stdout);
	DestroySubgraph(&g);
	fprintf(stdout, " OK\n");

	free(Acc);

	return 0;
}
