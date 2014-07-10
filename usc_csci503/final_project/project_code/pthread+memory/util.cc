#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void exchange(double * a, double * b)
{
	double temp= *b;
	*b=*a;
	*a=temp;

}

void readFile(char* fileName,double* array, int size){
    FILE* file;
    int num=0;
    
    char temp[1026];
    if((file=fopen(fileName, "r"))==NULL){
        fprintf(stderr, "can't open this file\n");
        exit(-1);
    }
    while ((fgets(temp, 1026, file)!=NULL)&&num<size) {
        array[num++]=atof(temp);
    }
    return;
}

void exchange(int * a, int * b)
{
	int temp= *b;
	*b=*a;
	*a=temp;

}

int random(int start, int end)
{
	srand( (unsigned)time( NULL ) );
	return (start+rand()%(end-start+1));
}


double * MakeAIntArray(int arraySize)
{
   double * theArray;
   char fileName[20]="input";
   theArray= (double *)malloc(arraySize*sizeof(double));
   readFile(fileName, theArray, arraySize);

   return theArray;
}

int array_compare(int N, double * A, double * B)
{
	int error=0;
	
	for(int i=0;i<N;i++)
	{
		//printf("i:%d\n",i);
		if(A[i]!=B[i])
		{
			error=1;
			return error;
		}
	}
	
	return error;
}

double * copyArray(int arraySize, double * array)
{
   double * theArray;
   theArray= (double *)malloc(arraySize*sizeof(double));
   
   for(int i=0;i<arraySize;i++)
   {
	  theArray[i]=array[i];
   }
	
	return theArray;
}

double * copyArrayFT(double * array, int from, int to)
{
	double * theArray= (double *)malloc((from-to+1)*sizeof(double));
	int count=0;
	for(int i=from; i<=to; i++)
	{
		theArray[count]=array[i];
		count++;
	}

}

void print(int n, double * A)
{
	for(int i=0;i<n;i++)
	   printf("%f ", A[i]);
	
	printf("\n");

}
