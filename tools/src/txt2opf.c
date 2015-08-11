#include <stdio.h>
#include <stdlib.h>
#include "OPF.h"

int main(int argc, char **argv){

	if (argc != 3) 
	{
		fprintf(stderr,"\nusage txt2opf <P1> <P2>\n");
		fprintf(stderr,"\nP1: input file name in the OPF ASCII format");
		fprintf(stderr,"\nP2: output file name in the OPF binary format\n");
		exit(-1);
	}

	fprintf(stderr, "\nProgram to convert files written in the OPF ASCII format to the OPF binary format.");

	FILE *fpIn = NULL,*fpOut = NULL;
	int n, nfeats, nclasses, i,j, id,label;
	float aux;

	fpIn = fopen(argv[1],"r");
	fpOut = fopen(argv[2],"wb");

	/*writing the number of samples*/
	if (fscanf(fpIn,"%d",&n) != 1) {
	  fprintf(stderr,"Could not read number of samples");
	  exit(-1);
	}
	fprintf(stderr, "\n number of samples: %d",n);
	fwrite(&n,sizeof(int),1,fpOut);

	/*writing the number of classes*/
	if (fscanf(fpIn,"%d",&nclasses) != 1) {
	  fprintf(stderr,"Could not read number of classes");
	  exit(-1);
	}

 	fprintf(stderr, "\n number of classes: %d",nclasses); 
	fwrite(&nclasses,sizeof(int),1,fpOut);

	/*writing the number of features*/
	if (fscanf(fpIn,"%d",&nfeats) != 1) {
	  fprintf(stderr,"Could not read number of features");
	  exit(-1);
	}

	fprintf(stderr, "\n number of features: %d",nfeats);
	fwrite(&nfeats,sizeof(int),1,fpOut);
	
	/*writing data*/
	for(i = 0; i < n; i++)	{
	  if (fscanf(fpIn,"%d",&id) != 1) {
	    fprintf(stderr,"Could not read sample id");
	    exit(-1);
	  }
	  fwrite(&id,sizeof(int),1,fpOut);
	  
	  if (fscanf(fpIn,"%d",&label) != 1) {
	    fprintf(stderr,"Could not read sample label");
	    exit(-1);
	  }
	  fwrite(&label,sizeof(int),1,fpOut);
	  
	  for(j = 0; j < nfeats; j++){
	    if (fscanf(fpIn,"%f",&aux) != 1) {
	      fprintf(stderr,"Could not read sample features");
	      exit(-1);
	    }

	    fwrite(&aux,sizeof(float),1,fpOut);
	  }
	}


	fclose(fpIn);
	fclose(fpOut);

	return 0;
}
