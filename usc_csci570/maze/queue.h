//
//  queue.h
//  570hw4
//
//  Created by linghao on 12-11-5.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70hw4_queue_h
#define _70hw4_queue_h
#include "maze.h"
typedef struct queue{
    int first;
    int rear;
    int size;
    int capacity;
    object_t* object;
}queue_t;


object_t* dequeue(queue_t*);
int enqueue(queue_t*,object_t*);
int empty(queue_t*);
queue_t* createQueue(int number);
#endif
