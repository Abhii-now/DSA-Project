#include <bits/stdc++.h>
int numSP;
int** adjMatrix;
int* isSP;
int* isInfected;

int doExperiments(int, int, int, double);  // performs
int randomYes(); /* randomly marks the required number of nodes in the matrix
                     as service providers.*/
// void initadjMatrix(int, int*); /*initializes a n*n adjacent matrix*/
int biasedYes(int, int);
int checkInfected(int);
int countCommonPrimeFactors(int, int);
int countPrimeFactors(int);
int gcd(int, int);
int countIP(int);
void printtable(int, int, double, double, double, double, double, double,
                double, double);

int main(void) {
    srand(time(0));
    int results[10] = {0}, pop = 2000, perSP = 0, socdis = 0, ip = 0,
        infection = 0;
    double prob = 0;
    double sum = 0;  // initialisation of different variables and arrays as per
                     // requirement
    double res3[3] = {0.0};
    double stddev[3] = {0.0};
    // int temp = doExperiments(2000, 3, 33, 5);

    // printf("%d", temp);
    int k = 0;
    for (int i = 0; i < 3; i++) {
        switch (i) {
            case 0:
                pop = 2000;
                infection = 100;
                prob = 0.25;
                break;
            case 1:
                pop = 2000;
                infection = 100;
                prob = 0.5;
                break;
            case 2:
                pop = 2000;
                infection = 100;
                prob = 0.75;
                break;
            default:
                break;
        }
        for (int k = 0; k < 3; k++) {
            sum = 0;
            switch (k) {
                case 0:
                    socdis = 0;
                    break;
                case 1:
                    socdis = 50;

                    break;
                case 2:
                    socdis = 75;
                    break;
                default:
                    break;
            }

            for (int l = 0; l < 10; l++) {
                printf(" pop = %d iteration = %d infection = %d \n", pop, l,
                       infection);
                results[l] = doExperiments(pop, socdis, infection, prob);
                sum += results[l];
            }
            res3[k] =
                sum / 10;  // res3[] stores the average of these 10 iterations
            for (int i2 = 0; i2 < 10; i2++) {
                stddev[k] += (double)pow((double)results[i2] - res3[k], 2);
            }  // calculation of standard deviation for each case
            stddev[k] /= 10.0;
            stddev[k] = sqrt(stddev[k]);
            printf("stddev : %f for k : %d is", stddev[k], k);
        }
        ip = countIP(pop);
        printtable(pop, infection, res3[0], res3[1], res3[2], res3[3],
                   stddev[0], stddev[1], stddev[2], stddev[3]);
        for (int i = 0; i < 4; i++) stddev[i] = 0;
    }

    return 0;
}

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
        if (i == total) i = 0;
    }
}

void setinitInfected(int total, int infected) {
    isInfected = (int*)malloc(sizeof(int) * total);
    assert(isInfected != NULL);
    setRandom(total, infected, isInfected);
    std::cout << countIP(total) << '\n';
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
        if (randomYes() == 1) return 1;

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
        while (x % 2 == 0) x = x / 2;
    }

    // x must be odd at this point.  So we
    // can skip one element (Note i = i +2)
    for (int i = 3; i <= sqrt(x); i = i + 2) {
        if (x % i == 0) {
            // While i divides x, print i and
            // divide x
            res++;
            while (x % i == 0) x = x / i;
        }
    }

    // This condition is to handle the case
    // when x is a prime number greater than 2
    if (x > 2) res++;

    if (res == 0) res = 1;
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
    if (b == 0) return a;
    return gcd(b, a % b);
}
int rand50() {
    // rand() function will generate odd or even
    // number with equal probability. If rand()
    // generates odd number, the function will
    // return 1 else it will return 0.
    return rand() & 1;
}

// Random Function to that returns 1 with 75%
// probability and 0 with 25% probability using
// Bitwise OR
int rand75() { return rand50() | rand50(); }
int rand25() { return rand50() & rand50(); }

void performInteractions(int pop, int normal_interactions, double prob) {
    int count_normal = 0;
    int count_service = 0;
    int i = 0;
    while (count_normal < normal_interactions) {
        i++;
        if (i >= pop) i = 0;
        for (int j = i + 1; j < pop; j++) {
            if (biasedYes(i, j) == 1) {
                if (adjMatrix[i][j] == 0) {
                    adjMatrix[i][j] = adjMatrix[j][i] = 1;
                    if (isInfected[i] == 1 || isInfected[j] == 1) {
                        if (prob == 0.5) {
                            int temp = rand50();
                            isInfected[i] = temp | isInfected[i];
                            isInfected[j] = temp | isInfected[j];
                        }
                        if (prob == 0.25) {
                            int temp = rand25();
                            isInfected[i] = temp | isInfected[i];
                            isInfected[j] = temp | isInfected[j];
                        }
                        if (prob == 0.75) {
                            int temp = rand75();
                            isInfected[i] = temp | isInfected[i];
                            isInfected[j] = temp | isInfected[j];
                        }
                    }
                    count_normal++;
                }
            }
        }
    }
}

int doExperiments(int pop, int distance, int infected, double prob) {
    initadjMatrix(pop, &adjMatrix);
    setinitInfected(pop, infected);
    distance = 100 - distance;
    int normal_interactions = (pop)*20 * (distance) / (100 * 2);
    performInteractions(pop, normal_interactions, prob);
    int count = countIP(pop);
    printf(" ****** infected are = %d ******* \n", count);

    return count;
}

// new function added below
int countIP(int pop) {
    int count = 0;
    for (int i = 0; i < pop; i++) {
        if (isInfected[i] == 1) count++;
    }
    return count;
}
void printtable(int population, int ip, double t100, double t50, double t33,
                double t49, double stddev1, double stddev2, double stddev3,
                double stddev4) {
    printf("\n");
    printf("        | Description \t                               | Value \n");
    printf("        | ---------------------------------------------|\n");
    printf("        | Population of town                        -> | %d \n",
           population);
    printf("        | ---------------------------------------------|\n");
    printf("        | Count of known infected persons           -> | %d \n",
           ip);
    printf("        | ---------------------------------------------| \n");
    printf(
        "        | Without any social distancing (T100)      -> | %f , %f \n",
        t100, stddev1);
    printf("        | ---------------------------------------------| \n");
    printf("        | With social distancing reducing contacts     |\n");
    printf(
        "        | to 50 percent (T50)                       -> | %f , %f \n",
        t50, stddev2);
    printf("        | ---------------------------------------------| \n");
    printf("        | With social distancing reducing contacts     |\n");
    printf(
        "        | to 75 per cent (T75)                      -> | %f , %f \n",
        t33, stddev3);
    printf("        | ---------------------------------------------| \n");
}
