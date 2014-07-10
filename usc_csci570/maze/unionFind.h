//
//  unionFind.h
//  570hw4
//
//  Created by linghao on 12-11-10.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70hw4_unionFind_h
#define _70hw4_unionFind_h
typedef struct unionFind un_t;
struct unionFind{
    un_t* parent;
};

un_t* findRoot(un_t*);
void unionT(un_t*,un_t*);
void initUnionFind(un_t* un, int size);


#endif
