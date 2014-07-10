//
//  unionFind.c
//  570hw4
//
//  Created by linghao on 12-11-10.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "unionFind.h"

void initUnionFind(un_t* un, int size){
    int i=0;
    for (i=0;i<size;i++) {
        un[i].parent=NULL;
    }
}

un_t* findRoot(un_t* unionFind){
    un_t* ret=unionFind;
    while (ret->parent!=NULL) {
        ret=ret->parent;
        //printf("touch\n");
    }
    return ret;
}

void unionT(un_t* un1,un_t* un2){
    un2->parent=un1;
}



