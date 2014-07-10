//
//  arrival_thread.h
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2_arrival_thread_h
#define _02_warmup2_arrival_thread_h
#include "header.h"
#include "my402list.h"
#include "402_warmup2_time.h"
#define PACKET ((my_packet*)(elem->obj));
extern int token;
extern int can_move;
extern long int num_enter;
extern int packet_enter;
extern int lose_packet;
int leave_arrive_thread;
extern int time_to_quit;
extern FILE* file;
extern My402List* my_list_q1;
extern My402List* my_list_q2;
//extern My402List* my_list_q4;
extern pthread_mutex_t queue_1;
extern pthread_mutex_t queue_2;
extern pthread_mutex_t token_mutex;
extern pthread_cond_t read_queue_1;
extern pthread_cond_t read_queue_2;
extern struct reg_input my_reg_input;
pthread_mutex_t printf_mutex;
void* arrival_file();
void* arrival_reg();

#endif
