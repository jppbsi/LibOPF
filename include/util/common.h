#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>

/* Error messages */

#define MSG1  "Cannot allocate memory space"
#define MSG2  "Cannot open file"
#define MSG3  "Invalid option"

/* Common data types */
typedef struct timeval timer;

/* Common definitions */

#define PI          3.1415926536
#define INTERIOR    0
#define EXTERIOR    1
#define BOTH        2
#define WHITE       0
#define GRAY        1
#define BLACK       2
#define NIL        -1
#define INCREASING  1
#define DECREASING  0
#define Epsilon     1E-05

/* Common operations */

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y))?(x):(y))
#endif

int    *AllocIntArray(int n);   /* It allocates 1D array of n integers */
double  *AllocFloatArray(int n); /* It allocates 1D array of n doubles */

void Error(char *msg,char *func); /* It prints error message and exits
                                     the program. */
void Warning(char *msg,char *func); /* It prints warning message and
                                       leaves the routine. */

inline void Change(int *a, int *b); /* It changes content between a and b */
int RandomInteger (int low, int high);/* Generates a random number within [low,high].
                                        http://www.ime.usp.br/~pf/algoritmos/aulas/random.html
                                        */

#endif
