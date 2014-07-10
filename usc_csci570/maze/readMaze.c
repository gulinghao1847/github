//
//  readMaze.c
//  570hw4
//
//  Created by linghao on 12-11-6.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "maze.h"
#include "read.h"
#define LARG_W 100;
extern int is_stdin;
extern int soluForm;

struct lineArray{
    int position;
    int weight;
};

int is_room(int w, int h, int n){
    int i;
    i=n/w;
    if (i%2==0) {
        return 0;
    }
    else
    {
        int number=n-i*w;
        if (number%2==1) {
            //printf("%d,i%d\n",n,i);
            return 1;
        }
        else
            return 0;
    }
}

void findSpace(int w, int h,struct lineArray* lineArray, char* buffer){
    int count=0;
    int spaceCount=0;
    for (count=0;buffer[count]!='\0';count++) {
        /*
        if (is_room(w,h,count)) {
            if(buffer[count]!=' '){
                fprintf(stderr, "this maze (maybe room) is illegal\n");
                exit(1);
            }
        }
        */
        if (buffer[count]==' '&&(!is_room(w,h,count))) {
            lineArray[spaceCount].position=count;
            lineArray[spaceCount].weight=1;
            spaceCount++;
            //printf("not,~~~%c~~~~\n",buffer[count]);
        }
        else if((buffer[count]>='0'&&buffer[count]<='9')&&(!is_room(w,h,count))){
            soluForm=2;
            lineArray[spaceCount].position=count;
            lineArray[spaceCount].weight=(int)(buffer[count]-'0');
            spaceCount++;
        }
        /*
        else if(buffer[count]!='+'&&buffer[count]!='-'&&buffer[count]!='|'&&buffer[count]!='\n'&&buffer[count]!=' '){
            fprintf(stderr,"file format is wrong, please correct your file\n");
            exit(1);
        }
         */
    }
    lineArray[spaceCount].position=0;  //impossible result
}

void findEnt(int w, int h, struct lineArray* lineArray,int* e, int* ep, int* l, int* lp,maze_t* myMaze){
    int i=0;
    int count=0;
    for (i=0;lineArray[i].position!=0;i++) {
        int num=lineArray[i].position;
        if (num%w==(w-2)||num%w==0||(num<w-1)||((num>w*(h-1))&&(num<w*h-1))) {
            //printf("come\n");
            if (*e==0&&count==0) {
                *e=num%w;
                *ep=num/w;
                myMaze->num[0]=num;
                count++;
                //printf("%d\n",count);
            }
            else if(*l==0&&count==1){
                *l=num%w;
                *lp=num/w;
                myMaze->num[1]=num;
                count++;
                //printf("%d\n",count);
            }
            else{
                fprintf(stderr,"more than two entrance\n");
                exit(1);
            }
        }
    }
    //printf("%d,%d,%d,%d",*e,*ep,*l,*lp);
}

void updateMaze(int w, int h,struct lineArray* lineArray,maze_t* maze){
    //int count=0;
    int spaceCount=0;
    int i;
    int height;
    int width;
    //int count=0;
    for (i=0;lineArray[i].position!=0;i++) {
        int num=lineArray[i].position;
        if (!(num%w==(w-2)||num%w==0||(num<w-1)||((num>w*(h-1))&&(num<w*h-1)))) {
            //count++;
            if ((num/w)%2==1) {                  // line that have rooms
                height=(num/w-1)/2;
                width=(w-1)/2;
                maze->lineInfo->deletedLines[spaceCount].number=(2*width-1)*height+(num%w)/2-1;
                maze->lineInfo->deletedLines[spaceCount++].weight=lineArray[i].weight;
            }
            else if((num/w)%2==0){
                height=(num/w-1)/2;
                width=(w-1)/2;
                maze->lineInfo->deletedLines[spaceCount].number=(2*width-1)*height+width-2/*caution!!*/+(num%w+1)/2;
                maze->lineInfo->deletedLines[spaceCount++].weight=lineArray[i].weight;
            }
        }
    }
    //printf("in updateMaze:%d",count);
    maze->lineInfo->deletedLines[spaceCount].number=-1;
}

void checkIfRight(int w, int h, char* buffer){
    if (strlen(buffer)<2) {
        return;
    }
    int i=0;
    char test[4];
    for (i=0;buffer[i+1]!='\n';i=i+2) {
        test[0]=buffer[i];
        test[1]=buffer[i+1];
        test[2]='\0';
        if (h%2==0) {                     //
            if (strcmp(test,"+-")!=0&&strcmp(test,"+ ")!=0&&strcmp(test,"+\n")!=0) {
                if (test[1]>='0'&&test[1]<='9') {
                    continue;
                }
                //printf("one %s\n",test);
                fprintf(stderr,"format error\n");
                exit(1);
            }
        }
        else if (strcmp(test,"| ")!=0&&strcmp(test,"  ")!=0&&strcmp(test,"|\n")!=0&&strcmp(test," \n")!=0) {
            if (test[0]>='0'&&test[0]<='9') {
                continue;
            }
            //printf("two: ~~1%s~~~\n",test);
            fprintf(stderr,"format error\n");
            exit(1);
        }
            
    }
}

char* readMazeFile(maze_t* myMaze,char* file_name){
    FILE* file;
    int largestBuffer=2+2*LARG_W;
    int w=0;
    int h=0;
    int enterPos=0;
    int enter=0;
    int leavePos=0;
    int leave=0;
    int lw=200;
    int lh=100;
    char* buffer=(char*)malloc(largestBuffer*sizeof(char));
    char* whole=(char*)malloc((lw*lh+5)*sizeof(char));
    
    
    if (is_stdin) {
        fgets(buffer,largestBuffer,stdin);
        //printf("~~~~%s~~~~",buffer);
        w=(int)strlen(buffer);
        strcpy(whole,buffer);
        //printf("width:%d,,,%s",w,buffer);
        h=h+1;
        while (fgets(buffer,largestBuffer,stdin)!=NULL) {
            if (strlen(buffer)!=w) {
                fprintf(stderr,"file format is wrong , please correct your maze\n");
                exit(1);
            }
            checkIfRight(w,h,buffer);
            h=h+1;
            strcat(whole,buffer);
        }

    }
    else{
        if ((file=fopen(file_name,"r"))==NULL) {
            //printf("here\n");
            fprintf(stderr,"can't open this file\n");
            exit(1);
        }
        fgets(buffer,largestBuffer,file);
        w=(int)strlen(buffer);
        strcpy(whole,buffer);
        //printf("width:%d,,,%s",w,buffer);
        h=h+1;
        while (fgets(buffer,largestBuffer,file)!=NULL) {
            
            
            if (strlen(buffer)!=w) {
                fprintf(stderr,"file format is wrong , please correct your maze\n");
                exit(1);
            }
            checkIfRight(w,h,buffer);
            strcat(whole,buffer);
            h=h+1;
        }
    //free(buffer);
        fclose(file);
    }
    //checkIfRight(,,buffer)
    //printf("hello in readMaze:\n%s\n",whole);
    
    struct lineArray* Array=(struct lineArray*)malloc(w*h*sizeof(struct lineArray));
    findSpace(w,h,Array,whole);
    findEnt(w,h,Array,&enter,&enterPos,&leave,&leavePos,myMaze);
    initMaze(enterPos,enter,leavePos,leave,(w-1)/2,(h-1)/2,myMaze);
    updateMaze(w,h,Array,myMaze);
    free(Array);
    free(buffer);
    return whole;
}





