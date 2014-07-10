//
//  my570list.h
//  hw5
//
//  Created by linghao on 12-11-26.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _MY570LIST_H_
#define _MY570LIST_H_

#include "cs570.h"

typedef struct tagMy570ListElem {
    void *obj;
    struct tagMy570ListElem *next;
    struct tagMy570ListElem *prev;
} My570ListElem;

typedef struct tagMy570List {
    int num_members;
    My570ListElem anchor;
    
    int  (*Length)(struct tagMy570List *);
    int  (*Empty)(struct tagMy570List *);
    
    int  (*Append)(struct tagMy570List *, void*);
    int  (*Prepend)(struct tagMy570List *, void*);
    void (*Unlink)(struct tagMy570List *, My570ListElem*);
    void (*UnlinkAll)(struct tagMy570List *);
    int  (*InsertBefore)(struct tagMy570List *, void*, My570ListElem*);
    int  (*InsertAfter)(struct tagMy570List *, void*, My570ListElem*);
    
    My570ListElem *(*First)(struct tagMy570List *);
    My570ListElem *(*Last)(struct tagMy570List *);
    My570ListElem *(*Next)(struct tagMy570List *, My570ListElem *cur);
    My570ListElem *(*Prev)(struct tagMy570List *, My570ListElem *cur);
    
    My570ListElem *(*Find)(struct tagMy570List *, void *obj);
} My570List;

extern int  My570ListLength(My570List*);
extern int  My570ListEmpty(My570List*);

extern int  My570ListAppend(My570List*, void*);
extern int  My570ListPrepend(My570List*, void*);
extern void My570ListUnlink(My570List*, My570ListElem*);
extern void My570ListUnlinkAll(My570List*);
extern int  My570ListInsertAfter(My570List*, void*, My570ListElem*);
extern int  My570ListInsertBefore(My570List*, void*, My570ListElem*);

extern My570ListElem *My570ListFirst(My570List*);
extern My570ListElem *My570ListLast(My570List*);
extern My570ListElem *My570ListNext(My570List*, My570ListElem*);
extern My570ListElem *My570ListPrev(My570List*, My570ListElem*);

extern My570ListElem *My570ListFind(My570List*, void*);

extern int My570ListInit(My570List*);

#endif /*_MY570LIST_H_*/
