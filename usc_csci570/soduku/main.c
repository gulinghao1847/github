//
//  main.c
//  hw5
//
//  Created by linghao on 12-11-26.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "my570list.h"
#include "ReadFile.h"
#include "SolveSu.h"
#include "GenSu.h"
int command=0;//  1:solve 2:count 3:gen
int is_stdin=1; //1 : is 0: is not
char file_name[256];
int printall=0;
int max=0;
int info=0;

void print9Mul9test(int** array){
    int i=0;
    int j=0;
    for (i=0;i<9;i++) {
        for (j=0;j<9;j++) {
            printf("%d",array[i][j]);
        }
        printf("\n");
    }
}

void genSu(){
    int i=0;
    int j=0;
    intarray_t** initArray=(intarray_t**)malloc(9*sizeof(intarray_t*));;
    int** resultArray =(int**)malloc(9*sizeof(int*));;
    char* buffer=(char*)malloc(2000*sizeof(char));
    
    int** array = (int**)malloc(9*sizeof(int*));
    int** suArray=(int**)malloc(9*sizeof(int*));
    int** elemArray=(int**)malloc(82*sizeof(int*));
    
    for (i=0;i<82;i++) {
        elemArray[i]=(int*)malloc(2*sizeof(int));
    }
    int emptNum=0;
    Occ_t* occ=(Occ_t*)malloc(sizeof(Occ_t));
    
    //int* deleteArray=(int*)malloc(81*sizeof(int));
    int** oldPuzzle=(int**)malloc(9*sizeof(int*));
    gen9Mul9Array(oldPuzzle);
    
    int count=0;
    int deleteNum=0;
    int position=0;
    unsigned int where=0;
    int row=0;
    int column=0;
    int len=81;
    intarray_t* deleteArray=(intarray_t*)malloc(sizeof(intarray_t*));
    deleteArray->array=(int*)malloc(100*sizeof(int));
    My570List* list=(My570List*)malloc(sizeof(My570List));
    
    //gen the org array
    if (is_stdin) {
        readBinStdin(buffer);
    }else
        readBinFile(file_name,buffer);
    
    gen9Mul9Array(resultArray);
    initGenInitArray(initArray);
    position=genOrgArray(initArray,resultArray,buffer);
    //free(buffer);
    free(initArray);
    
    
    
    //init array
    
    for (i=0;i<9;i++) {
        array[i]=(int*)malloc(9*sizeof(int));
        for (j=0;j<9;j++) {
            array[i][j]=0;
        }
    }
    
    //gen the solved sudoku
    initSuArray(array,suArray);
    initOcc(suArray,occ);
    emptNum=initEmptyArray(suArray,elemArray);
    genOrgSu(suArray,elemArray,emptNum,occ,resultArray);
    
    //print this solved sudoku
    if (info==1) {
        printf("Random shuffle results:\n\n");
        print9Mul9test(resultArray);
        printf("\n");
    }
    printf("Full board generated:\n\n");
    printSu(array,suArray);
    printf("\n");
    
    //gen a sudoku puzzle
    initDeleteArray(suArray,deleteArray);
    len=81;
    int count_1=0;
    while (count<2) {
        initSuArray(suArray,oldPuzzle);
        //count this suArraySulotion, need to prepare all the things that are needed
        where=getNext(buffer,position++);
        deleteNum=deleteElem(deleteArray,where%len--);
        //printf("elem:%d\n",deleteNum);
        row=deleteNum/9;
        column=deleteNum-row*9;
        suArray[row][column]=0;
        initOcc(suArray,occ);
        //printf("row: %d column:%d\n",row,column);
        emptNum=initEmptyArray(suArray,elemArray);
        count=countSudoku(suArray,elemArray,emptNum,occ,list,0);
        count_1++;
        if (info==1) {
            if(count==1){
                printf("Unassigning row %d column %d...\n",row+1,column+1);
            }
            else{
                printf("Unassigning row %d column %d.  %d solutions found.\n",row+1,column+1,count);
                printf("Row %d column %d restored.\n\n",row+1,column+1);
            }
        }
        //printf("count:%d,num: %d,%d\n",count,emptNum,len);
    }
    printf("Solution (after %d values unassigned):\n\n",count_1-1);
    printSu(array,oldPuzzle);
}

void countSu(){
    int i=0;
    int count;
    int** array = (int**)malloc(9*sizeof(int*));
    int** suArray=(int**)malloc(9*sizeof(int*));
    int** elemArray=(int**)malloc(9*9*sizeof(int*));
    for (i=0;i<81;i++) {
        elemArray[i]=(int*)malloc(2*sizeof(int));
    }
    int emptNum=0;
    
    
    Occ_t* occ=(Occ_t*)malloc(sizeof(Occ_t));
    
    
    My570List* list=(My570List*)malloc(sizeof(My570List));
    My570ListInit(list);
    
    My570List* resultList=(My570List*)malloc(sizeof(My570List));
    My570ListInit(resultList);
    
    if (is_stdin) {
        readStdin(list);
    }else{
        readFile(file_name, list);
    }
    
    staSudoku(list);
    initArray(array,list);
    initSuArray(array,suArray);
    initOcc(suArray,occ);
    emptNum=initEmptyArray(suArray,elemArray);
    count=countSudoku(suArray,elemArray,emptNum,occ,resultList,1);
    //printf("%d\n",count);
    My570ListElem* elem;
    /*
    for (elem=My570ListFirst(resultList);elem!=NULL;elem=My570ListNext(resultList,elem)) {
        for (test1=0;test1<9;test1++) {
            for (test2=0;test2<9;test2++) {
                printf("%d",((int**)(elem->obj))[test1][test2]);
            }
            printf("\n");
        }
    }
     */
    if (printall==1) {
        for (elem=My570ListFirst(resultList);elem!=NULL;elem=My570ListNext(resultList,elem)) {
            printSu(array,(int**)(elem->obj));
            printf("\n");
        }
    }
    if (count==1) {
        printf("%d solution found\n",count);
    }else
        printf("%d solutions found\n",count);
}

void solveSu()
{
    int i=0;
    //int j=0;
    int** array = (int**)malloc(9*sizeof(int*));
    int** suArray=(int**)malloc(9*sizeof(int*));
    int** elemArray=(int**)malloc(9*9*sizeof(int*));
    for (i=0;i<81;i++) {
        elemArray[i]=(int*)malloc(2*sizeof(int));
    }
    int emptNum=0;
    Occ_t* occ=(Occ_t*)malloc(sizeof(Occ_t));
    My570List* list=(My570List*)malloc(sizeof(My570List));
    My570ListInit(list);
    
    if (is_stdin) {
        readStdin(list);
    }else{
        //printf("here");
        readFile(file_name, list);
    }
    staSudoku(list);
    initArray(array,list);
    initSuArray(array,suArray);
    initOcc(suArray,occ);
    emptNum=initEmptyArray(suArray,elemArray);
    solveSudoku(suArray,elemArray,emptNum,occ);
    printSu(array,suArray);
}

void Usage(){
    fprintf(stderr,"Usage:\nhw5 solve [file]\nhw5 count [-printall] [-max=n] [file]\nhw5 gen [-info] [rndfile]");
    exit(1);
}

void wrongError(char* error){
    fprintf(stderr,"%s\n",error);
    Usage();
}

int getNumber(char* buffer){
    int i=0;
    int number=0;
    while (!(buffer[i]>'0'&&buffer[i]<='9')){
        i++;
        if (strlen(buffer)==i) {
            wrongError("-max=? you should enter a number");
        }
    }
    for(;buffer[i]!='\0';i++){
        
        number=number*10+(buffer[i]-'0');
    }
    return number;
}

void getInfo(char* buffer){
    char temp[20];
    if (command==2) {
        if (strcmp(buffer,"-printall")==0) {
            printall=1;
        }else{
            strcpy(temp,buffer);
            temp[5]='\0';
            if (strcmp(temp,"-max=")==0) {
                max=getNumber(buffer);
            }else if(buffer[0]=='-'){
                wrongError("you should enter the right command for count");
            }
            else {
                strcpy(file_name,buffer);
                is_stdin=0;
            }
        }
    }else if(command==3){
        if (strcmp(buffer,"-info")==0) {
            info=1;
        }else if(buffer[0]=='-'){
            wrongError("you should enter the right command for gen");
        }
        else{
            strcpy(file_name,buffer);
            is_stdin=0;
        }
    }
}

void doSolveOption(int argc,char** argv){
    if (argc==1) {
    }else{
        argc--;
        argv++;
        strcpy(file_name,*argv);
        is_stdin=0;
    }
    if (argc>1) {
        wrongError("too many arguments");
    }
}

void doCountOption(int argc, char** argv){
    if (argc==1) {
    }if(argc>4){
        wrongError("too many arguments");
    }
    else{
        while (--argc) {
            argv++;
            getInfo(*argv);
        }
    }
}

void doGenOption(int argc, char** argv){
    if (argc==1) {
    }else if(argc>3){
        wrongError("too many arguments");
    }else{
        while (--argc) {
            argv++;
            getInfo(*argv);
        }
    }
}

void doOption(int argc,char** argv){
    if (argc==1) {
        wrongError("lose command");
    }
    argc--;
    argv++;
    if (strcmp(*argv,"solve")==0) {
        command=1;
        doSolveOption(argc, argv);
    }else if(strcmp(*argv,"count")==0){
        command=2;
        doCountOption(argc,argv);
    }else if (strcmp(*argv,"gen")==0){
        command=3;
        doGenOption(argc,argv);
    }
    else{
        wrongError("command you type is wrong");
    }
}


int main(int argc,char** argv){
    doOption(argc,argv);
    if (command==1) {
        solveSu();
    }else if(command==2){
        countSu();
    }else
        genSu();
    return 1;
}

