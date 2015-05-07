#ifndef _SGCTREE_H_
#define _SGCTREE_H_

#include "gqueue.h"
#include "set.h"
#include "subgraph.h"

// ---- Component tree for built from Subgraph ------------
typedef struct _sgctnode {
  int  level;   /* gray level */
  int  comp;    /* representative pixel of this node */
  int  dad;     /* dad node in the maxtree */
  int *son;     /* son nodes in the maxtree */
  int  numsons; /* number of sons in the maxtree */
  int  size;    /* number of pixels of the node */
} SgCTNode;

typedef struct _sgctree {
  SgCTNode *node;     /* nodes of the mtree */
  int      *cmap;     /* component map */
  int       root;     /* root node of the mtree */
  int       numnodes; /* number of nodes of the maxtree */
} SgCTree;


SgCTree *CreateSgMaxTree(Subgraph *g);
void DestroySgCTree(SgCTree **ctree);
int SgAncestor(int *dad, int *cmap, int rq);
int SgRepresentative(int *cmap, int p);
void SgCumSize(SgCTree *ctree, int i);
int *SgAreaOpen(Subgraph *g, int thres);
int SgAreaLevel(SgCTree *ctree, int *level, int i, int thres);
int *SgVolumeOpen(Subgraph *g, int thres);
int SgVolumeLevel(SgCTree *ctree, int *level, int i, int thres, int cumvol);

#endif
