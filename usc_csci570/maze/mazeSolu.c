//
//  maze.c
//  570hw4
//
//  Created by linghao on 12-11-5.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maze.h"
#include "queue.h"
#define LARG_W 100;

int getStartRoom(maze_t* myMaze){
    int enter=myMaze->enter;
    int enterPos=myMaze->enterPos;
    int height=myMaze->lineInfo->height;
    int width=myMaze->lineInfo->width;
    //printf("enter:%d\n",enter);
    //printf("leave:%d\n",myMaze->leavePos);
    if (enterPos==0) {
        return (enter+1)/2-1;
    }
    else if(enterPos==2*height){
        //printf("enter:%d",enter);
        return (height-1)*width+(enter+1)/2-1;
    }
    else if(enter==0){
        return ((myMaze->enterPos-1)/2)*width;
    }
    else
        return ((myMaze->enterPos-1)/2)*width+width-1;
}

int getEndRoom(maze_t* myMaze){
    int leave=myMaze->leave;
    int leavePos=myMaze->leavePos;
    int height=myMaze->lineInfo->height;
    int width=myMaze->lineInfo->width;
    if (leavePos==0) {
        return (leave+1)/2-1;
    }
    else if(leavePos==2*height){
        return (height-1)*width+(leave+1)/2-1;
    }
    else if(leave==0){
        return ((myMaze->leavePos-1)/2)*width;
    }
    else
        return ((myMaze->leavePos-1)/2)*width+width-1;
}

void initAdj(int number, adList_t* adList,maze_t* myMaze){
    adList->count=number;
    int i=0;
    for (i=0;i<number;i++) {
        adList->object[i].room=&(myMaze->room[i]);
        //adList->object[i].depth=-1;
        adList->object[i].firstEdge=NULL;
        //adList->object[i-1].amount=-1;
        //adList->object[i-1].lastLine=NULL;
    }
}

void genAdj(maze_t* myMaze, adList_t* adList){
    adList->object=(object_t*)malloc(myMaze->roomNumber*sizeof(object_t));
    initAdj(myMaze->roomNumber,adList,myMaze);
    lines_t* iterLine=myMaze->lineInfo;
    object_t* object;
    int i;
    struct line temp;
    for (i=0;iterLine->deletedLines[i].number!=-1;i++) {
        temp=iterLine->deletedLines[i];
        edge_t* tempEdge=(edge_t*)malloc(sizeof(edge_t));
        //initialize edge
        tempEdge->number=temp;
        tempEdge->endRoom=&(adList->object[getSecondRoom(temp.number,myMaze->lineInfo)]);
        tempEdge->nextEdge=NULL;
        tempEdge->weight=temp.weight;
        //tempEdge->depth=-1;
        //initialize end
        
        object=&(adList->object[getFirstRoom(temp.number,myMaze->lineInfo)]);
        if (object->firstEdge==NULL) {
            object->firstEdge=tempEdge;
        }
        else{
            edge_t* edge;
            for (edge=object->firstEdge;edge->nextEdge!=NULL;edge=edge->nextEdge);
            edge->nextEdge=tempEdge;
        }
        
        
        edge_t* tempEdge2=(edge_t*)malloc(sizeof(edge_t));
        //initialize edge
        tempEdge2->number=temp;
        tempEdge2->endRoom=&(adList->object[getFirstRoom(temp.number,myMaze->lineInfo)]);
        tempEdge2->nextEdge=NULL;
        tempEdge2->weight=temp.weight;
        //tempEdge->depth=-1;
        //initialize end
        
        object=&(adList->object[getSecondRoom(temp.number,myMaze->lineInfo)]);
        if (object->firstEdge==NULL) {
            object->firstEdge=tempEdge2;
        }
        else{
            edge_t* edge;
            for (edge=object->firstEdge;edge->nextEdge!=NULL;edge=edge->nextEdge);
            edge->nextEdge=tempEdge2;
        }
    }
    /*
    printf("delete:%d\n",i);
    int countNumber=0;
    for (i=0;i<adList->count;i++) {
        printf("room:%d, ",adList->object[i].room->room);
        edge_t* temp_edge=adList->object[i].firstEdge;
        for (;temp_edge!=NULL;temp_edge=temp_edge->nextEdge) {
            if (temp_edge->endRoom!=&adList->object[temp_edge->endRoom->room->room]) {
                printf("impossible\n");
            }
            printf("edge:%d edge_end_room: %d,weight: %d",temp_edge->number.number,temp_edge->endRoom->room->room,temp_edge->weight);
            countNumber++;
        }
        printf("\n");
    }
     
    printf("%d\n",countNumber);
     */
}


void doBFS(maze_t* myMaze, adList_t* adList){
    queue_t* queue= createQueue(myMaze->roomNumber);;
    int start=getStartRoom(myMaze);
    //printf("%d\n",start);
    object_t* object;
    edge_t* edge;
    room_t* room;
    int largest=0;
    adList->object[start].room->depth=0;
    enqueue(queue,&(adList->object[start]));
    while (!empty(queue)) {
        //printf("here\n");
        object=dequeue(queue);
        //printf("dequeue room: %d ,depth:%d,%d",object->room->room,object->depth,adList->object[object->room->room].depth);
        edge=object->firstEdge;
        if (edge!=NULL)
            //printf("firstEdge: %d ",edge->number.number);
        for (;edge!=NULL;edge=edge->nextEdge) {
            if (edge->endRoom->room->depth==-1){
                room=edge->endRoom->room;
                enqueue(queue,&adList->object[edge->endRoom->room->room]);
                room->parent=object->room->room;
                //adList->object[edge->endRoom->room->room].room->parent=object->room->room;
                room->edge=edge->number.number;
                //adList->object[edge->endRoom->room->room].room->edge=edge->number.number;
                room->depth=object->room->depth+1;
                //adList->object[edge->endRoom->room->room].depth=adList->object[object->room->room].depth+1;
                //printf("enqueue room: %d ,depth:%d,object room:%d",edge->endRoom->room->room,adList->object[16].depth,object->room->room);
                largest=room->depth;
            }
        }
    }
    myMaze->maxDepth=largest;
    free(queue);
}


void initQ(orgRoom_t* roomList,adList_t* adList){
    int i=0;
    for (i=0;i<adList->count;i++) {
        roomList[i].object=&adList->object[i];
        roomList[i].amount=-1;
        roomList[i].lastLine=NULL;
        roomList[i].used=0;
    }
}

orgRoom_t* findMin(int num,orgRoom_t* roomList){
    int i=0;
    orgRoom_t* min=NULL;
    for (i=0;i<num;i++) {
        if (roomList[i].used==0&&roomList[i].amount!=-1) {
            min=&roomList[i];
            break;
        }
    }
    if (min==NULL) {
        return NULL;
    }
    for (;i<num;i++) {
        if (roomList[i].used==0&&(roomList[i].amount!=-1)&&(roomList[i].amount<min->amount)) {
            min=&roomList[i];
        }
    }
    if (min!=NULL) {
        min->used=1;
    }
    
    return min;
}

void update(orgRoom_t* roomList, object_t* object){
    edge_t* edge=object->firstEdge;
    room_t* room;
    int room_2=object->room->room;
    for (;edge!=NULL;edge=edge->nextEdge) {
        room=edge->endRoom->room;
        if (roomList[room->room].amount>(roomList[room_2].amount+edge->weight)||roomList[room->room].amount==-1) {
            roomList[room->room].amount=roomList[room_2].amount+edge->weight;
            roomList[room->room].lastLine=edge;
            roomList[room->room].object->room->parent=object->room->room;
            roomList[room->room].object->room->edge=edge->number.number;
        }
    }
}

void doDijk(adList_t* adList,maze_t* myMaze){
    int totalRoom=adList->count;
    int i=0;
    int count=0;
    orgRoom_t* min;
    orgRoom_t* roomList=(orgRoom_t*)malloc(totalRoom*sizeof(orgRoom_t));
    path_t* path=(path_t*)malloc(totalRoom*sizeof(path_t));
    initQ(roomList,adList);
    int start=getStartRoom(myMaze);
    //printf("start room :%d\n",start);
    roomList[start].amount=0;  //init
    for (i=0;i<totalRoom;i++) {
        if((min=findMin(totalRoom,roomList))==NULL)
            break;
        //path[i].object=min->object;
        //path[i].edge=min->lastLine;
        myMaze->room[min->object->room->room].amount=min->amount;
        update(roomList,min->object);
        count++;
    }
    /*
    printf("count:%d",count);
    for (i=1;i<totalRoom;i++) {
        printf("room: %d, edge: %d\n",path[i].object->room->room,roomList[path[i].object->room->room].amount);
    }
     */
    free(roomList);
    free(path);
}















