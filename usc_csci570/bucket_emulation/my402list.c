//
//  my402list.c
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include "my402list.h"

extern int  My402ListLength(My402List* list){
    return list->num_members;
}

extern int  My402ListEmpty(My402List* list){
    if(list->anchor.prev==list->anchor.next)
        return TRUE;
    else
        return FALSE;
}


int  My402ListAppend(My402List* list, void* obj){
    My402ListElem* tempE;
    tempE=malloc(sizeof(My402ListElem));
    tempE->obj=obj;
    //tempE->next=&(list->anchor);
    if(list->num_members!=0){
        tempE->prev=My402ListLast(list);
        My402ListLast(list)->next=tempE;
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

extern int  My402ListPrepend(My402List* list, void* obj){
    My402ListElem* tempE;
    tempE=(My402ListElem*)malloc(sizeof(My402ListElem));
    tempE->obj=obj;
    if(list->num_members!=0){
        tempE->prev=&(list->anchor);
        tempE->next=My402ListFirst(list);
        My402ListFirst(list)->prev=tempE;
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
extern void My402ListUnlink(My402List* list, My402ListElem* tempE){
    tempE->next->prev=tempE->prev;
    tempE->prev->next=tempE->next;
    list->num_members--;
}

extern void My402ListUnlinkAll(My402List* list){
    if (My402ListLength(list)==0) {
        return;
    }
    My402ListElem* elem=(My402ListElem*)malloc(sizeof(My402ListElem));
    for(elem=list->anchor.next;&(list->anchor)!=elem;elem=elem->next){                                                               // why elem->next can't be used
        My402ListUnlink(list, elem);
    }
    list->anchor.prev=&(list->anchor);
    list->anchor.next=&(list->anchor);
    
}
extern int  My402ListInsertAfter(My402List* list, void* obj, My402ListElem* tempE){
    My402ListElem* elem=(My402ListElem*)malloc(sizeof(My402ListElem));
    My402ListElem* temp1=(My402ListElem*)malloc(sizeof(My402ListElem));
    elem->obj=obj;
    elem->next=tempE->next;
    elem->prev=tempE;
    temp1=tempE->next;
    tempE->next=elem;
    temp1->prev=elem;
    list->num_members++;
    return TRUE;
}
extern My402ListElem* My402ListFindElem(My402List* list, My402ListElem* tempE){
    My402ListElem* elem;
    elem=&(list->anchor);
    while(elem!=tempE){
        elem=elem->next;
    }
    return elem;
}

extern int  My402ListInsertBefore(My402List* list, void* obj, My402ListElem* tempE){
    My402ListElem* elem=(My402ListElem*)malloc(sizeof(My402ListElem));
    My402ListElem* temp1=(My402ListElem*)malloc(sizeof(My402ListElem));
    elem->obj=obj;
    elem->next=tempE;
    elem->prev=tempE->prev;
    temp1=tempE->prev;
    tempE->prev=elem;
    temp1->next=elem;
    list->num_members++;
    
    return TRUE;
}
extern My402ListElem *My402ListFirst(My402List* list){
    if(list->num_members==0){
        return NULL;
    }
    else{
        
        return list->anchor.next;
    }
    
}

extern My402ListElem *My402ListLast(My402List* list){
    if(list->num_members==0)
        return NULL;
    else
        return list->anchor.prev;
}

extern My402ListElem *My402ListNext(My402List* list, My402ListElem* tempE){
    if(tempE->next==&(list->anchor))
        return NULL;
    else
        return tempE->next;
}

extern My402ListElem *My402ListPrev(My402List* list, My402ListElem* tempE){
    if(tempE->prev==&(list->anchor))
        return NULL;
    return tempE->prev;
}

extern My402ListElem *My402ListFind(My402List* list, void* obj){
    My402ListElem* tempE=malloc(sizeof(My402List));
    for(tempE=My402ListFirst(list);tempE!=&(list->anchor);tempE=tempE->next){
        if(tempE->obj==obj)
            return tempE;
    }
    return NULL;
    
}

extern int My402ListInit(My402List* list){
    list->anchor.prev=&(list->anchor);
    list->anchor.next=&(list->anchor);
    list->num_members=0;
    return TRUE;
}

