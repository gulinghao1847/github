//
//  GenSu.c
//  hw5
//
//  Created by linghao on 12-11-28.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include "GenSu.h"
#include "SolveSu.h"
/*
unsigned long readBinFile(char* file_name,char* buffer){
    FILE* file;
    unsigned long ret=0;
    if ((file=fopen(file_name,"r"))==NULL) {
        fprintf(stderr,"can't open this file\n");
        exit(1);
    }
    ret=fread(buffer,4,300,file);
    fclose(file);
    return ret;
}

unsigned int getNext(char* buffer, int where){
    int position=0;
    int i=0;
    unsigned int amount;
    char* temp=(char*)malloc(8*sizeof(char));
    unsigned int nValue=0;
    position=where*4;
    for (;i<=3;i++) {
        sprintf(temp,"%02x",(unsigned char)buffer[position+i]);
        sscanf(temp,"%x",&nValue);
        amount=amount*256+nValue;
    }
    free(temp);
    return amount;
}

int deleteElem(intarray_t* intArray, int where){
    int ret=intArray->array[where];
    int count=where;
    for (;count<intArray->count;count++) {
        intArray->array[count]=intArray->array[count+1];
    }
    //free(&intArray->array[intArray->count--]);
    return ret;
}

void gen9Mul9Array(int** array){
    int i=0;
    for (i=0;i<9;i++) {
        array[i]=(int*)malloc(9*sizeof(int));
    }
}

void initGenInitArray(intarray_t** array){
    int i=0;
    int j=0;
    for (i=0;i<9;i++) {
        array[i]=(intarray_t*)malloc(sizeof(intarray_t));
        array[i]->array=(int*)malloc(9*sizeof(int));
        array[i]->count=9;
        
        for (j=0;j<9;j++) {
            array[i]->array[j]=j+1;
        }
    }
}

void genOrgArray(intarray_t** initArray,int** resultArray,char* buffer){
    int i=0;
    int j=0;
    int count=0;
    unsigned int where=0;
    int position=0;
    gen9Mul9Array(resultArray);
    for (i=0;i<9;i++) {
        count=9;
        for (j=0;j<9;j++) {
            where=getNext(buffer,position++);
            //printf("where:%u \n",where);
            resultArray[i][j]=deleteElem(initArray[i],where%count);
            count--;
        }
    }
}

*/




