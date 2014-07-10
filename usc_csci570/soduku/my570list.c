//
//  my570list.c
//  hw5
//
//  Created by linghao on 12-11-26.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include "my570list.h"
#include <stdlib.h>
int  My570ListLength(My570List* list){
    return list->num_members;
}

int  My570ListEmpty(My570List* list){
    if(list->anchor.prev==list->anchor.next)
        return TRUE;
    else
        return FALSE;
}


int  My570ListAppend(My570List* list, void* obj){
    My570ListElem* tempE;
    tempE=malloc(sizeof(My570ListElem));
    tempE->obj=obj;
    //tempE->next=&(list->anchor);
    if(list->num_members!=0){
        tempE->prev=My570ListLast(list);
        My570ListLast(list)->next=tempE;
        tempE->next=&(list->anchor);
        list->anchor.prev=tempE;
        list->num_members++;
    }
    else{
        list->anchor.prev=tempE;
        list->anchor.next=tempE;
        tempE->next=&(list->anchor);
        tempE->prev=&(list->anchor);
        list->num_members++;
    }
    //printf("%d\n",list->num_members);
    return TRUE;
}            //false 如何弄 就是catch

int  My570ListPrepend(My570List* list, void* obj){
    My570ListElem* tempE;
    tempE=(My570ListElem*)malloc(sizeof(My570ListElem));
    tempE->obj=obj;
    if(list->num_members!=0){
        tempE->prev=&(list->anchor);
        tempE->next=My570ListFirst(list);
        My570ListFirst(list)->prev=tempE;
        list->anchor.next=tempE;
        list->num_members++;
    }
    else{
        list->anchor.prev=tempE;
        list->anchor.next=tempE;
        tempE->next=&(list->anchor);
        tempE->prev=&(list->anchor);
        list->num_members++;
    }
    return TRUE;
}
void My570ListUnlink(My570List* list, My570ListElem* tempE){
    tempE->next->prev=tempE->prev;
    tempE->prev->next=tempE->next;
    list->num_members--;
}

void My570ListUnlinkAll(My570List* list){
    My570ListElem* elem=(My570ListElem*)malloc(sizeof(My570ListElem));
    for(elem=list->anchor.next;&(list->anchor)!=elem;elem=elem->next){                                                               // why elem->next can't be used
        My570ListUnlink(list, elem);
    }
    list->anchor.prev=&(list->anchor);
    list->anchor.next=&(list->anchor);
    
}

int  My570ListInsertAfter(My570List* list, void* obj, My570ListElem* tempE){
    My570ListElem* elem=(My570ListElem*)malloc(sizeof(My570ListElem));
    My570ListElem* temp1=(My570ListElem*)malloc(sizeof(My570ListElem));
    elem->obj=obj;
    elem->next=tempE->next;
    elem->prev=tempE;
    temp1=tempE->next;
    tempE->next=elem;
    temp1->prev=elem;
    list->num_members++;
    return TRUE;
}

My570ListElem* My570ListFindElem(My570List* list, My570ListElem* tempE){
    My570ListElem* elem;
    elem=&(list->anchor);
    while(elem!=tempE){
        elem=elem->next;
    }
    return elem;
}

int  My570ListInsertBefore(My570List* list, void* obj, My570ListElem* tempE){
    My570ListElem* elem=(My570ListElem*)malloc(sizeof(My570ListElem));
    My570ListElem* temp1=(My570ListElem*)malloc(sizeof(My570ListElem));
    elem->obj=obj;
    elem->next=tempE;
    elem->prev=tempE->prev;
    temp1=tempE->prev;
    tempE->prev=elem;
    temp1->next=elem;
    list->num_members++;
    
    return TRUE;
}

My570ListElem *My570ListFirst(My570List* list){
    if(list->num_members==0){
        return NULL;
    }
    else{
        
        return list->anchor.next;
    }
    
}

My570ListElem *My570ListLast(My570List* list){
    if(list->num_members==0)
        return NULL;
    else
        return list->anchor.prev;
}

My570ListElem *My570ListNext(My570List* list, My570ListElem* tempE){
    if(tempE->next==&(list->anchor))
        return NULL;
    else
        return tempE->next;
}

My570ListElem *My570ListPrev(My570List* list, My570ListElem* tempE){
    if(tempE->prev==&(list->anchor))
        return NULL;
    return tempE->prev;
}

My570ListElem *My570ListFind(My570List* list, void* obj){
    My570ListElem* tempE=malloc(sizeof(My570List));
    for(tempE=My570ListFirst(list);tempE!=&(list->anchor);tempE=tempE->next){
        if(tempE->obj==obj)
            return tempE;
    }
    return NULL;
    
}

int My570ListInit(My570List* list){
    list->anchor.prev=&(list->anchor);
    list->anchor.next=&(list->anchor);
    list->num_members=0;
    return TRUE;
}

