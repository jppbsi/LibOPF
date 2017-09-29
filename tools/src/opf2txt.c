#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{

	if (argc != 3)
	{
		fprintf(stderr, "\nusage: opf2txt <opf file name> <output file name> \n");
		exit(-1);
	}

	fprintf(stderr, "\nProgram to convert files written in the OPF binary format to the OPF ASCII format.");

	FILE *fpIn = NULL, *fpOut = NULL;
	int n, ndata, nclasses, label, i, j;
	int id;
	float aux;
	size_t result = 0;

	fpIn = fopen(argv[1], "rb");
	fpOut = fopen(argv[2], "w");

	/*gravando numero de objetos*/
	result = fread(&n, sizeof(int), 1, fpIn);
	fprintf(fpOut, "%d ", n);

	/*gravando numero de classes*/
	result = fread(&nclasses, sizeof(int), 1, fpIn);
	fprintf(fpOut, "%d ", nclasses);

	/*gravando tamanho vetor de caracteristicas*/
	result = fread(&ndata, sizeof(int), 1, fpIn);
	fprintf(fpOut, "%d ", ndata);

	fprintf(fpOut, "\n");
	/*gravando vetor de caracteristicas*/
	for (i = 0; i < n; i++)
	{
		result = fread(&id, sizeof(int), 1, fpIn);
		result = fread(&label, sizeof(int), 1, fpIn);
		fprintf(fpOut, "%d %d ", id, label);
		for (j = 0; j < ndata; j++)
		{
			result = fread(&aux, sizeof(float), 1, fpIn);
			fprintf(fpOut, "%f ", aux);
		}
		fprintf(fpOut, "\n");
	}

	fclose(fpIn);
	fclose(fpOut);
	result++;

	return 0;
}
