#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include "myHeap.h"
#include "header.h"
#include "math.h"

using namespace std;

extern double * MakeAIntArray(int arraySize);
extern int array_compare(int N, double * A, double * B);
extern void print(int n, int * A);
extern double read_timer();
extern double * copyArray(int arraySize, double * array);
extern void serial_main(int arraySize, double * array);
extern void quicksort(double * A, int p, int r);
extern double * copyArrayFT(double * array, int from, int to);

double * memoryOpt_main(int arraySize, double * array, int blockSize)
{
	int number=(int)ceil((float)arraySize/(float)blockSize);
	int ptr[number];
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*number);
	
	for(int i=0; i<number-1; i++)
	{
		quicksort(array, i*blockSize, (i+1)*blockSize-1);
		ptr[i]=(i+1)*blockSize-1;
		heap[i].value=array[ptr[i]];
		heap[i].index=i;
	}

	quicksort(array, (number-1)*blockSize, arraySize-1);
	ptr[number-1]=arraySize-1;
	heap[number-1].value=array[ptr[number-1]];
	heap[number-1].index=number-1;
	
	
	
	int heapSize=number;
	int counter=0;
	double * sortedArray=(double *)malloc(sizeof(double)*arraySize);
	build_max_heap(heap, heapSize);
	//printHeap(heap, heapSize);
	
	
	while(counter!=arraySize)
	{
		heapNode max=heap_extract_max(heap, &heapSize);
		counter++;
		sortedArray[arraySize-counter]=max.value;
		ptr[max.index]--;
		if(ptr[max.index]>= (max.index * blockSize))
		{
			max.value=array[ptr[max.index]];
			max_heap_insert(heap, &heapSize, max);
		}
		//printHeap(heap, heapSize);
	}
	
	
	free(array);
	return sortedArray;	
}	
/*
void memoryOpt_mainA(int arraySize, int * array, int blockSize)
{
	int number=(int)ceil((float)arraySize/(float)blockSize);
	printf("%d/n",number);
	int ptr[number];
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*number);
	int * header[number];
	
	for(int i=0; i<number-1; i++)
	{
		header[i]=copyArrayFT(array,  i*blockSize, (i+1)*blockSize-1);
		ptr[i]=blockSize-1;
		
	}
	
	
	header[number-1]=copyArrayFT(array, (number-1)*blockSize, arraySize-1);
	ptr[number-1]=arraySize-(number-1)*blockSize-1;
	
	for(int i=0;i<number;i++)
	{
		print(ptr[i]+1, header[i]);
	}

	for(int i=0;i< number; i++){
		printf("%d\n", ptr[i]);
		quicksort(header[i], 0, ptr[i]);
		heap[i].value=*(header[i]+ptr[i]);
		heap[i].index=i;
	}
		
	
	int heapSize=number;
	int counter=0;
	build_max_heap(heap, heapSize);
	//printHeap(heap, heapSize);
	while(counter!=arraySize)
	{
		heapNode max=heap_extract_max(heap, &heapSize);
		counter++;
		array[arraySize-counter]=max.value;
		ptr[max.index]--;
		if(ptr[max.index]>= 0)
		{
			max.value=*(header[max.index]+ptr[max.index]);;
			max_heap_insert(heap, &heapSize, max);
		}
		//printHeap(heap, heapSize);
	}
	
	for(int i=0;i<number;i++)
	{
		free(header[i]);
		header[i]=NULL;
	}		
}*/

int main(int argc, char *argv[])
{    
	int N = atoi(argv[1]);

	int numRuns=1;	
	double elapse1, elapse2;
	elapse1=0;
	elapse2=0;

  for (int i=0; i< numRuns; i++){
	double * A = MakeAIntArray(N);
	//print(N, A);
	double time=0;
	int blockSize=atoi(argv[2]);
	    
	double * serialArray=copyArray(N, A);
	time=read_timer();
	serial_main(N, serialArray);
	elapse1 += read_timer()-time;

	//print(N, serialArray);
	double * parallelArray=copyArray(N, A);
	time=read_timer();
	parallelArray=memoryOpt_main(N, parallelArray, blockSize);	
	elapse2 +=read_timer()-time;
	
	if(array_compare(N,serialArray,parallelArray)==1){
		fprintf(stderr,"Error\n");
		exit(-1);
    	}
  }
	printf("total serial   time: %f\n",elapse1/numRuns);
	printf("total parallel time: %f\n",elapse2/numRuns);

	//print(N, pthreadArray);
	return 0;
}



