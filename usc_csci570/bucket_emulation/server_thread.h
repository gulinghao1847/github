//
//  server_thread.h
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2_server_thread_h
#define _02_warmup2_server_thread_h
#include "header.h"
#include "my402list.h"
#include "402_warmup2_time.h"
extern pthread_cond_t read_queue_2;
extern pthread_mutex_t queue_2;
extern pthread_mutex_t printf_mutex;
extern pthread_mutex_t queue_3;
extern int time_to_quit;
extern long int num_enter;
extern int lose_packet;
int leave_server_thread;
struct timeval get_now_time;
char get_time_char[20];
char get_time_char_2[20];
char get_time_char_3[20];
extern My402List* my_list_q2;
extern My402List* my_list_q1;
extern My402List* my_list_q3;
extern struct reg_input my_reg_input;
void* server_thread();
extern int given_time;
#endif
