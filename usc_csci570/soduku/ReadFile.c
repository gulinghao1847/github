//
//  ReadFile.c
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

void checkList(My570List* list){
    unsigned long len=0;
    int line=0;
    My570ListElem* elem=My570ListFirst(list);
    len=strlen((char*)(elem->obj));
    for (;elem!=NULL;elem=My570ListNext(list,elem),line++) {
        line++;
        if (strlen((char*)(elem->obj))!=len) {
            fprintf(stderr,"File format is wrong\n");
            exit(1);
        }
    }
}

void readFile(char* fileName, My570List* list){
    FILE* file;
    char temp[1026];
    if ((file=fopen(fileName,"r"))==NULL) {
        fprintf(stderr,"can't open this file\n");
        exit(1);
    }
    while (fgets(temp,1026,file)!=NULL) {
        char* oneLine=(char*)malloc(LINELEN*sizeof(char));
        if (strlen(temp)>LINELEN) {
            fprintf(stderr,"file is not a legal file\n");
            exit(1);
        }
        strcpy(oneLine,temp);
        oneLine[strlen(oneLine)]='\0';
        My570ListAppend(list,oneLine);
    }
    checkList(list);
    fclose(file);
}

void readStdin(My570List* list){
    char temp[1026];
    while (fgets(temp,1026,stdin)) {
        char* oneLine=(char*)malloc(LINELEN*sizeof(char));
        strcpy(oneLine,temp);
        oneLine[strlen(oneLine)]='\0';
        My570ListAppend(list,oneLine);
    }
    checkList(list);
}

void staSudoku(My570List* list){
    //int len=My570ListLength(list);
    My570ListElem* elem;
    int count=0;
    int i=0;
    int j=0;
    char* obj;
        for (elem=My570ListFirst(list);elem!=NULL;) {
            count++;
            obj=(char*)(elem->obj);
            //printf("%s",obj);
            if (strcmp(obj,"+---+---+---+\n")==0||strcmp(obj,"+---+---+---+")==0) {
                //printf("here");
                My570ListElem* temp;
                temp=elem;
                elem=My570ListNext(list,elem);
                My570ListUnlink(list,temp);
            }else{
                j=0;
                //printf("org:%s",(char*)(obj));
                char* temp=(char*)malloc(20*sizeof(char));
                for (i=0;obj[i]!='\0';i++) {
                    if ((obj[i]>'0'&&obj[i]<='9')||obj[i]=='.') {
                        temp[j++]=obj[i];
                        if (i%4==0&&obj[0]=='|') {
                            fprintf(stderr,"format is wrong\n");
                            exit(1);
                        }
                    }else if(obj[i]=='|'||obj[i]=='\n'){
                    }
                    else {
                        fprintf(stderr,"format is wrong\n");
                        exit(1);
                    }
                }
                temp[j]='\0';
                elem->obj=temp;
                free(obj);
                //printf("exc:%s\n",(char*)(elem->obj));
                elem=My570ListNext(list,elem);
            }
        }
    if (My570ListLength(list)!=9) {
        fprintf(stderr,"format is wrong, the puzzle is not 9 lines please checke the file %d\n",My570ListLength(list));
        exit(1);
    }
}


void initArray(int** array, My570List* list){
    int i=0;
    My570ListElem* elem;
    char* oneLine;
    int count=0;
    for (i=0;i<9;i++) {
        array[i]=(int*)malloc(9*sizeof(int));
    }
    for(elem=My570ListFirst(list);elem!=NULL;elem=My570ListNext(list,elem),count++){
        oneLine=(char*)(elem->obj);
        //printf("%s   ~~~~",oneLine);
        for (i=0;oneLine[i]!='\0';i++) {
            if (oneLine[i]>'0'&&oneLine[i]<='9') {
                array[count][i]=oneLine[i]-'0';
            }else if(oneLine[i]=='.')
                array[count][i]=0;
            else
                fprintf(stderr,"impossible initArray\n");
        }
    }
}


unsigned long readBinFile(char* file_name,char* buffer){
    FILE* file;
    unsigned long ret=0;
    if ((file=fopen(file_name,"r"))==NULL) {
        fprintf(stderr,"can't open this file\n");
        exit(1);
    }
    ret=fread(buffer,4,400,file);
    fclose(file);
    return ret;
}

unsigned long readBinStdin(char* buffer){
    unsigned long ret=0;
    ret=fread(buffer,4,400,stdin);
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

int genOrgArray(intarray_t** initArray,int** resultArray,char* buffer){
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
    return position;
}










