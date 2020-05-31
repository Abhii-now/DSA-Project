
#include "headers.h"

int main(void) {
  srand(time(0));
  int results[10] = {0}, pop = 2000, perSP = 3, socdis = 0, ip = 0,
      infection = 0;
  double sum = 0;                   // initialisation of different variables and arrays as per requirement
  double res3[4] = {0.0};
  double stddev[4] = {0.0};
  // int temp = doExperiments(2000, 3, 33, 5);

  // printf("%d", temp);
  int k = 0;
  for (int i = 0; i < 4; i++) {
    switch (i) {
      case 0:
        pop = 2000;
        infection = 5;
        perSP = 3;
        break;
      case 1:
        pop = 2000;
        infection = 100;
        perSP = 8;
        break;
      case 2:
        pop = 5000;
        infection = 30;
        perSP = 3;
        break;
      case 3:
        pop = 10000;
        infection = 100;
        perSP = 8;
        break;
      default:
        break;
    }
    // switch (pop) {
    //   case 2000:
    //     perSP = 3;
    //     break;
    //   case 5000:
    //     perSP = 5;
    //     break;
    //   case 10000:
    //     perSP = 3;
    //     break;
    //   default:
    //     break;
    // }
    for (int k = 0; k < 4; k++) {
      sum = 0;
      switch (k) {
        case 0:
          socdis = 0;
          break;
        case 1:
          socdis = 50;

          break;
        case 2:
          socdis = 33;
          break;
        case 3:
          socdis = 49;
          break;
        default:
          break;
      }

      for (int l = 0; l < 10; l++) {
        printf(" pop = %d perSP = %d iteration = %d infection = %d \n", pop,
               perSP, l, infection);
        results[l] = doExperiments(pop, perSP, socdis, infection);
        sum += results[l];
      }
      res3[k] = sum / 10;  // res3[] stores the average of these 10 iterations
      for (int i2 = 0; i2 < 10; i2++) {
        stddev[k] += (float)pow((float)results[i2] - res3[k], 2); 
      }                    // calculation of standard deviation for each case
      stddev[k] /= 10.0;
      stddev[k] = sqrt(stddev[k]);
      printf("stddev : %f for k : %d is", stddev[k], k);
    }
    ip = countIP(pop);
    printtable(pop, perSP, infection, res3[0], res3[1], res3[2], res3[3],
               stddev[0], stddev[1], stddev[2], stddev[3]);
    for (int i = 0; i < 4; i++)
      stddev[i] = 0;
  }

  return 0;
}
