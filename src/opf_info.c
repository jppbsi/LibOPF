#include "OPF.h"
#include <stdio.h>
#include <time.h>

int main(int argc, char **argv){
	fflush(stdout);
	fprintf(stdout, "\nProgram that gives information about the OPF file\n");
	fprintf(stdout, "\nIf you have any problem, please contact: ");
	fprintf(stdout, "\n- alexandre.falcao@gmail.com");
	fprintf(stdout, "\n- papa.joaopaulo@gmail.com\n");
	fprintf(stdout, "\nLibOPF version 2.0 (2009)\n");
	fprintf(stdout, "\n"); fflush(stdout);

	if(argc != 2) {
		fprintf(stderr, "\nusage opf_info <P1>");
		fprintf(stderr, "\nP1: OPF file\n");
		exit(-1);
	}

	Subgraph *g = NULL;
	FILE *fp = NULL;
	int ndata, nfeats, nlabels;
	char msg[128];
	
	if((fp = fopen(argv[1], "rb")) == NULL){
		sprintf(msg, "%s%s", "Unable to open file ", argv[1]);
		Error(msg,"opf_info");
	}

        if (fread(&ndata, sizeof(int), 1, fp) != 1) {
	  fprintf(stderr,"\n Could not read number of samples");
	  exit(-1);
	}
	if (fread(&nlabels, sizeof(int), 1, fp) != 1) {
	  fprintf(stderr,"\n Could not read number of labels");
	  exit(-1);
	}

	if (fread(&nfeats, sizeof(int), 1, fp) != 1){
	  fprintf(stderr,"\n Could not read number of features");
	  exit(-1);
	}
	
	fprintf(stdout, "\nInformations about %s file\n --------------------------------", argv[1]);
	fprintf(stdout,"\nData size: %d",ndata);
	fprintf(stdout,"\nFeatures size: %d",nfeats);
	fprintf(stdout,"\nLabels number: %d",nlabels);
	fprintf(stdout, "\n--------------------------------\n");

	DestroySubgraph(&g);
	fclose(fp);

	return 0;
}
