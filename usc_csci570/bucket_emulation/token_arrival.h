//
//  token_arrival.h
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2_token_arrival_h
#define _02_warmup2_token_arrival_h
#include "header.h"
#include "402_warmup2_time.h"
#include "my402list.h"
extern int token;
extern long int num_enter;
extern int token_amount;
extern int lose_packet;
int leave_token_thread;
extern int time_to_quit;
struct timeval temp_time_use;
extern struct timeval ini_time;
extern pthread_mutex_t token_mutex;
extern pthread_mutex_t queue_3;
extern pthread_t server_pthread;
//extern pthread_cond_t read_queue_1;
extern pthread_mutex_t printf_mutex;
extern pthread_mutex_t queue_1;
extern My402List* my_list_q3;
extern int can_move;
extern int lose_token;
extern My402List* my_list_q1;
extern My402List* my_list_q2;
void* token_arrival();
extern struct reg_input my_reg_input;
extern int given_time;
#endif
