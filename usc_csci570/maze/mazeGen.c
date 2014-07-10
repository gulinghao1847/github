//
//  mazeGen.c
//  570hw4
//
//  Created by linghao on 12-11-4.
//  Copyright (c) 2012年 linghao. All rights reserved.
//
//first room is 0;
//first line is 0;
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"


void initIntArray(array_t* intArray,int number){
    int count=0;
    intArray->count=number;
    intArray->array=(int*)malloc(number*sizeof(int));
    for (;count<number;count++) {
        intArray->array[count]=count;
    }
}

int deleteElem(array_t* intArray, int where){
    int ret=intArray->array[where];
    int count=where;
    for (;count<intArray->count;count++) {
        intArray->array[count]=intArray->array[count+1];
    }
    //free(&intArray->array[intArray->count--]);
    return ret;
}

void initLineInfo(int h, int w,lines_t* init){
    init->totalNumber=2*w*h-w-h;
    init->height=h;
    init->width=w;
    init->deletedLines=(struct line*)malloc((init->totalNumber)*sizeof(struct line));
    int i=0;
    for (i=0;i<init->totalNumber;i++) {
        init->deletedLines[i].number=-1;
    }
}

int initRoom(maze_t* maze,lines_t* line){
    int number=line->height*line->width;
    int iter;
    maze->room=(room_t*)malloc(number*sizeof(room_t));
    for (iter=0;iter<number;iter++) {
        maze->room[iter].unionParent=NULL;
        maze->room[iter].room=iter;
        maze->room[iter].parent=-1;
        maze->room[iter].edge=-1;
        maze->room[iter].depth=-1;
    }
    return number;
}

void initMaze(int enterPos,int enter,int leavePos, int leave, int weight, int height,maze_t* maze){
    maze->enter=enter;
    maze->enterPos=enterPos;
    maze->leave=leave;
    maze->leavePos=leavePos;
    maze->lineInfo=(lines_t*)malloc(sizeof(lines_t));
    initLineInfo(height,weight,maze->lineInfo);
    maze->roomNumber=initRoom(maze,maze->lineInfo);
    
}

int getFirstRoom(int line,lines_t* lineInfo){
    int ech=0;  //each_line_number
    int n=0;    //the row this line belong to
    int room=0;  //the first room
    int temp=line;
    ech=2*lineInfo->width-1;
    for (n=0;temp-ech>=0;n++) {
        temp=temp-ech;
    }
    if (temp<lineInfo->width-1) {
        room=n*lineInfo->width+temp;
    }else
        room=n*lineInfo->width+temp-(lineInfo->width-1);
    return room;
}

int getSecondRoom(int line,lines_t* lineInfo){
    int ech=0;  //each_line_number
    int n=0;    //the row this line belong to
    int room=0;  //the second room
    int temp=line;
    ech=2*lineInfo->width-1;
    for (n=0;temp-ech>=0;n++) {
        temp=temp-ech;
    }
    if (temp<lineInfo->width-1) {
        room=n*lineInfo->width+temp+1;
    }else
        room=(n+1)*lineInfo->width+temp-(lineInfo->width-1);
    return room;
}

int is_deleted(int line,maze_t* myMaze){
    int totalNumber=myMaze->roomNumber;
    int i=0;
    for (i=0;i<totalNumber;i++) {
        if (myMaze->lineInfo->deletedLines[i].number==line) {
            return 1;
        }
    }
    return 0;
}

int isEnt(int pos, int where,maze_t* myMaze){
    //printf("enter:%d,enterPos:%d\n",myMaze->enter,myMaze->enterPos);
    int entPos=myMaze->enterPos;
    int leaPos=myMaze->leavePos;
    int ret=0;
    if (pos==entPos) {
        if(where==myMaze->enter)
            ret=1;
        else
            ret=0;
    }
    else if (pos==leaPos) {
        if (where==myMaze->leave) {
            ret=1;
        }
        else
            ret=0;
    }
    else
        ret=0;
    return ret;
}

void printTB(int where,maze_t* myMaze){        //where=1 indicate top     where=2 indicate bottom
    int w=myMaze->lineInfo->width;
    int count=0;
    for (;count<w;count++) {
        if (isEnt(where,count+1,myMaze)) {
            printf("+ ");
        }
        else
            printf("+-");
    }
    printf("+\n");
}


void printEvenLine(int where, maze_t* myMaze){
    if (isEnt(3,where+1, myMaze)) {
        printf(" ");
        //printf("here\n");
    }
    else
        printf("|");
    int w=myMaze->lineInfo->width;
    int count=0;
    for (;count<w-1;count++) {
        if(is_deleted(where*(2*w-1)+count,myMaze)){
            printf("  ");
        }else
            printf(" |");
    }
    
    if (isEnt(4,where+1, myMaze)) {
        printf("  \n");
        //printf("here\n");
    }
    else
        printf(" |\n");
}


void printOddLine(int where,maze_t* myMaze){
    int w=myMaze->lineInfo->width;
    int count=0;
    for (;count<w;count++) {
        if (is_deleted(where*(2*w-1)+count+w-1,myMaze)) {
            printf("+ ");
        }else
            printf("+-");
    }
    printf("+\n");
}

void print(maze_t* myMaze){
    int count=0;
    int h=myMaze->lineInfo->height;
    //int w=myMaze->lineInfo->width;
    //char* buffer=(char*)malloc((myMaze->lineInfo->height*2+5)*(myMaze->lineInfo->width*2+5)*sizeof(char));
    printTB(1,myMaze);
    for (count=0;count<h-1;count++) {
        printEvenLine(count,myMaze);
        printOddLine(count,myMaze);
    }
    printEvenLine(count,myMaze);
    printTB(2,myMaze);
}


void freeMaze(maze_t* maze){
    free(maze->lineInfo->deletedLines);
    free(maze->room);
    free(maze);
}

