#ifndef _GQUEUE_H_
#define _GQUEUE_H_

#include "common.h"

#define MINVALUE   0 /* define queue to remove node with minimum value */
#define MAXVALUE   1 /* define queue to remove node with maximum value */
#define FIFOBREAK 0  /* define queue to solve ambiguity by FIFO */
#define LIFOBREAK 1  /* define queue to solve ambiguity by LIFO */
#define QSIZE     32768

#define SetTieBreak(a,b) a->C.tiebreak=b 
#define SetRemovalPolicy(a,b) a->C.removal_policy=b 

typedef struct _gqnode { 
  int  next;  /* next node */
  int  prev;  /* prev node */
  char color; /* WHITE=0, GRAY=1, BLACK=2 */ 
} GQNode;

typedef struct _gdoublylinkedlists {
  GQNode *elem;  /* all possible doubly-linked lists of the circular queue */
  int nelems;  /* total number of elements */
  int *value;   /* the value of the nodes in the graph */
} GDoublyLinkedLists; 

typedef struct _gcircularqueue { 
  int  *first;   /* list of the first elements of each doubly-linked list */
  int  *last;    /* list of the last  elements of each doubly-linked list  */
  int  nbuckets; /* number of buckets in the circular queue */
  int  minvalue;  /* minimum value of a node in queue */
  int  maxvalue;  /* maximum value of a node in queue */
  char tiebreak; /* 1 is LIFO, 0 is FIFO (default) */
  char removal_policy; /* 0 is MINVALUE and 1 is MAXVALUE */
} GCircularQueue;

typedef struct _gqueue { /* Priority queue by Dial implemented as
                           proposed by A. Falcao */
  GCircularQueue C;
  GDoublyLinkedLists L;
} GQueue;

GQueue *CreateGQueue(int nbuckets, int nelems, int *value);
void   DestroyGQueue(GQueue **Q);
void   ResetGQueue(GQueue *Q);
int    EmptyGQueue(GQueue *Q);
void   InsertGQueue(GQueue **Q, int elem);
int    RemoveGQueue(GQueue *Q);
void   RemoveGQueueElem(GQueue *Q, int elem);
void   UpdateGQueue(GQueue **Q, int elem, int newvalue);
GQueue *GrowGQueue(GQueue **Q, int nbuckets);

#endif







