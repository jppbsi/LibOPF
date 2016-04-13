#include "OPF.h"

#define N 5000

struct label{
	int value;
	int real;
	struct label *next;
};

struct data {
	int ndata;
	int nlabels;
	int nfeats;
};

void InsertLabel(struct label **node, int real, int value){
	struct label *p = calloc(1, sizeof(struct label));
	p->real = real;
	p->value = value;
	if(*node == NULL){
		p->next = NULL;
	}
	else{
		p->next = *node;
	}
	*node = p;
}

/*int FindLabel(struct label *node, int value){
	struct label *p = node;

	while(p!=NULL){
		if(p->real == value)
			return p->value;
		p = p->next;
	}
	return 0;
}*/

struct data CountData(char *file){
	struct data d;
	int i, j = 0, k;
	char buffer[N];
	char c[N];
	char *t;
	FILE *fp = NULL;
	
	d.ndata = d.nlabels = d.nfeats = 0;
	
	fp = fopen(file,"r");
		
	while (fgets (buffer, sizeof(buffer), fp)){
		strcpy(c, buffer);
		i = atoi(strtok(c, " "));
		strcpy(c, buffer);
		t = strtok(c, " ");
		t = strtok(NULL, ":");
		while (t != NULL){
			k = atoi(t);
			if (k > d.nfeats)
				d.nfeats = k;
			t = strtok(NULL, " ");
			t = strtok(NULL, ":");
		}
		if (i > d.nlabels)
			d.nlabels = i;
		j++;
	}
	d.ndata = j;
	fclose(fp);
	return d;
}

int main(int argc, char** argv){
	if(argc != 3){
		fprintf(stderr, "\nusage svm2opf <input libsvm file> <output libopf file>\n");
		exit(-1);
	}
	
	FILE *file = fopen(argv[1],"r");
	int i;
	int index, label;
	//int aux = 1;
	float value;
	char *line = calloc(N, sizeof(char));
	struct data d;
	char *seg;
	
	d = CountData(argv[1]);
	fprintf(stderr, "Allocating memory...\n");
	Subgraph *graph = CreateSubgraph(d.ndata);
	fprintf(stderr, "OK.\n\n");
	//struct label *node = NULL;
	graph->nlabels = d.nlabels;
	graph->nfeats = d.nfeats;
	fprintf(stderr, "Creating graph...\n");
	for(i=0; i<d.ndata; i++){
		fgets(line, N, file);
		graph->node[i].position = i;
		seg = strtok(line, " ");
		label = atoi(seg);
		//fprintf(stderr,"%d\n", label);
		graph->node[i].truelabel = label;
		/*fprintf(stderr,"%d\n", graph->node[i].truelabel);
		if(graph->node[i].truelabel == 0){
			graph->node[i].truelabel = aux;
			InsertLabel(&node, label, aux);
			aux++;
		}*/
		graph->node[i].feat = calloc(d.nfeats, sizeof(float));
		while(seg != NULL){
			seg = strtok(NULL, ":\n");
			if(seg==NULL)
				break;
			index = atoi(seg);
			seg = strtok(NULL, " \n");
			value = atof(seg);
			//fprintf(stderr, "%d %f\n", index, value);
			graph->node[i].feat[index-1] = value;
		}
	}
	fprintf(stderr, "OK.\n\n");
	fprintf(stderr, "Writing graph to OPF format...\n");
	WriteSubgraph(graph, argv[2]);
	fprintf(stderr, "\nOK.\n\n");
	DestroySubgraph(&graph);
	fclose(file);
	free(line);
}
