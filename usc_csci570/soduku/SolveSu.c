//
//  SolveSu.c
//  hw5
//
//  Created by linghao on 12-11-27.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>

#include "SolveSu.h"

extern int max;

int initEmptyArray(int**suArray, int** emptyArray){
    int count=0;
    int i=0;
    int j=0;
    for (i=0;i<9;i++) {
        for (j=0;j<9;j++) {
            if (suArray[i][j]==0) {
                //printf("%d,%d \n",i,j);
                emptyArray[count][0]=i;
                emptyArray[count][1]=j;
                //printf("%d,%d \n",emptyArray[count][0],emptyArray[count][1]);
                count++;
            }
        }
    }
    emptyArray[count][0]=emptyArray[count][1]=-1;
    return count;
}

void initSuArray(int** puzzle, int** suArray){
    int i=0,j=0;
    for (i=0;i<9;i++) {
        suArray[i]=(int*)malloc(9*sizeof(int));
    }
    for (i=0;i<9;i++) {
        for (j=0;j<9;j++) {
            suArray[i][j]=puzzle[i][j];
        }
    }
}

int findRegion(int row, int column){   //list all the conditions
    int ret=10;
    if (row<=2){
        if (column<=2) {
            ret=0;
        }else if (column>=3&&column<=5){
            ret=1;
        }else if(column>=6&&column<=8){
            ret=2;
        }
        else
            fprintf(stderr,"impossible in findRegion\n");
    }else if (row>=3&&row<=5){
        if (column<=2) {
            ret=3;
        }else if (column>=3&&column<=5){
            ret=4;
        }else if(column>=6&&column<=8){
            ret=5;
        }
        else
            fprintf(stderr,"impossible in findRegion\n");
    }else if(row>=6&&row<=8){
        if (column<=2) {
            ret=6;
        }else if (column>=3&&column<=5){
            ret=7;
        }else if(column>=6&&column<=8){
            ret=8;
        }
        else
            fprintf(stderr,"impossible in findRegion\n");
    }else
        fprintf(stderr,"impossible in findRegion\n");
    return ret;
}

void initOcc(int** suArray, Occ_t* occ){
    //array_t temp;
    int i=0;
    int j=0;
    for(i=0;i<9;i++){
        occ->row[i].array_first_empty=0;
        occ->column[i].array_first_empty=0;
        occ->region[i].array_first_empty=0;
        for (j=0;j<9;j++) {
            occ->row[i].array[j]=-1;
            occ->column[i].array[j]=-1;
            occ->region[i].array[j]=-1;
        }
    }
    for (i=0; i<9;i++) {    // row
        for (j=0;j<9;j++) {   //column
            if (suArray[i][j]!=0) {
                //printf("wrong!\n");
                //printf("%d,%d  %d    ",i,j,suArray[i][j]);
                occ->row[i].array[occ->row[i].array_first_empty]=suArray[i][j];
                occ->column[j].array[occ->column[j].array_first_empty]=suArray[i][j];
                occ->region[findRegion(i,j)].array[occ->region[findRegion(i,j)].array_first_empty]=suArray[i][j];
                occ->row[i].array_first_empty+=1;
                occ->column[j].array_first_empty+=1;
                occ->region[findRegion(i,j)].array_first_empty+=1;
            }
        }
    }
}

int findAviNum(int where,int position,Occ_t* occ){  //where=1: row, where=2: column, where=3:region
    int min=1;
    int i=0;
    int ret=0;
    if (where==1) {
        for (i=0;occ->row[position].array[i]!=-1;i++) {
            if (occ->row[position].array[i]==min) {
                i=-1;
                min++;
            }
        }
        ret=min;
    }
    return ret;
}

int checkRow(int curElem,int row,Occ_t* occ){
    int i=0;
    for (i=0;occ->row[row].array[i]!=-1;i++) {
        if (occ->row[row].array[i]==curElem) {
            //printf("row,%d,,%d\n",occ->row[row].array[i],row);
            return 0;
        }
    }
    return 1;
}

int checkColumn(int curElem,int column,Occ_t* occ){
    int i=0;
    for (i=0;occ->column[column].array[i]!=-1;i++) {
        if (occ->column[column].array[i]==curElem) {
            //printf("col,%d,,%d\n",occ->column[column].array[i],column);
            return 0;
        }
    }
    return 1;
}

int checkRegion(int curElem,int row, int column,Occ_t* occ){
    int i=0;
    int region=findRegion(row,column);
    //printf("region:%d\n",region);
    for (i=0;occ->region[region].array[i]!=-1;i++) {
        if (occ->region[region].array[i]==curElem) {
            //printf("region:~~~~~~~~\n");
            return 0;
        }
    }
    return 1;
}
/*
int getNext(int curElem,int row, int column,Occ_t* occ){
    int next=findAviNum(1,row,occ);
    printf("next val:%d\n",next);
    if (curElem<next) {
    }else
        next=curElem+1;
    return next;
}
*/
int ifConsistent(int curElem, int row, int column,Occ_t* occ){
    int ret=0;
    //printf("curElem:%d,row:%d,column:%d\n",curElem,row,column);
    if(checkColumn(curElem,column,occ)&&checkRegion(curElem,row,column,occ)&&checkRow(curElem,row,occ)){
        ret=1;
    }
    else
        ret=0;
    return ret;
}


void update(int curElem, int row, int column, Occ_t* occ){
    int region=findRegion(row,column);
    occ->column[column].array[occ->column[column].array_first_empty++]=curElem;
    occ->row[row].array[occ->row[row].array_first_empty++]=curElem;
    occ->region[region].array[occ->region[region].array_first_empty++]=curElem;
}

void minus(int curElem, int row, int column, Occ_t* occ){
    int region=findRegion(row,column);
    occ->column[column].array[--(occ->column[column].array_first_empty)]=-1;
    occ->row[row].array[--(occ->row[row].array_first_empty)]=-1;
    occ->region[region].array[--(occ->region[region].array_first_empty)]=-1;
}

int solveSudoku(int** suArray, int** emptyArray, int numEmp,Occ_t* occ){
    int i=0;
    int curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
    while (i<numEmp) {
        if (curElem<9) {
            //curElem=getNext(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            curElem++;
            if (ifConsistent(curElem,emptyArray[i][0],emptyArray[i][1],occ)) {
                suArray[emptyArray[i][0]][emptyArray[i][1]]=curElem;
                update(curElem,emptyArray[i][0],emptyArray[i][1],occ);
                i++;
                curElem=0;
                //printf("in one\n");
            }
        }
        else{
            suArray[emptyArray[i][0]][emptyArray[i][1]]=0;
            i--;
            if (i<0) {
                printf("impossible,this puzzle can't be solved\n");
                exit(1);
            }
            curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
            minus(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            //printf("in three\n");

        }
    }
    return 0;
}

int countSudoku(int** suArray, int** emptyArray, int numEmp,Occ_t* occ,My570List* list,int needStore){
    int i=0;
    //int solution=0;
    //int j=0;
    int count=0;
    //int test1=0;
    //int test2=0;
    int curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
    while (i<numEmp) {
        if (curElem<9) {
            //curElem=getNext(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            curElem++;
            if (ifConsistent(curElem,emptyArray[i][0],emptyArray[i][1],occ)) {
                suArray[emptyArray[i][0]][emptyArray[i][1]]=curElem;
                
                if (i==numEmp-1) {
                    // indicate that a solution has been found
                    count++;
                    //printf("here,%d\n",curElem);
                    if(needStore==1){
                    int** soluArray=(int**)malloc(9*sizeof(int*));
                    initSuArray(suArray,soluArray);
                    My570ListAppend(list,soluArray);
                    }
                    suArray[emptyArray[i][0]][emptyArray[i][1]]=0;
                    if (max!=0) {
                        if (count>=max) {
                            return count;
                        }
                    }
                }
                else{
                    update(curElem,emptyArray[i][0],emptyArray[i][1],occ);
                    i++;
                    curElem=0;
                }
            }
        }
        else{
            suArray[emptyArray[i][0]][emptyArray[i][1]]=0;
            i--;
            if (i<0) {
                //printf("impossible\n");
                return count;
            }
            curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
            minus(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            //printf("in three\n");
        }
    }
    return count;
}

int getNextNum(int line,int where,int** orgArray){
    return orgArray[line][where];
}

int findWhere(int line, int curElem, int** orgArray){
    int i=0;
    int ret=0;
    int result=0;
    for (i=0;i<9;i++) {
        if (orgArray[line][i]==curElem) {
            ret=i;
            result=1;
            //printf("here,line:%d",line);
        }
    }
    if (result==0) 
        fprintf(stderr,"impossible in where\n");
    return ret;
}

int genOrgSu(int** suArray, int** emptyArray, int numEmp,Occ_t* occ,int** orgArray){
    int i=0;
    int curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
    int where=-1;
    int line=0;
    while (i<numEmp) {
        if (where<8) {
            //curElem=getNext(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            where++;
            line=i/9;
            curElem=getNextNum(line,where,orgArray);
            //printf("%d,%d,\n",curElem,line);
            if (ifConsistent(curElem,emptyArray[i][0],emptyArray[i][1],occ)) {
                suArray[emptyArray[i][0]][emptyArray[i][1]]=curElem;
                update(curElem,emptyArray[i][0],emptyArray[i][1],occ);
                i++;
                where=-1;
                //printf("in one\n");
            }
        }
        else{
            suArray[emptyArray[i][0]][emptyArray[i][1]]=0;
            i--;
            if (i<0) {
                printf("impossible\n");
                return 1;
            }
            curElem=suArray[emptyArray[i][0]][emptyArray[i][1]];
            where=findWhere(i/9,curElem,orgArray);
            minus(curElem,emptyArray[i][0],emptyArray[i][1],occ);
            //printf("in three\n");
        }
    }
    return 0;
}

void initDeleteArray(int** suArray,intarray_t* deleteArray){
    int i=0;
    int j=0;
    int count=0;
    for (i=0;i<9;i++) {
        for (j=0;j<9;j++) {
            count++;
            deleteArray->array[9*i+j]=9*i+j;
        }
    }
    deleteArray->count=count;
}

void printHead(){
    printf("+---+---+---+\n");
}

void printLine(int* org, int* sol){
    int countNum=0;
    int countPosition=0;
    for (countNum=0;countNum<9;) {
        if (countPosition%4==0) {
            printf("|");
            countPosition++;
        }else {
            if (org[countNum]==sol[countNum]) {
                printf(".");
            }else
                printf("%d",sol[countNum]);
            countPosition++;
            countNum++;
        }
    }
    printf("|\n");
}

void printSu(int** org,int** sol){
    int line=0;
    printHead();
    for (;line<3;line++) {
        printLine(org[line],sol[line]);
    }
    printHead();
    for (;line<6;line++) {
        printLine(org[line],sol[line]);
    }
    printHead();
    for (;line<9;line++) {
        printLine(org[line],sol[line]);
    }
    printHead();
}







