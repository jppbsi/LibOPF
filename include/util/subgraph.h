#ifndef _SUBGRAPH_H_
#define _SUBGRAPH_H_

#include "common.h"
#include "set.h"

/*--------- Data types ----------------------------- */
typedef struct _snode {
  float pathval; //path value
  float dens;    //node density
  float radius;   // maximum distance among the k-nearest neighbors in
		  // the training set. It is used to propagate
		  // clustering labels to testing nodes)
  int   label;   //node label
  int   root;    //root node
  int   pred;    //predecessor node
  int   truelabel; //true label if it is known
  long int   position;  //index in the feature space
  float *feat;    //feature vector
  char  status;  //0 - nothing, 1 - prototype
  char  relevant; //0 - irrelevant, 1 - relevant

  int nplatadj; //holds the amount of adjacent nodes on plateaus
                //It is used to optimize opf_BestkMinCut
                //because a knn graph need only be built
                //for kmax, but the opf_PDF and opf_NormalizedCut computation
                //need only be done for the current k,
                //or until k+nplatadj is reached.
  Set   *adj;    //adjacency list for knn graphs
} SNode;

typedef struct _subgraph {
  SNode *node;   //nodes of the image/scene subgraph
  int   nnodes;  //number of nodes
  int   nfeats;  //number of features
  int   bestk;   //number of adjacent nodes
  int   nlabels; //number of clusters
  float df;      //radius in the feature space for density computation
  float mindens; //minimum density value
  float maxdens; //maximum density value
  float K;       //Constant for opf_PDF computation
  int  *ordered_list_of_nodes; // Store the list of nodes in the increasing order of cost for speeding up supervised classification.
} Subgraph;

/*----------- Constructor and destructor ------------------------*/
Subgraph *CreateSubgraph(int nnodes); //Allocates nodes without features
void DestroySubgraph(Subgraph **sg); //Deallocates memory for subgraph

void WriteSubgraph(Subgraph *g, char *file); //write subgraph to disk
Subgraph *ReadSubgraph(char *file);//read subgraph from opf format file
Subgraph *CopySubgraph(Subgraph *g);//Copy subgraph (does not copy Arcs)

void CopySNode(SNode *dest, SNode *src, int nfeats); //Copy nodes
void SwapSNode(SNode *a, SNode *b); //Swap nodes
#endif // _SUBGRAPH_H_
