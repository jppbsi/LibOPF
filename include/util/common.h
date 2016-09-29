#ifndef _COMMON_H_
#define _COMMON_H_

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <limits.h>
#include <float.h>
#include <sys/time.h>
#include <time.h>

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

#define IM1 2147483563
#define IM2 2147483399
#define AM (1.0/IM1)
#define IMM1 (IM1-1)
#define IA1 40014
#define IA2 40692
#define IQ1 53668
#define IQ2 52774
#define IR1 12211
#define IR2 3791
#define NTAB 32
#define NDIV (1+IMM1/NTAB)
#define EPS 1.e-14
#define RNMX (1.0-EPS)

/* Common operations */

#ifndef MAX
#define MAX(x,y) (((x) > (y))?(x):(y))
#endif

#ifndef MIN
#define MIN(x,y) (((x) < (y))?(x):(y))
#endif

int    *AllocIntArray(int n);   /* It allocates 1D array of n integers */
float  *AllocFloatArray(int n); /* It allocates 1D array of n floats */

void Error(char *msg,char *func); /* It prints error message and exits
                                     the program. */
void Warning(char *msg,char *func); /* It prints warning message and
                                       leaves the routine. */

void Change(int *a, int *b); /* It changes content between a and b */

double ran(int *idum);
int seedrandinter(int seed); /* It initializes the random number generator */
int RandomInteger(double low, double high); /* It returns a random integer number uniformly distributed within [low,high].
                                              http://www.physics.drexel.edu/courses/Comp_Phys/Physics-306/random.c */
double RandomFloat(double low, double high); /* It returns a random float number uniformly distributed within [low,high].
                                              http://www.physics.drexel.edu/courses/Comp_Phys/Physics-306/random.c */
double RandomGaussian(double mean, double variance); /* It returns a number drawn from a Gaussian distribution */

int BernoulliDistribution(double p); /* It returns a number drawn from Bernoulli distribution with probability p */

#endif