//
//  mazeSoluGen.c
//  570hw4
//
//  Created by linghao on 12-11-11.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void initSoluPath(solu_t* path,int num){
    path->edge=(int*)malloc((num+2)*sizeof(int));
    path->room=(int*)malloc((num+2)*sizeof(int));
}

void freeSoluPath(solu_t* path){
    free(path->edge);
    free(path->room);
    free(path);
}

void genePath(solu_t* path,maze_t* myMaze){
    int end=getEndRoom(myMaze);
    int iter=end;
    int i=0;
    for (;myMaze->room[iter].parent!=-1;iter=myMaze->room[iter].parent,i++) {
        path->room[i]=iter;
        path->edge[i]=myMaze->room[iter].edge;
    }
    
    path->room[i]=iter;
    path->edge[i++]=myMaze->room[iter].edge;
    if (myMaze->room[iter].room!=getStartRoom(myMaze)) {
        printf("impossible,can't generate solution\n");
        exit(1);
    }
    
    path->room[i]=-1;
    /*
    for (i=0;path->room[i]!=-1;i++) {
        printf("room: %d, edge:%d\n",path->room[i],path->edge[i]);
    }
     */
}

void printMaze(char* buffer, solu_t* path, maze_t* myMaze){
    //int h=myMaze->lineInfo->height;
    int w=myMaze->lineInfo->width;
    int chLen=2*w+2;      //the length of every line
    //int chH=2*h+1;       //the height of the output
    int r=0;
    int l=0;
    //for room
    int i=0;
    int temp_1=0;
    int temp_2=0;
    for (i=0;path->room[i]!=-1;i++) {
        r=path->room[i];
        
        if (r%w==w-1) {
           buffer[chLen-1+2*chLen*((r)/w)+(r)%w*2+2]='@';
        }
        else
            buffer[chLen-1+2*chLen*((r+1)/w)+(r+1)%w*2]='@';
      
    }
    for (i=0;path->edge[i]!=-1;i++) {
        l=path->edge[i];
        temp_1=(l+1)/(2*w-1);
        temp_2=(l+1)%(2*w-1);
        if (temp_2<=w-1&&temp_2!=0) {
            buffer[chLen+2*chLen*temp_1+temp_2*2]='@';
        }
      
        else if(temp_2>w-1&&temp_2!=0)
            buffer[chLen+2*chLen*temp_1+chLen+(temp_2-w+1)*2-1]='@';
        else
            buffer[chLen+2*chLen*temp_1-3]='@';
        
    }
    for (i=0;buffer[i]!='\0';i++) {
        if (buffer[i]>='0'&&buffer[i]<='9') {
            buffer[i]=' ';
        }
    }
    buffer[myMaze->num[0]]='@';
    buffer[myMaze->num[1]]='@';
    printf("%s",buffer);
    
    int startRoom=getStartRoom(myMaze);
    //printf("startRoom:%d",startRoom);
    int endRoom=getEndRoom(myMaze);
    //printf("endRoom:%d",endRoom);
    int startRow=startRoom/w+1;
    int startColumn=startRoom%w+1;
    int endRow=endRoom/w+1;
    int endColumn=endRoom%w+1;
    printf("Starts in room at row = %d and column = %d.\nEnds in room at row = %d and column = %d.\n",startRow,startColumn,endRow,endColumn);
}







