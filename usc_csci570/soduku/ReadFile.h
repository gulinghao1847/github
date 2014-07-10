//
//  ReadFile.h
//  hw5
//
//  Created by linghao on 12-11-26.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef hw5_ReadFile_h
#define hw5_ReadFile_h
#define LINELEN 20

typedef struct intArray{
    int* array;
    int count;
}intarray_t;


void readFile(char* fileName, My570List* list);
void readStdin(My570List* list);
void staSudoku(My570List* list);
void initArray(int** array, My570List* list);


unsigned long readBinFile(char* file_name,char* buffer);
unsigned long readBinStdin(char* buffer);
unsigned int getNext(char* buffer, int where);
int deleteElem(intarray_t* intArray, int where);
void gen9Mul9Array(int** array);
void initGenInitArray(intarray_t** array);
int genOrgArray(intarray_t** initArray,int** resultArray,char* buffer);
int deleteElem(intarray_t* intArray, int where);

//print
void printSu(int**,int**);
#endif
