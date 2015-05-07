#ifndef _SET_H_
#define _SET_H_

#include "common.h"

typedef struct _set {
  int elem;
  struct _set *next;
} Set;

void InsertSet(Set **S, int elem);
int  RemoveSet(Set **S);
int  GetSetSize(Set *S);
Set *CloneSet(Set *S);
void DestroySet(Set **S);

#endif
