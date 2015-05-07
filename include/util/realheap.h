#ifndef _REALHEAP_H_
#define _REALHEAP_H_

#include "common.h"
#include "gqueue.h"

/* Auxiliary for RealHeap */
#define HEAP_DAD(i) ((i - 1) / 2)
#define HEAP_LEFTSON(i) (2 * i + 1)
#define HEAP_RIGHTSON(i) (2 * i + 2)


typedef struct _realheap {
  double *cost;
  char *color;
  int *pixel;
  int *pos;
  int last;
  int n;
  char removal_policy; /* 0 is MINVALUE and 1 is MAXVALUE */
} RealHeap;


void SetRemovalPolicyRealHeap(RealHeap *H, char policy);
char IsFullRealHeap(RealHeap *H);
char IsEmptyRealHeap(RealHeap *H);
RealHeap *CreateRealHeap(int n, double *cost);
void DestroyRealHeap(RealHeap **H);
char InsertRealHeap(RealHeap *H, int pixel);
char RemoveRealHeap(RealHeap *H, int *pixel);
void UpdateRealHeap(RealHeap *H, int p, double value);
void GoUpRealHeap(RealHeap *H, int i);
void GoDownRealHeap(RealHeap *H, int i);
void ResetRealHeap(RealHeap *H);

#endif



