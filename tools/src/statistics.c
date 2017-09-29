#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	if (argc != 4)
	{
		fprintf(stderr, "\nusage statistics <file name> <running times> <message>\n");
		exit(-1);
	}

	FILE *fpIn = NULL;
	int i, it = atoi(argv[2]);
	float Std = 0.0f, MeanAcc = 0.0f, aux, *acc = NULL;

	/*Computing mean accuracy and standard deviation***/
	fpIn = fopen(argv[1], "r");
	if (!fpIn)
	{
		fprintf(stderr, "\nunable to open file %s\n", argv[1]);
		exit(-1);
	}

	acc = (float *)malloc(it * sizeof(float));
	for (i = 1; i <= it; i++)
	{
		if (fscanf(fpIn, "%f", &aux) != 1)
		{
			fprintf(stderr, "\n Could not read accuracy");
			exit(-1);
		}
		acc[i - 1] = aux;
		MeanAcc += aux;
	}
	MeanAcc /= it;
	for (i = 0; i < it; i++)
		Std += pow(acc[i] - MeanAcc, 2);
	Std = sqrt(Std / it);

	fclose(fpIn);
	free(acc);

	fprintf(stderr, "\n%s %f with standard deviation: %f\n", argv[3], MeanAcc, Std);

	return 0;
}
