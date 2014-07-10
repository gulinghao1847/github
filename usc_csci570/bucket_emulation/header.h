//
//  header.h
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2_header_h
#define _02_warmup2_header_h
#include <stdio.h>
#include <time.h>
#include <sys/time.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
typedef struct packet {
    char name[20];
    int where;
    struct timeval arrive_time;
    struct timeval enter_q1_time;
    struct timeval leave_q1_time;
    struct timeval enter_q2_time;
    struct timeval leave_q2_time;
    struct timeval enter_S_time;
    struct timeval leave_S_time;
    struct timeval response_time;
    long int inter_arrival;
    int token_need;
    long int org_inter_arrival;
    int mu;
    int have_served;
}my_packet;

struct reg_input{
    int token_need;
    int lambda;
    int mu;
    int token_interval_time;
    int token_max;
};

struct org_struct_input{
    char lambda[10];
    //char mu[5];
    char r[10];
    char mu[10];
    char file_name[256];
    //char r[10];
};
void clean_char_array(char* array);
void store_line_to_struct(char* one_line,my_packet* packet);
#endif
