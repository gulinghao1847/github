//
//  statistics.h
//  402_warmup2
//
//  Created by linghao on 12-10-5.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2_statistics_h
#define _02_warmup2_statistics_h
#include "header.h"
#include "my402list.h"
#include "402_warmup2_time.h"
#include <math.h>
extern My402List* my_list_q3;
extern My402List* my_list_q1;
extern My402List* my_list_q4;
extern struct timeval ini_time;
extern struct timeval end_time;
extern int token;
extern int token_amount;
extern int lose_packet;
extern long int num_enter;
extern int lose_token;
long int avg_packet_inter_arrival_time(My402List* my_list);
long int avg_service_time(My402List* my_list);
double avg_num_packet_in_Q1(My402List* my_list);
double avg_num_packet_in_Q2(My402List* my_list);
double avg_num_packet_in_S(My402List* my_list);
long int avg_time_spent_in_system(My402List* my_list);
void print_statistics(My402List* my_list);
long int count_token_drop();
void print_header();
long int count_packet_drop(My402List*);
char* print_statistics_time(long int count_interval_time,char* print_char);
char* print_avg_packets_and_drop_prob(long int org_data,char* data_char);
struct org_struct_input my_struct_input;
extern int msg_type;
char* file_name;
#endif
