#include "headers.h"

int main(void) {
srand(time(0));	
int results[10],sum=0;
float avg,stddev=0.0;
int temp = doExperiments(2000, 3, 0);

printf("%d", temp);
for (int i = 0; i < 10; i++){
    results[i]=doExperiments(2000,3,0);
  	sum+=results[i];
    }
avg=(float)sum/(10.0);
for(int i=0;i<10;i++)
    {
    stddev+=pow((float)results[i]-avg,2);
    }
stddev/=10.0;
stddev=sqrt(stddev);
  return 0;
