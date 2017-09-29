#include "OPF.h"
#include <stdio.h>

int main(int argc, char **argv)
{
	fflush(stdout);
	fprintf(stdout, "\nProgram that generates the precomputed distance file for the OPF classifier\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n");
	fflush(stdout);

	if (argc != 4)
	{
		fprintf(stderr, "\nusage opf_distance <P1> <P2> <P3>");
		fprintf(stderr, "\nP1: Dataset in the OPF file format");
		fprintf(stderr, "\nP2: Distance ID\n");
		fprintf(stderr, "\n	1 - Euclidean");
		fprintf(stderr, "\n	2 - Chi-Square");
		fprintf(stderr, "\n	3 - Manhattan (L1)");
		fprintf(stderr, "\n	4 - Canberra");
		fprintf(stderr, "\n	5 - Squared Chord");
		fprintf(stderr, "\n	6 - Squared Chi-Squared");
		fprintf(stderr, "\n	7 - BrayCurtis");
		fprintf(stderr, "\nP3: Distance normalization? 1- yes 0 - no");
		exit(-1);
	}

	Subgraph *sg = ReadSubgraph(argv[1]);
	FILE *fp = fopen("distances.dat", "wb");
	int i, j, distance = atoi(argv[2]), normalize = atoi(argv[3]);
	float **Distances = NULL, max = -FLT_MAX;

	fwrite(&sg->nnodes, sizeof(int), 1, fp);

	Distances = (float **)malloc(sg->nnodes * sizeof(float *));
	for (i = 0; i < sg->nnodes; i++)
		Distances[i] = (float *)malloc(sg->nnodes * sizeof(int));

	switch (distance)
	{
	case 1:
		fprintf(stdout, "\n	Computing euclidean distance ...");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_EuclDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 2:
		fprintf(stdout, "\n	Computing chi-square distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_ChiSquaredDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 3:
		fprintf(stdout, "\n	Computing Manhattan distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_ManhattanDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 4:
		fprintf(stdout, "\n	Computing Canberra distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_CanberraDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 5:
		fprintf(stdout, "\n	Computing Squared Chord distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_SquaredChordDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 6:
		fprintf(stdout, "\n	Computing Squared Chi-squared distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_SquaredChiSquaredDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	case 7:
		fprintf(stdout, "\n	Computing Bray Curtis distance ...\n");
		for (i = 0; i < sg->nnodes; i++)
		{
			for (j = 0; j < sg->nnodes; j++)
			{
				if (i == j)
					Distances[i][j] = 0.0;
				else
					Distances[sg->node[i].position][sg->node[j].position] = opf_BrayCurtisDist(sg->node[i].feat, sg->node[j].feat, sg->nfeats);
				if (Distances[sg->node[i].position][sg->node[j].position] > max)
					max = Distances[sg->node[i].position][sg->node[j].position];
			}
		}
		break;
	default:
		fprintf(stderr, "\nInvalid distance ID ...\n");
	}

	if (!normalize)
		max = 1.0;
	for (i = 0; i < sg->nnodes; i++)
	{
		for (j = 0; j < sg->nnodes; j++)
		{
			Distances[i][j] /= max;
			fwrite(&Distances[i][j], sizeof(float), 1, fp);
		}
	}

	fprintf(stdout, "\n\nDistances generated ...\n");
	fflush(stdout);
	fprintf(stdout, "\n\nDeallocating memory ...\n");
	for (i = 0; i < sg->nnodes; i++)
		free(Distances[i]);
	free(Distances);

	DestroySubgraph(&sg);
	fclose(fp);

	return 0;
}
