#include <math.h>

#include "headers.h"

// int population = 2000;
// int adjMatrix[population][population];

void printMatrix(int edgeSize) {
  for (int i = 0; i < edgeSize; i++) {
    printf("\n");
    for (int j = 0; j < edgeSize; j++) {
      printf("%d", adjMatrix[i][j]);
    }
  }
}

static void setRandom(int total, int num, int* arr) {
  int count = 0;
  int i = 0;

  while (count < num) {
    if (randomYes() == 1) {
      if (arr[i] == 0) {
        arr[i] = 1;
        count++;
      }
    }
    i++;
    if (i == total)
      i = 0;
  }
}

void setSP(int total, int per) {
  int numSP;
  int i = 0;
  isSP = (int*)malloc(sizeof(int) * total);
  assert(isSP != NULL);
  numSP = total * per / 100;
  setRandom(total, numSP, isSP);
}

void setinitInfected(int total) {
  isInfected = (int*)malloc(sizeof(int) * total);
  assert(isInfected != NULL);
  for (int i = 0; i < total; i++) {
    isInfected[i] = randomYes();
  }
}

int randomYes() {
  {
    int arr[1000];
    arr[0] = 1;
    // for (int i = 1; i < 1000; i++) {
    //   arr[i] = 0;
    // }
    int temp = rand() % 1000;
    return arr[temp];
  }
}

int biasedYes(int x, int y) {
  /* Where x and y and indices of persons in
  Adjacency matrix. */
  int common = countCommonPrimeFactors(x + 1001, y + 1001);
  /* Define function countPrimeFactors() that computes the
  Count of prime factors common in two arguments.
  More prime factor they have in common, more
  often the pair meets!
  */
  // Return biased interaction
  while (common--)
    if (randomYes() == 1)
      return 1;

  return 0;
}

void initadjMatrix(int edgeSize, int*** arr) {
  (*arr) = (int**)malloc(sizeof(int*) * edgeSize);

  for (int i = 0; i < edgeSize; i++) {
    (*arr)[i] = (int*)malloc(sizeof(int) * edgeSize);
    for (int j = 0; j < edgeSize; j++) {
      (*arr)[i][j] = 0;
    }
  }
}
// A function to count all prime factors of
// a given number x
int countPrimeFactors(int x) {
  int res = 0;
  if (x % 2 == 0) {
    res++;

    // Print the number of 2s that divide x
    while (x % 2 == 0)
      x = x / 2;
  }

  // x must be odd at this point.  So we
  // can skip one element (Note i = i +2)
  for (int i = 3; i <= sqrt(x); i = i + 2) {
    if (x % i == 0) {
      // While i divides x, print i and
      // divide x
      res++;
      while (x % i == 0)
        x = x / i;
    }
  }

  // This condition is to handle the case
  // when x is a prime number greater than 2
  if (x > 2)
    res++;

  if (res == 0)
    res = 1;
  return res;
}

// Count of common prime factors
int countCommonPrimeFactors(int a, int b) {
  // Get the GCD of the given numbers
  int temp = gcd(a, b);

  // Count prime factors in GCD
  return countPrimeFactors(temp);
}

int gcd(int a, int b) {
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int doExperiments(int population, int perSP, int distancing) {
  initadjMatrix(population, &adjMatrix);

  int flag = 0;
  int interactions = 0;
  int j = 0;
  setSP(population, perSP);
  // setinitInfected(population);

  for (int i = 0; i < population; i++) {
    int count = 0;
    int temp;
    if (isSP[i] == 1) {
      if (perSP < 5)
        interactions = population * 5 / 100;
      else {
        interactions = population * 3 / 100;
      }
    } else {
      interactions = 20;
      interactions = (interactions * distancing / 100);
      // printf("%d\n", interactions);
      count = (interactions * i) / (population - 1);
      // printf("count = %d    i = %d\n", count, i);
      j = i + 1;
      while (count < interactions) {
        assert(j < population);

        //  printf("%d   %d  %d\n", i, j, count);
        temp = biasedYes(i, j);
        if (temp == 1) {
          if (adjMatrix[i][j] != 1)
            if (isSP[j] != 1) {
              count++;
              adjMatrix[i][j] = 1;
              adjMatrix[j][i] = adjMatrix[i][j];
            } else {
              adjMatrix[i][j] = 1;
              adjMatrix[j][i] = adjMatrix[i][j];
            }
        }

        j++;
        if (j >= population)
          j = i + 1;
      }
    }
    // free(adjMatrix);
    return checkInfected(population);
  }
  // int reach[2000][2000];
}
int checkInfected(int population) {
  int** reach;
  initadjMatrix(population, &reach);
  clock_t t;
  t = clock();
  int checkNeeded[population];
  /* reach[][] will be the output matrix that will finally have the
       shortest distances between every pair of vertices */
  int i, j, k;
  int count = 0;

  setinitInfected(population);

  /* Initialize the solution matrix same as input graph matrix. Or
     we can say the initial values of shortest distances are based
     on shortest paths considering no intermediate vertex. */
  // reach[1][1] = 1;
  for (int i = 0; i < population; i++) {
    for (int j = 0; j < population; j++) {
      reach[i][j] = adjMatrix[i][j];
    }
  }

  /* Add all vertices one by one to the set of intermediate vertices.
    ---> Before start of a iteration, we have reachability values for
         all pairs of vertices such that the reachability values
         consider only the vertices in set {0, 1, 2, .. k-1} as
         intermediate vertices.
    ----> After the end of a iteration, vertex no. k is added to the
          set of intermediate vertices and the set becomes {0, 1, .. k} */
  for (k = 0; k < population; k++) {
    /// Pick all vertices as source one by on
    for (i = k; i < population; i++) {
      // Pick all vertices as destination for the
      // above picked source

      for (j = 0; j < population; j++) {
        // If vertex k is on a path from i to j,
        // then make sure that the value of reach[i][j] is 1
        reach[i][j] = reach[i][j] || (reach[i][k] && reach[k][j]);
      }
    }
  }
  for (int i = 0; i < population; i++) {
    if (isInfected[i] == 1)
      for (int j = 0; j < population; j++) {
        if (reach[i][j] == 1) {
          checkNeeded[j] = 1;
        }
      }
  }

  for (int i = 0; i < population; i++) {
    if (checkNeeded[i] == 1) {
      count++;
    }
  }
  t = clock() - t;
  double time_taken = ((double)t) / CLOCKS_PER_SEC;  // in seconds

  printf("fun() took %f seconds to execute \n", time_taken);
  // free(reach);
  // free(adjMatrix);
  return count;
}

void printtable(){

    printf("          Description \t                                Value \n");
    printf("          ----------------------------------------- \n");
    printf("          Population of town                        ->  %d \n", 2000 );
    printf("          ----------------------------------------- \n");
    printf("          Count of major service providers          ->  %d \n",  3);
    printf("          ----------------------------------------- \n");
    printf("          Count of known infected persons           ->  %d  \n", 5);
    printf("          ----------------------------------------- \n");
    printf("          Result                                    ->  %d \n" , 20);
    printf("          ----------------------------------------- \n");
    printf("          Without any social distancing (T100)      ->  %d \n" , 13);
    printf("          ----------------------------------------- \n");
    printf("          With social distancing reducing contacts\n");
    printf("          to 50 percent (T50)                       ->  %d \n" , 50); 
    
    printf("          ----------------------------------------- \n");
    printf("          With social distancing reducing contacts\n"); 
    printf("          to 33 per cent (T33)                      ->  %d \n" , 33);
    printf("          ----------------------------------------- \n");
    printf("          With social distancing reducing contacts\n");
    printf("          to 50 percent with assigned service\n");
    printf("          provider (TC)                             ->  %d \n" , 49);
    printf("          ----------------------------------------- \n");        

}
