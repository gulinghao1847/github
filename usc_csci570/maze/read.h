//
//  readBin.h
//  570hw4
//
//  Created by linghao on 12-11-4.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _70hw4_readBin_h
#define _70hw4_readBin_h
#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//read a binary file named file_name, and then use a buffer called buffer to store the information on it
unsigned long readFile(char*,char*);
//get the Next number need to be divided, the user must provide the last position
unsigned int getNext(char*, int,unsigned long);
//get the maze from a txt file;
char* readMazeFile(maze_t* myMaze,char* file_name);//
unsigned long readStdIn(char* buffer);
#endif

