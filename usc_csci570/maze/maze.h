//
//  maze.h
//  570hw4
//
//  Created by linghao on 12-11-4.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70hw4_maze_h
#define _70hw4_maze_h
//#include "global.h"
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define NUMBER 4000
#define SIZE 4

typedef struct intArray{
    int* array;
    int count;
}array_t;

typedef int door;
typedef struct room room_t;
struct room{
    int parent;
    int room;
    int edge;
    int depth;
    int amount;
    room_t* unionParent;
};

//typedef int line;

struct line{
    int weight;
    int number;
};

typedef struct lineInfo{
    int totalNumber;
    struct line* deletedLines;
    int width;
    int height;
}lines_t;

typedef struct maze{
    int enter;       //position from 0;
    int enterPos;    //in which line, from line 0;
    int leave;
    int leavePos;
    int roomNumber;
    room_t* room;
    lines_t* lineInfo;
    int num[2];
    int maxDepth;
}maze_t;

typedef struct edge edge_t;
typedef struct object object_t;
typedef struct adList adList_t;

struct edge{
    struct line number;
    edge_t* nextEdge;
    object_t* endRoom;
    int weight;
    //int depth;
};

//typedef struct object object_t;

struct object{
    room_t* room;
    edge_t* firstEdge;
    //int depth;
    //int amount;
    //edge_t* lastLine;   // the last line which make amount min
};

struct adList{
    int count;
    object_t* object;
};

typedef struct orgRoom{
    object_t* object;
    int amount;
    edge_t* lastLine;
    int used;
}orgRoom_t;

typedef struct path{
    object_t* object;
    edge_t* edge;
    //object_t* next;
}path_t;

typedef struct soluPath{
    int* room;
    int* edge;
}solu_t;
//maze generate
//void initLineInfo(int h, int w,lines_t* init);
void initMaze(int enterPos,int enter,int leavePos, int leave, int weight, int height,maze_t*);
//int initRoom(room_t* room,lines_t* line);
int getFirstRoom(int line,lines_t* lineInfo);
int getSecondRoom(int line,lines_t* lineInfo);
void initIntArray(array_t* intArray,int number);
int deleteElem(array_t* intArray, int where);
//int is_deleted(int line,lines_t* lineInfo,int number); //unimplement
void print (maze_t* maze);//unimplement

//maze solution    mazeSolu.c file
void doBFS(maze_t* myMaze, adList_t* adList);
void genAdj(maze_t* myMaze, adList_t* adList);
void doDijk(adList_t* adList,maze_t* myMaze);
int getStartRoom(maze_t* myMaze);
int getEndRoom(maze_t* myMaze);

//mazeSoluGen       mazeSoluGen.c
void genePath(solu_t* path,maze_t* myMaze);
void printMaze(char* buffer, solu_t* path, maze_t* myMaze);
void initSoluPath(solu_t* path,int num);
#endif
