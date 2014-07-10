#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <mpi.h>

using namespace std;

extern double * MakeAIntArray(int arraySize);
extern int array_compare(int N, double * A, double * B);
extern void print(int n, int * A);
extern double read_timer();
extern double * copyArray(int arraySize, double * array);
extern void serial_main(int arraySize, double * array);
extern void pthread_main(int arraySzie, double * array, int threadNumber);
extern double * parallel_top_main(int N, double * array/*, double* overhead,int numPro*/);
//double overhead = 0.0;

int main(int argc, char *argv[])
{
    int numPro;
    int rank;
    double * A;
    double * serialArray;
    double * parallelArray=NULL;
    double time;
    double elapse1, elapse2;
    double overhead;
    elapse1=0; 
    elapse2=0;
    overhead=0;
    MPI_Init(NULL,NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &numPro);
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    
    int N = atoi(argv[1]);
    numPro=atoi(argv[2]);
    
    if(rank==0){
	A=MakeAIntArray(N);// 
	serialArray=copyArray(N, A);
	time=read_timer();
	serial_main(N, serialArray);
	elapse1+=read_timer()-time;
	printf("\nhost number: %d, size: %d\n",numPro, N);
	printf("serial time:%f\n",elapse1);
    }
    if(numPro>1){
	if(rank==0){
		parallelArray=copyArray(N,A);
		time=read_timer();
       		parallelArray=parallel_top_main(N,parallelArray/*,&overhead*/);
		elapse2+=read_timer()-time;
		//print(N,parallelArray);
		printf("parallel time:%f\n",elapse2);
		//printf("overhead: %f\n", overhead);
		printf("speedup: %f\n", elapse1/elapse2);
		//printf("overhead occupy: %f\n", overhead/elapse2);
	}else{
		parallel_top_main(N,parallelArray/*,&overhead*/);
		//printf("first here,%d\n",rank);
	}
    }
    MPI_Finalize();
    if(rank==0&&array_compare(N,serialArray,parallelArray)==1){
		fprintf(stderr,"Error\n");
		exit(-1);
    }
    //printf("here,%d\n",rank);
    return 0;
}
