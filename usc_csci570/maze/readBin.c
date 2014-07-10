//
//  readBin.c
//  570hw4
//
//  Created by linghao on 12-11-4.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include "read.h"
#include <string.h>
//#include "global.h"
unsigned long readFile(char* file_name,char* buffer){
    FILE* file;
    unsigned long ret=0;
    if ((file=fopen(file_name,"r"))==NULL) {
        fprintf(stderr,"can't open this file\n");
        exit(1);
    }
    ret=fread(buffer,SIZE, NUMBER,file);
    fclose(file);
    return ret;
}

unsigned long readStdIn(char* buffer){
    //int num=0;
    //char temp[1026];
    //fgets(temp,1026,stdin);
    /*
    //printf("1here\n");
    strcpy(buffer,temp);
    while (fgets(temp,1026,stdin)!=NULL) {
        strcat(buffer,temp);
        num++;
        if (strlen(buffer)>=SIZE*NUMBER) {
            break;
        }
    }
     */
    unsigned long ret=0;
    if((ret=fread(buffer,SIZE, NUMBER,stdin))==0){
        fprintf(stderr,"error stdin is empty");
        exit(1);
    };
    return ret;
    //printf("2here\n%s \n",buffer);
}

unsigned int getNext(char* buffer, int where,unsigned long len){
    int position=0;
    int i=0;
    unsigned int amount;
    char* temp=(char*)malloc(8*sizeof(char));
    unsigned int nValue=0;
    position=where*4;
    for (;i<=3;i++) {
        
        if ((where+1)>len) {
            //printf("pos:%d,i:%d\n",position,i);
            fprintf(stderr,"can't generate a maze\n");
            exit(1);
        }
        
        sprintf(temp,"%02x",(unsigned char)buffer[position+i]);
        sscanf(temp,"%x",&nValue);
        amount=amount*256+nValue;
    }
    free(temp);
    return amount;
}

