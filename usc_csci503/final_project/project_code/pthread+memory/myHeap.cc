#include <stdlib.h>
#include <stdio.h>
#include "myHeap.h"
#define INT_MIN 0x80000000





void exchangeNode(heapNode * a, heapNode * b){
	exchange(&(a->value), &(b->value));
	exchange(&(a->index), &(b->index));
}

int parent(int index)
{
	return ((index+1)/2-1);
}

int leftIndex(int index)
{
	return (2*index+1);
}

int rightIndex(int index)
{
	return (2*index+2);
}

void heap_increase_key(heapNode * array, int arraySize, int index, heapNode node)
{
	array[index].value=node.value;
	array[index].index=node.index;
	
	while(index>0 && array[parent(index)].value<array[index].value)
	{
		exchangeNode(array+index, array+parent(index));
		index=parent(index);
	}
}

void max_heapify(heapNode * array, int index, int arraySize)
{
	int left=leftIndex(index);
	int right=rightIndex(index);
	
	int largest;
	if(left<arraySize && array[left].value>array[index].value)
	{
		largest=left;
	}
	else
	{
		largest=index;
	}

	if(right<arraySize && array[right].value>array[largest].value)
		largest=right;
	
	if(largest!=index)
	{
		exchangeNode(array+largest, array+index);
		max_heapify(array, largest, arraySize);
	}
}

heapNode heap_extract_max(heapNode * array, int * arraySize)
{
	heapNode max;
	max.value=array[0].value;
	max.index=array[0].index;
	array[0].value=array[*arraySize-1].value;
	array[0].index=array[*arraySize-1].index;
	(*arraySize)--;
	max_heapify(array,0,*arraySize);
	
	return max;
}



void max_heap_insert(heapNode * array, int * arraySize, heapNode node)
{
	(*arraySize)++;
	array[(*arraySize)-1].value=double(INT_MIN);
	heap_increase_key(array, *arraySize, *arraySize-1, node);

}

void printHeap(heapNode * array, int arraySize)
{
	for(int i=0;i<arraySize;i++)
	  printf("%f ", array[i].value);
	printf("\n");

}

void build_max_heap(heapNode * array, int arraySize)
{
	for(int i=arraySize/2-1;i>=0;i--)
	{
		max_heapify(array, i, arraySize);
	}
}
