//
//  heap.h
//  503FINAL
//
//  Created by linghao on 13-3-30.
//  Copyright (c) 2013年 linghao. All rights reserved.
//

#ifndef _03FINAL_heap_h
#define _03FINAL_heap_h

struct heapNode{
	double value;
	int index;
};

extern void exchange(double * a, double *b);
extern void exchange(int * a, int *b);
void heap_increase_key(heapNode * array, int arraySize, int index, heapNode node);
void max_heapify(heapNode * array, int index, int arraySize);
heapNode heap_extract_max(heapNode * array, int * arraySize);
void max_heap_insert(heapNode * array, int * arraySize, heapNode node);
void printHeap(heapNode * array, int arraySize);
void build_max_heap(heapNode * array, int arraySize);

#endif
