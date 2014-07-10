//
//  main.c
//  570hw4
//
//  Created by linghao on 12-11-3.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include "read.h"
#include "maze.h"
//#include "global.h"
#include "unionFind.h"
#define GEN 1;
#define Solu 2;
#define SHOW 1;
#define NOTSHOW 0;
int instruction=0;
int is_stdin=1;  // 1:stdin  0: not stdin
char file_name[256];
int w=0;
int h=0;
int Ent=1;
int EntPos=UP;
int lea=0;
int leaPos=DOWN;
int show=NOTSHOW;
int soluForm=1;  //1:bfs  2:dijk
//#include "mazeSolu.c"
void geneMaze(/*int enterPos,int enter,int leavePos, int leave, int weight, int height,char* file_name*/){
    //init
    //open FILE* file;
    //initialize
    char* buffer=(char*)malloc(NUMBER*SIZE*sizeof(char));
    //unsigned long bufferLen=strlen(buffer);
    maze_t* myMaze=(maze_t*)malloc(sizeof(maze_t));
    initMaze(EntPos,Ent,leaPos,lea,w,h,myMaze);
    unsigned long len=0;
    if (is_stdin) {
        len=readStdIn(buffer);
    }else
        len=readFile(file_name,buffer);
    //initialize finished
    
    
    //build the maze
    //printf("len:%lu\n",len);
    int totalNumber=myMaze->lineInfo->totalNumber;
    int iter=0;
    //printf("4here\n");
    int delWal=myMaze->lineInfo->totalNumber;
    //printf("4here\n");
    int number=0;
    int Wal=0;
    int hasDel=0;
    //int i=0;
    room_t* firstRoom;
    room_t* secondRoom;
    room_t* room=myMaze->room;
    //printf("4here\n");
    array_t* delArray=(array_t*)malloc(sizeof(array_t));
    //printf("4here\n");
    initIntArray(delArray,totalNumber);
    //printf("4here\n");
    //printf("%d\n",delArray->array[16]);
    
    un_t* unionFind=(un_t*)malloc((myMaze->roomNumber)*sizeof(un_t));
    initUnionFind(unionFind,myMaze->roomNumber);
    //printf("4here\n");
    //printf("line 0:%d,%d\n",getFirstRoom(15,myMaze->lineInfo),getSecondRoom(15,myMaze->lineInfo));
    for (;iter<totalNumber;iter++) {
        number=getNext(buffer,iter,len)%(delWal--);
        Wal=deleteElem(delArray,number);
        //printf("first room:%d\n",getSecondRoom(Wal,myMaze->lineInfo));
        firstRoom=&room[getFirstRoom(Wal,myMaze->lineInfo)];
        secondRoom=&room[getSecondRoom(Wal,myMaze->lineInfo)];
        un_t* first=&unionFind[firstRoom->room];
        un_t* second=&unionFind[secondRoom->room];
        
        if (findRoot(first)==findRoot(second)) {
            //printf("here%d\n",Wal);
            continue;
        }
        else{
            myMaze->lineInfo->deletedLines[hasDel].number=Wal;
            //printf("%d  %d    %dlalalala\n",Wal,firstRoom->parent,secondRoom->parent);
            myMaze->lineInfo->deletedLines[hasDel++].weight=1;
            unionT(findRoot(first),findRoot(second));
            if (show) {
                printf("Wall %d removed.\n",Wal);
            }
        }
    }
    if (hasDel!=myMaze->lineInfo->height*myMaze->lineInfo->width-1) {
        fprintf(stderr,"can't generate a maze\n");
        exit(1);
    }
    print(myMaze);
    //printf("%d")
    free(buffer);
    free(myMaze);
    free(delArray);
}

void mazeSolu(){
    maze_t* maze=(maze_t*)malloc(sizeof(maze_t));
    char* buffer=readMazeFile(maze,file_name);
    //printf("%s\n",buffer);
    //readMazeFile(maze,"j0");
    adList_t* adList=(adList_t*)malloc(sizeof(adList_t));
    //print(maze);
    genAdj(maze,adList);
    if (soluForm==1) {
        doBFS(maze,adList);
    }
    else
        doDijk(adList,maze);
    solu_t* path =(solu_t*)malloc(sizeof(solu_t));
    initSoluPath(path,maze->roomNumber+3);
    genePath(path,maze);
    printMaze(buffer,path,maze);
    int lastRoom=getEndRoom(maze);
    if (soluForm==1) {
        printf("Cost of shortest path = %d.\nMaximum level = %d.\n",maze->room[lastRoom].depth,maze->maxDepth);
    }
    else
        printf("Cost of shortest path = %d.\n",maze->room[lastRoom].amount);
    free(maze);
    free(adList);
    free(path);
}

void usage(){
    fprintf(stderr,"\nthe right format is: \nhw4 mazegen w h -info -top=tpos -bottom=bpos -left=lpos -right=rpos rndfile\nhw4 mazesolve file\n");
    exit(1);
}

void wrongWarning(char* buffer){
    fprintf(stderr,"%s",buffer);
    usage();
}

void check(int pos, int where){
    if (pos==1||pos==2) {
        if (where>w) {
            wrongWarning("illegal input");
        }
    }
    else if(where>h)
        wrongWarning("illegal input");
}
void checkVar(){
    check(EntPos,Ent);
    check(leaPos,lea);
}

int getPos(int number){
    int ret=0;
    if (number==1) {
        ret=0;
    }else if(number==3||number==4){
        ret=1;
    }
    else if(number==2)
        ret=2;
    return ret;
}

void change(){
    int temp_pos=EntPos;
    int temp=Ent;
    EntPos=leaPos;
    Ent=lea;
    leaPos=temp_pos;
    lea=temp;
}

void modifyEntAndExit(){
    int ent_pos=getPos(EntPos);
    int lea_pos=getPos(leaPos);
    if (ent_pos<lea_pos) {
    }
    else if(ent_pos==lea_pos){
        if (Ent>lea) {
            change();
        }
    }
    else if (ent_pos>lea_pos)
        change();
}

void inputNumber(int pos, int where,int* count){
    //printf("pos:%d",pos);
    if (*count==0) {
        Ent=where;
        EntPos=pos;
        //printf("EntPos%d\n",EntPos);
        (*count)++;
    }
    else if(*count==1){
        lea=where;
        leaPos=pos;
        (*count)++;
        //printf("leaPos%d\n",leaPos);
        //printf("%d\n",*count);
    }
    else if (*count>=2)
        wrongWarning("you must specify none or two of -top, -bottom, -left,-right ");
}

int getNumber(char* buffer){
    int count=0;
    int i=0;
    char number[5];
    int num=0;
    for (i=0;i<strlen(buffer);i++) {
        if (buffer[i]>='0'&&buffer[i]<='9') {
            number[count++]=buffer[i];
        }
    }
    number[count]='\0';
    num=atoi(number);
    if (num>65) {
        wrongWarning("this number is too large");
    }
    return num;
}

void getInfo(char* buffer,int *count){
    int number=0;
    //int count=0;
    if (strcmp(buffer,"-info")==0) {
        show=SHOW;
    }
    else if(strcmp(buffer,"-top=0")>0&&strcmp(buffer,"-top=99")<0){
        number=getNumber(buffer);
        inputNumber(1,number,count);
    }
    else if (strcmp(buffer,"-bottom=0")>0&&strcmp(buffer,"-bottom=99")<0){
        number=getNumber(buffer);
        inputNumber(2,number,count);
    }
    else if (strcmp(buffer,"-left=0")>0&&strcmp(buffer,"-left=99")<0){
        number=getNumber(buffer);
        inputNumber(3,number,count);
    }
    else if (strcmp(buffer,"-right=0")>0&&strcmp(buffer,"-right=99")<0){
        number=getNumber(buffer);
        inputNumber(4,number,count);
    }
    else
    {printf("%s\n",buffer);wrongWarning("the number is too large or too small or\nthe format you type is wrong");}
}

int checkIfNumber(char* buffer){
    int i=0;
    for (i=0;i<strlen(buffer);i++) {
        if (buffer[i]<'0'||buffer[i]>'9') {
            wrongWarning("illegal number");
        }
    }
    return 1;
}

void doGenOption(int argc, char* argv[]){
    int count=0;
    ++argv;
    if (!argc) {
        wrongWarning("lose weight and height");
    }
    else if(checkIfNumber(*argv)){
        w=atoi(*argv++);
        lea=w;
        if (w>64||w<=0) {
            wrongWarning("w is too large or too small");
        }
    }
    
    if (!--argc) {
        wrongWarning("lose height");
    }
    else if(checkIfNumber(*argv)){
        h=atoi(*argv++);
        if (h>32||h<=0) {
            wrongWarning("h is too large or too small");
        }
    }
    
    
    while (--argc&&*argv[0]=='-') {
        //printf("\nhere\n");
        getInfo(*argv++,&count);
    }
    //printf("here\n");
    if (count!=0&&count!=2) {
         wrongWarning("you must specify none or two of -top, -bottom, -left,-right ");
    }
    if (argc==1) {
        //printf("here\n");
        strcpy(file_name,*argv);
        is_stdin=0;
    }
    else if(argc==0){
        //printf("here out \n");
            return;
    }
    else if(argc>1){
        wrongWarning("too many arguments");
    }
    //printf("here\n");
    return;
}

void doSoluOption(int argc, char* argv[]){
    if (!argc--) {
        return;
    }
    else{
        strcpy(file_name,*(++argv));
        is_stdin=0;
    }
    
    if (argc) {
        wrongWarning("too many arguments");
    }
    
}

void doOption(int argc,char* argv[]){
    --argc==0?wrongWarning("lose command"):0;
    argv++;
    //argv++;
    argc--;
    if (strcmp(*argv,"mazegen")==0){
        instruction=GEN;
        doGenOption(argc,argv);
    }
    else if(strcmp(*argv,"mazesolve")==0){
        instruction=Solu;
        //printf("%d\n",argc);
        doSoluOption(argc,argv);
    }
    else
        wrongWarning("unspecified command");
    if (instruction==1) {
        modifyEntAndExit();
        checkVar();
    }
    //printf("here dooption\n");
}

int main(int argc,char * argv[])
{
    doOption(argc,argv);
    if (instruction==1) {
        geneMaze();
    }
    else if(instruction==2){
        mazeSolu();
    }
    /*printf("instruction:%d  w:%d  h:%d  ent:%d  entPos:%d   lea:%d  leaPos:%d   file_name:%s is_std:%d\n",instruction,w,h,Ent,EntPos,lea,leaPos,file_name,is_stdin);
     */
    return 0;
}

