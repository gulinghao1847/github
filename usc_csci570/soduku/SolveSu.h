//
//  SolveSu.h
//  hw5
//
//  Created by linghao on 12-11-27.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef hw5_SolveSu_h
#define hw5_SolveSu_h
#include "my570list.h"
#include "ReadFile.h"
typedef struct array{
    int array[9];
    int array_first_empty;
}array_t;

typedef struct OccNum{
    array_t row[9];
    array_t column[9];
    array_t region[9];
}Occ_t;

void initSuArray(int** puzzle, int** suArray);
void initOcc(int** suArray, Occ_t* occ);
int initEmptyArray(int** suArray, int** emptyArray);
int solveSudoku(int** suArray, int** emptyArray, int numEmp,Occ_t* occ);

int countSudoku(int** suArray, int** emptyArray, int numEmp,Occ_t* occ,My570List* list,int needStore);

int genOrgSu(int** suArray, int** emptyArray, int numEmp,Occ_t* occ,int** orgArray);
void initDeleteArray(int** suArray,intarray_t* deleteArray);
#endif
