#include "headers.h"
int main(void) {
  srand(time(0));

  int temp = doExperimentsFix(2000, 3, 50);
  printf("\ncount : %d", temp);
  int results[10], sum = 0, pop = 2000, perSP = 3, socdis = 0, res2[3] = {0l};
  float avg, stddev = 0.0, avg2 = 0.0;
  //   //int temp = doExperiments(2000, 3, 0);

  // //  printf("%d", temp);
  int k = 0;
  for (int i = 0; i < 3; i++) {
    sum = 0;
    switch (i) {
      case 0:
        pop = 2000;
        break;
      case 1:
        pop = 5000;
        break;
      case 2:
        pop = 10000;
        break;
      default:
        break;
    }
    for (int perSP = 3; perSP <= 5; perSP += 2) {
      for (int k = 0; k < 3; k++) {
        switch (k) {
          case 0:
            socdis = 0;
            break;
          case 1:
            socdis = 33;
            break;
          case 2:
            socdis = 50;
            break;
          default:
            break;
        }

        for (int l = 0; l < 10; l++) {
          result[l] = doExperiments(pop, perSP, socdis);
          sum += result[l];
        }
      }
    }
    avg = (float)sum / 60.0;
    res2[i] = avg;
    avg2 += res2[i];
  }
  avg2 = avg2 / 3.0;
  for (int i = 0; i < 3; i++) {
    stddev += pow((float)res2[i] - avg2, 2);
  }
  stddev /= 3;
  stddev = sqrt(stddev);
  return 0;
}
