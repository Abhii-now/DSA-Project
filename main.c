int main(void) {
  srand(time(0));	
	int results[6],sum=0;
float avg,stddev=0.0;
  //int temp = doExperiments(2000, 3, 0);

//  printf("%d", temp);
	int k=0;
  for (int i = 0; i < 3; i++) {
  	for(int j=3;j<=5;j+=2)
  	{
	  if(i==0){
	  
    			results[k]=doExperiments(2000,j,0);
    			sum+=results[k];
				k++;
    			
			}
		else if(i==1)
				{
				results[k]=doExperiments(2000,j,33);
    			sum+=results[k];
				k++;
    			
				}
		else if (i==2)
				{
				results[k]=doExperiments(2000,j,50);
				sum+=results[k];
    			k++;	
				}
	}
	
  }
	avg=(float)sum/(10.0);
for(int i=0;i<6;i++)
{
stddev+=pow((float)results[i]-avg,2);
}
stddev/=10.0;
stddev=sqrt(stddev);
printf("The average for 2000 population is %f and standard deviation is %f",avg ,stddev);

avg=0;stddev=0;
sum=0;
k=0;
for (int i = 0; i < 3; i++) {
  	for(int j=3;j<=5;j+=2)
  	{
	  if(i==0){
	  
    			results[k]=doExperiments(5000,j,0);
    			sum+=results[k];
				k++;
    			
			}
		else if(i==1)
				{
				results[k]=doExperiments(5000,j,33);
    			sum+=results[k];
				k++;
    			
				}
		else if (i==2)
				{
				results[k]=doExperiments(5000,j,50);
				sum+=results[k];
    			k++;	
				}
	}
	
  }
	avg=(float)sum/(10.0);
for(int i=0;i<6;i++)
{
stddev+=pow((float)results[i]-avg,2);
}
stddev/=10.0;
stddev=sqrt(stddev);
printf("The average for 5000 population is %f and standard deviation is %f",avg ,stddev);


avg=0;stddev=0;
sum=0;
k=0;
for (int i = 0; i < 3; i++) {
  	for(int j=3;j<=5;j+=2)
  	{
	  if(i==0){
	  
    			results[k]=doExperiments(10000,j,0);
    			sum+=results[k];
				k++;
    			
			}
		else if(i==1)
				{
				results[k]=doExperiments(10000,j,33);
    			sum+=results[k];
				k++;
    			
				}
		else if (i==2)
				{
				results[k]=doExperiments(10000,j,50);
				sum+=results[k];
    			k++;	
				}
	}
	
  }
	avg=(float)sum/(10.0);
for(int i=0;i<6;i++)
{
stddev+=pow((float)results[i]-avg,2);
}
stddev/=10.0;
stddev=sqrt(stddev);
printf("The average for 10000 population is %f and standard deviation is %f",avg ,stddev);
  return 0;
}
