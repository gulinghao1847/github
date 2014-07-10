//
//  queue.c
//  570hw4
//
//  Created by linghao on 12-11-5.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

queue_t* createQueue(int elemSize){
    queue_t* queue=(queue_t*)malloc(sizeof(queue_t));
    queue->object=(object_t*)malloc(elemSize*sizeof(object_t));
    queue->first=0;
    queue->rear=-1;
    queue->size=0;
    queue->capacity=elemSize;
    return queue;
}

int empty(queue_t* queue){
    return queue->size==0;
}

int enqueue(queue_t* queue, object_t* object){
    if (queue->size==queue->capacity)
        return 0;
    queue->size++;
    queue->rear=((queue->rear+1)==queue->capacity)?0:(queue->rear+1);
    queue->object[queue->rear]=*object;
    return 1;
}

object_t* dequeue(queue_t* queue){
    if (queue->size==0) {
        return NULL;
    }
    queue->size--;
    object_t* ret=&(queue->object[queue->first]);
    queue->first=((queue->first+1)==queue->capacity)?0:(queue->first+1);
    //object_t* ret=queue
    return ret;
}
