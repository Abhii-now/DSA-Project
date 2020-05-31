#include <assert.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
int** adjMatrix;
int* isSP;
int* isInfected;

int doExperiments(int, int, int, int);  // performs
int randomYes(); /* randomly marks the required number of nodes in the matrix
                     as service providers.*/
// void initadjMatrix(int, int*); /*initializes a n*n adjacent matrix*/
int biasedYes(int, int);
int checkInfected(int);
int countCommonPrimeFactors(int, int);
int countPrimeFactors(int);
int gcd(int, int);
int countIP(int);
void printtable(int, int, int, double, double, double, double, double, double, double, double);
