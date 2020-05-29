int main(void) {
  srand(time(0));	
	int results[10]={0},sum=0,pop=2000,perSP=3,socdis=0,ip=0,res3[4]={0};
    float stddev[4]={0.0};
  //int temp = doExperiments(2000, 3, 0);

//  printf("%d", temp);
	int k=0;
  for (int i = 0; i < 3; i++) {
  	switch(i)
	  	  {
	  		case 0:	pop=2000;
	  				break;
	  		case 1: pop=5000;
	  				break;
	  		case 2: pop=10000;
	  				break;
	  		default:break;
		  }
  	switch(pop)
  		{
  	  case 2000:perSP=3;
					break;
		  case 5000:perSP=5;
		  			break;
		  case 10000:perSP=3;
		  			break;
		  default:break;	
		}
	  for(int k=0;k<4;k++)
	  {sum=0;	
	  switch(k)
	  	  {
	  		case 0:socdis=0;
	  				break;
	  		case 1:socdis=33;
	  				break;
	  		case 2:socdis=50;
	  				break;
	  		case 3:socdis=49;
	  				break;
	  		default:break;
		  }
		  
		  for(int l=0;l<10;l++)
		  {
		  	results[l]=doExperiments(pop,perSP,socdis);
		  	sum+=results[l];
	   	  }
	   	  res3[k]=sum/10;//res3[] stores the average of these 10 iterations
	  	  for(int i2=0;i2<10;i2++)
		{
		stddev[k]+=pow((float)results[i2]-res3[k],2);
		}
		stddev[k]/=10.0;
		stddev[k]=sqrt(stddev[k]);	
	  }
	  ip=countIP(pop);
	  printtable(pop,perSP,ip,res3[0],res3[1],res3[2],res3[3],stddev[0],stddev[1],stddev[2],stddev[3]);
	  	  
  }

  return 0;
}
