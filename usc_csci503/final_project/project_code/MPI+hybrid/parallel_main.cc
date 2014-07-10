//
//  parallel_main.cpp
//  503FINAL
//
//  Created by linghao on 13-3-30.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#include "parallel_main.h"
#include <mpi.h>
#include "header.h"
#include "myHeap.h"
#include <stdlib.h>
#define MAX_NAME_LEN 100

extern void quicksort(double * A, int p, int r);
extern void print(int n, double * A);
extern double * MakeAIntArray(int arraySize);
extern double read_timer();
//double overhead;

double * parallel_main(int N, double * array/*, double* overhead,int numPro*/){
    //array=MakeAIntArray(N);
    int rank, size, count, namelen,numPro;
    int arraySize=N;
    char processor_name[MAX_NAME_LEN];
    MPI_Status status;
    int offset=0;
    //int size=0;
    subproblem * sub;
    subproblem result;
    double* subArray;
    double time=0.0/*, overhead= 0.0*/;
    double overhead = 0.0, runningTime= 0.0, overhead2= 0.0;
    //int* array=(int*)malloc(N*sizeof(int));
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numPro);
    MPI_Get_processor_name(processor_name,&namelen);

    int averageRow=arraySize/numPro;
    int remainder=arraySize%numPro;

    if (rank==0) {
        time=read_timer();
        sub= (subproblem *)malloc(sizeof(subproblem)*numPro);
        int i;
        for(i=0;i<numPro;i++)
        {
            size=(i<remainder)?(averageRow+1):averageRow;
            sub[i].array=array;
            sub[i].row_start=offset;
            sub[i].row_end=offset+size-1;
            offset+=size;
            int temp=size;
	    if(i!=0){
            	MPI_Send(&temp,1,MPI_INT,i,100,MPI_COMM_WORLD);
            	MPI_Send(&array[sub[i].row_start],size,MPI_DOUBLE,i,101,MPI_COMM_WORLD);
	    }
	result.array=array;
	result.row_start=sub[0].row_start;
	result.row_end=sub[0].row_end;
        }
	(overhead)+=read_timer()-time;
    }else{
        MPI_Recv(&size,1,MPI_INT,0,100,MPI_COMM_WORLD,&status);
        subArray=(double*)malloc(size*sizeof(double));
        MPI_Recv(&subArray[0],size,MPI_DOUBLE,0,101,MPI_COMM_WORLD,&status);
        result.array=subArray;
        result.row_start=0;
        result.row_end=size-1;
    }

    time=read_timer();
    quicksort(result.array, result.row_start, result.row_end);
    runningTime=read_timer()-time;

    if(rank!=0){
	size=result.row_end-result.row_start+1;
        MPI_Send(&result.array[0],size,MPI_DOUBLE,0,200,MPI_COMM_WORLD);
    }
    if (rank==0) {
	time=read_timer();
        int i=0;
        int start=sub[i].row_start;
        int size=sub[i].row_end-sub[i].row_start+1;
        for (i=0; i<size; i++) {
            array[i]=result.array[i];
        }
        for (i=1; i<numPro; i++) {
            start=sub[i].row_start;
            size=sub[i].row_end-sub[i].row_start+1;
            MPI_Recv(&array[start],size,MPI_DOUBLE,i,200,MPI_COMM_WORLD,&status);
        }
	(overhead2)+=read_timer()-time;
	int ptr[numPro];
	for(i=0;i<numPro;i++)
	{
		ptr[i]=sub[i].row_end;
	}	

    
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*numPro);
	for(i=0;i<numPro;i++)
	{
		heap[i].value=array[ptr[i]];
		heap[i].index=i;
	}	
	
	int heapSize=numPro;
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
	//print(N,array);
}



