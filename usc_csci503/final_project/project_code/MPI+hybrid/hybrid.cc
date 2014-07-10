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
#define THREADNUM 1


extern void quicksort(double * A, int p, int r);
extern void print(int n, double * A);
extern int * MakeAIntArray(int arraySize);
extern double * pthread_main(int arraySize, double * array, int threadNumber);
extern double read_timer();
/*
void test(int node1, int node2,int size, int* array, int* org){
	printf("data from node:%d to node:%d\n",node1,node2);
	printf("size: %d\n",size);
	for(int i=0;i<10; i++){
		printf("%d,",array[i]);
	}
	printf("\n");
	for(int i=0;i<10; i++){
		printf("%d,",org[i]);
	}
	printf("\n");
}

double* parallel_hybrid_main(int N, double * array){
	//test(100,array);
	int i=0;
    int rank, size, count, namelen,numPro;
    int arraySize=N;
    char processor_name[MAX_NAME_LEN];
    MPI_Status status;
    int offset=0;
    subproblem * sub;
    subproblem result;
    double* subArray;
    
    MPI_Comm_rank(MPI_COMM_WORLD,&rank);
    MPI_Comm_size(MPI_COMM_WORLD,&numPro);
    MPI_Get_processor_name(processor_name,&namelen);

    int averageRow=arraySize/numPro;
    int remainder=arraySize%numPro;
	sub=(subproblem*)malloc(sizeof(subproblem)*numPro);
	for(i=0;i<numPro;i++){
		size=(i<remainder)?(averageRow+1):averageRow;
		sub[i].array=array;
		sub[i].row_start=offset;
		sub[i].row_end=offset+size-1;
		offset+=size;
	}

    if (rank==0) {
		//test(100,array);
        //sub= (subproblem *)malloc(sizeof(subproblem)*numPro);
        int i;
		int data_size=0;
		for(i=4;i<8;i++){
			data_size+=sub[i].row_end-sub[i].row_start+1;
			//printf("%d\n",data_size);
		}
		//printf("%d\n",data_size);
		//sending data to node04
		MPI_Send(&data_size, 1, MPI_INT, 4, 0241, MPI_COMM_WORLD);
		MPI_Send(&array[sub[4].row_start],data_size, MPI_DOUBLE, 4, 0242, MPI_COMM_WORLD);
		//test(4,7,data_size, &array[sub[4].row_start],&array[500]);
		
		//sending data to node02
		data_size=0;
		for(i=2;i<4;i++){
			data_size+=sub[i].row_end-sub[i].row_start+1;
		}
		MPI_Send(&data_size, 1, MPI_INT, 2, 0221, MPI_COMM_WORLD);
		MPI_Send(&array[sub[2].row_start], data_size, MPI_DOUBLE, 2, 0222, MPI_COMM_WORLD);
		
		//sending data to node01
		data_size=0;
		i=1;
		data_size+=sub[i].row_end-sub[i].row_start+1;	
		MPI_Send(&data_size, 1, MPI_INT, 1, 0211, MPI_COMM_WORLD);
		MPI_Send(&array[sub[1].row_start],data_size, MPI_DOUBLE, 1, 0212, MPI_COMM_WORLD);

		//init node00's part
		result.array=array;
		result.row_start=sub[0].row_start;
		result.row_end=sub[0].row_end;
		
    }else if(rank==4){
		//receive data from node00
		//printf("ok in 4\n");
		MPI_Recv(&size, 1, MPI_INT, 0, 0241, MPI_COMM_WORLD, &status);
		subArray=(double*)malloc(size*sizeof(double));
		MPI_Recv(&subArray[0], size, MPI_DOUBLE, 0, 0242, MPI_COMM_WORLD, &status);
		//printf("ok in 4\n");
		
		//send data to node06 and node05
		int data_size=0;
		int occpy=0;
		int i=0;
		//send data to node06
		for(i=6;i<8;i++){
			data_size+=sub[i].row_end-sub[i].row_start+1;
		}
		MPI_Send(&data_size, 1, MPI_INT, 6, 4261, MPI_COMM_WORLD);
		MPI_Send(&subArray[size-data_size], data_size, MPI_DOUBLE, 6, 4262, MPI_COMM_WORLD);
		//test(6,7,data_size, &subArray[size-data_size],&array[750]);
		//Send data to node05
		data_size=0;
		for(i=5;i<6;i++){
			data_size+=sub[i].row_end-sub[i].row_start+1;
		}
		for(i=4;i<5;i++){
			occpy=sub[i].row_end-sub[i].row_start+1;
		}
		MPI_Send(&data_size, 1, MPI_INT, 5, 4251, MPI_COMM_WORLD);
		MPI_Send(&subArray[occpy], data_size, MPI_DOUBLE, 5, 4252, MPI_COMM_WORLD);
		//test(5,5,data_size, &subArray[occpy],&array[625]);
		//Init node04 part
		result.array=subArray;
		result.row_start=0;
		result.row_end=sub[4].row_end-sub[4].row_start;
	}
	else if(rank==2||rank==6){
		int parent=((rank==2)?0:4);
		int child=((rank==2)?3:7);
		//receive data from parent
		if(rank==2){
			MPI_Recv(&size, 1, MPI_INT, 0, 0221, MPI_COMM_WORLD, &status);
			subArray=(double*)malloc(size*sizeof(double));
			MPI_Recv(&subArray[0], size, MPI_DOUBLE, 0, 0222, MPI_COMM_WORLD, &status);
		}else{
			MPI_Recv(&size, 1, MPI_INT, 4, 4261, MPI_COMM_WORLD, &status);
			subArray=(double*)malloc(size*sizeof(double));
			MPI_Recv(&subArray[0], size, MPI_DOUBLE, 4, 4262, MPI_COMM_WORLD, &status);
		}

		//send data to child
		int data_size=0;
		int occpy=0;
		int i;

		if(rank==2){  //send data to node03
			for(i=3;i<4;i++){
				data_size+=sub[i].row_end-sub[i].row_start+1;
				i--;
				occpy+=sub[i].row_end-sub[i].row_start+1;
				i++;
			}
			MPI_Send(&data_size, 1, MPI_INT, 3, 2231, MPI_COMM_WORLD);
			MPI_Send(&subArray[occpy], data_size, MPI_DOUBLE, 3, 2232, MPI_COMM_WORLD);
		}else if(rank==6){
			for(i=7;i<8;i++){
				data_size+=sub[i].row_end-sub[i].row_start+1;
				i--;
				occpy+=sub[i].row_end-sub[i].row_start+1;
				i++;
			}
			MPI_Send(&data_size, 1, MPI_INT, 7, 6271, MPI_COMM_WORLD);
			MPI_Send(&subArray[occpy], data_size, MPI_DOUBLE, 7, 6272, MPI_COMM_WORLD);		
		}
		//init its own data
		result.array=subArray;
		result.row_start=0;
		result.row_end=sub[rank].row_end-sub[rank].row_start;
	
	}
	else{

		int recOne,recTwo,parent;
		if(rank==1||rank==3){
			recOne=((rank==1)?0211:2231);
			recTwo=((rank==1)?0212:2232);
			parent=((rank==1)?0:2);
		}else if(rank==5||rank==7){
			recOne=((rank==5)?4251:6271);
			recTwo=((rank==5)?4252:6272);
			parent=((rank==5)?4:6);
		}

		//receive data
        MPI_Recv(&size,1,MPI_INT,parent,recOne,MPI_COMM_WORLD,&status);
        subArray=(double*)malloc(size*sizeof(double));
        MPI_Recv(&subArray[0],size,MPI_DOUBLE,parent,recTwo,MPI_COMM_WORLD,&status);
		//init data
        result.array=subArray;
        result.row_start=0;
        result.row_end=size-1;
    }

   
   //quicksort(result.array, result.row_start, result.row_end);
   pthread_main(result.row_end-result.row_start+1, &result.array[0], THREADNUM);

    if(rank!=0){
	int io=0;
	size=result.row_end-result.row_start+1;
        MPI_Send(&result.array[0],size,MPI_DOUBLE,0,200,MPI_COMM_WORLD);
*/
	/*
	printf("This is rank:%d report\n",rank);
	for(io=0;io<size; io++){
		printf("%f  ",result.array[io]);
	}
	printf("\nSize: %d\n",io);
	*/
/*
    }
    if (rank==0) {
	printf("got here\n");
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
		printf("got here 3 rank: %d, size: %d\n",rank,size);
		for(int j=0; j<size; j++) printf("%f ",array[j+start]);
		printf("\n");
        }
	
	print(N, array);
	int ptr[numPro];
	
	for(i=0;i<numPro;i++)
        {
            size=(i<remainder)?(averageRow+1):averageRow;
            sub[i].array=array;
            sub[i].row_start=offset;
            sub[i].row_end=offset+size-1;
            offset+=size;
        }

	for(i=0;i<numPro;i++)
	{
		ptr[i]=sub[i].row_end;
	}	

    	printf("got here 3\n");
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*numPro);
	for(i=0;i<numPro;i++)
	{
		heap[i].value=array[ptr[i]];
		heap[i].index=i;
	}	
	
	int heapSize=numPro;
	int counter=0;
	printf("got here 2\n");
	double * sortedArray=(double *)malloc(sizeof(double)*arraySize);
	build_max_heap(heap, heapSize);
	//printHeap(heap, heapSize);
	printf("got here 1\n");
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
*/

double * parallel_hybrid_main(int N, double * array, int threadNum/*,int numPro*/){
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
    double time=0, overhead=0;
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
	overhead=read_timer()-time;
    }else{
        MPI_Recv(&size,1,MPI_INT,0,100,MPI_COMM_WORLD,&status);
        subArray=(double*)malloc(size*sizeof(double));
        MPI_Recv(&subArray[0],size,MPI_DOUBLE,0,101,MPI_COMM_WORLD,&status);
        result.array=subArray;
        result.row_start=0;
        result.row_end=size-1;
    }
    
    	//quicksort(result.array, result.row_start, result.row_end);
	double* sorted;
	sorted=pthread_main(result.row_end-result.row_start+1, result.array, threadNum);
	result.array=sorted;
	//print(result.row_end-result.row_start+1, result.array);
	//result.array=sorted;

    if(rank!=0){
	size=result.row_end-result.row_start+1;
        MPI_Send(&result.array[0],size,MPI_DOUBLE,0,200,MPI_COMM_WORLD);
    }
    if (rank==0) {
        int i=0;
        int start=sub[i].row_start;
        int size=sub[i].row_end-sub[i].row_start+1;
	time=read_timer();
        for (i=0; i<size; i++) {
            array[i]=result.array[i];
        }
        for (i=1; i<numPro; i++) {
            start=sub[i].row_start;
            size=sub[i].row_end-sub[i].row_start+1;
            MPI_Recv(&array[start],size,MPI_DOUBLE,i,200,MPI_COMM_WORLD,&status);
        }
	//print(N, array);
	//printf("get here1\n");
	int ptr[numPro];
	for(i=0;i<numPro;i++)
	{
		ptr[i]=sub[i].row_end;
	}	
	overhead+=read_timer()-time;
    //printf("get here2\n");
	heapNode * heap= (heapNode * )malloc(sizeof(heapNode)*numPro);
	for(i=0;i<numPro;i++)
	{
		heap[i].value=array[ptr[i]];
		heap[i].index=i;
	}	
	//printf("get here4\n");
	int heapSize=numPro;
	int counter=0;
	double * sortedArray=(double *)malloc(sizeof(double)*arraySize);
	build_max_heap(heap, heapSize);
	//printHeap(heap, heapSize);
//printf("get here3\n");
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
	
	printf("overhead: %f\n",overhead);
	free(array);
	//print(N, sortedArray);
	return sortedArray;
    }
	//print(N,array);
}



