#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

extern double * MakeAIntArray(int arraySize);
extern int array_compare(int N, double * A, double * B);
extern void print(int n, double * A);
extern double read_timer();
extern double * copyArray(int arraySize, double * array);
extern void serial_main(int arraySize, double * array);
extern double * pthread_main(int arraySzie, double * array, int threadNumber);

int main(int argc, char *argv[])
{    
	int N = atoi(argv[1]);
	int numRuns=1;	
	double elapse1, elapse2;
	elapse1=0;
	elapse2=0;

  for (int i=0; i< numRuns; i++){
	double * A = MakeAIntArray(N);
	double time=0;
	int threadNumber=atoi(argv[2]);
    
	double * serialArray=copyArray(N, A);
	time=read_timer();
	int testtime=1;
	cout<<"serial"<<endl;
	for(i=0; i<testtime; i++)
	serial_main(N, serialArray);
	elapse1 += read_timer()-time;
	
	//print(N, serialArray);
	
	double * pthreadArray=copyArray(N, A);
	time=read_timer();
	cout<<"parallel"<<endl;
	for(i=0; i<testtime; i++)
	pthreadArray=pthread_main(N, pthreadArray, threadNumber);	
	elapse2 +=read_timer()-time;
	
	if(array_compare(N,serialArray,pthreadArray)==1){
		fprintf(stderr,"Error\n");
		exit(-1);
    	}
   }
  
	printf("total serial   time: %f\n",elapse1/numRuns);
	printf("total parallel time: %f\n",elapse2/numRuns);
	return 0;
}
