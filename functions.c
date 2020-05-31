#include <math.h>
int numSP;

#include "headers.h"

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

  for (int i = 0; i < total; i++) {
    arr[i] = 0;
  }

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
  int i = 0;
  isSP = (int*)malloc(sizeof(int) * total);
  assert(isSP != NULL);
  numSP = total * per / 100;
  setRandom(total, numSP, isSP);
}

void setinitInfected(int total, int infected) {
  isInfected = (int*)malloc(sizeof(int) * total);
  assert(isInfected != NULL);
  setRandom(total, infected, isInfected);
}

int randomYes() {
  int r = rand() % 1000;
  if (r == 0)
    return 1;
  else
    return 0;
}

int biasedYes(int x, int y) {
  /* Where x and y and indices of persons in
  Adjacency matrix. */
  int common = countCommonPrimeFactors(x + 1002, y + 11001);
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

void performInteractions(int pop,
                         int normal_interactions,
                         int service_interactions) {
  int count_normal = 0;
  int count_service = 0;
  int i = 0;
  while (count_normal < normal_interactions ||
         count_service < service_interactions) {
    if (count_service < service_interactions &&
        count_normal < normal_interactions) {
      i++;
      if (i >= pop)
        i = 0;
      for (int j = i + 1; j < pop; j++) {
        if (biasedYes(i, j) == 1) {
          if (adjMatrix[i][j] == 0) {
            adjMatrix[i][j] = adjMatrix[j][i] = 1;
            if (isInfected[i] == 1 || isInfected[j] == 1)
              isInfected[i] = isInfected[j] = 1;
            if (isSP[i] == 1 || isSP[j] == 1)
              count_service++;
            else
              count_normal++;
          }
        }
      }

    } else if (count_normal >= normal_interactions &&
               count_service < service_interactions) {
      i++;
      if (i >= pop)
        i = 0;
      if (isSP[i] == 1) {
        // printf("here : %d", i);

        for (int j = i + 1; j < pop; j++) {
          if (biasedYes(i, j) == 1)
            if (adjMatrix[i][j] != 1) {
              adjMatrix[i][j] = adjMatrix[j][i] = 1;
              if (isInfected[i] == 1 || isInfected[j] == 1)
                isInfected[i] = isInfected[j] = 1;
              count_service++;
            }
        }
      }
    } else if (count_normal < normal_interactions &&
               count_service >= service_interactions) {
      i++;
      if (i >= pop)
        i = 0;
      if (isSP[i] != 1) {
        // printf("here2 : %d", i);

        for (int j = i + 1; j < pop; j++) {
          if (biasedYes(i, j) == 1)
            if (adjMatrix[i][j] != 1) {
              adjMatrix[i][j] = adjMatrix[j][i] = 1;
              if (isInfected[i] == 1 || isInfected[j] == 1) {
                isInfected[i] = isInfected[j] = 1;
              }
              count_normal++;
            }
        }
      }
    }
  }
}

void performInteractionsTC(int pop,
                           int normal_interactions,
                           int service_interactions) {
  int count_normal = 0;
  int count_service = 0;
  int i = 0;
  while (count_normal < normal_interactions ||
         count_service < service_interactions) {
    if (count_service < service_interactions) {
      if (i >= pop)
        i = 0;
      if (isSP[i] == 1) {
        // printf("here : %d", i);

        for (int j = i + 2; j < pop; j = j + 2) {
          if (biasedYes(i, j) == 1)
            if (adjMatrix[i][j] != 1) {
              adjMatrix[i][j] = adjMatrix[j][i] = 1;
              if (isInfected[i] == 1 || isInfected[j] == 1)
                isInfected[i] = isInfected[j] = 1;
              count_service++;
            }
        }
      }
      i++;

    }

    else if (count_normal < normal_interactions &&
             count_service >= service_interactions) {
      if (i >= pop)
        i = 0;
      if (isSP[i] != 1) {
        // printf("here2 : %d", i);

        for (int j = i + 1; j < pop; j++) {
          if (isSP[j] != 1) {
            if (biasedYes(i, j) == 1)
              if (adjMatrix[i][j] != 1) {
                adjMatrix[i][j] = adjMatrix[j][i] = 1;
                if (isInfected[i] == 1 || isInfected[j] == 1) {
                  isInfected[i] = isInfected[j] = 1;
                }
                count_normal++;
              }
          }
        }
      }
      i++;
    }
  }
}

int doExperiments(int pop, int per_service, int distance, int infected) {
  initadjMatrix(pop, &adjMatrix);
  setSP(pop, per_service);
  setinitInfected(pop, infected);
  int service_interaction;
  int flag = 0;

  if (distance == 49) {
    distance = 50;
    flag = 1;
  }
  if (distance == 0)
    distance = 100;
  int normal_interactions = (pop - numSP) * 20 * (distance) / (100 * 2);
  if (per_service < 5)
    service_interaction = numSP * pop * 5 / 200;
  else
    service_interaction = numSP * pop * 3 / 200;

  int interactions = 0;
  if (flag == 0)
    performInteractions(pop, normal_interactions, service_interaction);
  else
    performInteractionsTC(pop, normal_interactions, service_interaction);


  int count = 0;
  for (int i = 0; i < pop; i++) {
    if (isInfected[i] == 1)
      count++;
  }
  printf(" ****** infected are = %d ******* \n", count);

  return count;
}


// new function added below
int countIP(int pop) {
  int count = 0;
  for (int i = 0; i < pop; i++) {
    if (isInfected[i] == 1)
      count++;
  }
  return count;
}
void printtable(int population,
                int sp,
                int ip,
                double t100,
                double t50,
                double t33,
                double t49,
                double stddev1,
                double stddev2,
                double stddev3,
                double stddev4) {
  printf("\n");
  printf("        | Description \t                               | Value \n");
  printf("        | ---------------------------------------------|\n");
  printf("        | Population of town                        -> | %d \n",
         population);
  printf("        | ---------------------------------------------|\n");
  printf("        | Count of major service providers          -> | %d \n", sp);
  printf("        | ---------------------------------------------|\n");
  printf("        | Count of known infected persons           -> | %d \n", ip);
  printf("        | ---------------------------------------------| \n");
  printf("        | Result                                    -> | %d \n", 20);
  printf("        | ---------------------------------------------| \n");
  printf("        | Without any social distancing (T100)      -> | %f , %f \n",
         t100, stddev1);
  printf("        | ---------------------------------------------| \n");
  printf("        | With social distancing reducing contacts     |\n");
  printf("        | to 50 percent (T50)                       -> | %f , %f \n",
         t50, stddev2);
  printf("        | ---------------------------------------------| \n");
  printf("        | With social distancing reducing contacts     |\n");
  printf("        | to 33 per cent (T33)                      -> | %f , %f \n",
         t33, stddev3);
  printf("        | ---------------------------------------------| \n");
  printf("        | With social distancing reducing contacts     |\n");
  printf("        | to 50 percent with assigned service          |\n");
  printf("        | provider (TC)                             -> | %f , %f \n",
         t49, stddev4);
  printf("        | ---------------------------------------------| \n");
}
