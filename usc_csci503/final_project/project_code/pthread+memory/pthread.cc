#include <stdlib.h>
#include <iostream>
#include <stdio.h>
#include <pthread.h>
#include "myHeap.h"
#include "header.h"

using namespace std;

extern void quicksort(double * A, int p, int r);
extern void print(int n, double * A);
extern double read_timer();


/*
extern heapNode heap_extract_max(heapNode * array, int * arraySize);
extern void max_heap_insert(heapNode * array, int * arraySize, heapNode node);
extern void build_max_heap(heapNode * array, int arraySize);
extern void printHeap(heapNode * array, int arraySize);
*/
void * quicksortSubRoutine(void * ptr){
	subproblem * sub=(subproblem *)ptr;
	quicksort(sub->array, sub->row_start, sub->row_end);
    return NULL;
}

double * pthread_main(int arraySize, double * array, int threadNumber)
{
	pthread_t *thread= (pthread_t *) malloc(sizeof(pthread_t)* threadNumber);
	subproblem * sub= (subproblem *)malloc(sizeof(subproblem)*threadNumber);
	
	int averageRow=arraySize/threadNumber;
	int remainder=arraySize%threadNumber;
	int offset=0;
	int size=0;	
	double time=0;

	int i;
	//time=read_timer();
	for(i=0;i<threadNumber;i++)
	{
		size=(i<remainder)?(averageRow+1):averageRow;
		sub[i].array=array;
		sub[i].row_start=offset;
		sub[i].row_end=offset+size-1;
		offset+=size;
		pthread_create( ( pthread_t * ) &(thread[i]), NULL, quicksortSubRoutine, (void *) &sub[i] );
	}
	//time=read_timer()-time;
	//printf("total overhead time: %f\n", time);
	for(i =0;i<threadNumber;i++)
	{
		pthread_join(thread[i],NULL);
	}
//barrier
	//print(arraySize, array);
	//printf("done in pthread\n");

	int ptr[threadNumber];
	for(i=0;i<threadNumber;i++)
	{
		ptr[i]=sub[i].row_end;
	}	

    
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*threadNumber);
	for(i=0;i<threadNumber;i++)
	{
		heap[i].value=array[ptr[i]];
		heap[i].index=i;
	}	
	
	int heapSize=threadNumber;
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
		if(ptr[max.index]>=sub[max.index].row_start)
		{
			max.value=array[ptr[max.index]];
			max_heap_insert(heap, &heapSize, max);
		}
		//printHeap(heap, heapSize);
	}
	
	free(array);
	return sortedArray;

}
