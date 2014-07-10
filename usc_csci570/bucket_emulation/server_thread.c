//
//  server_thread.c
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//
#include "server_thread.h"
void* server_thread(){
    //int given_time=0;
    int old_type_signal;
    //printf("server\n");
    while (time_to_quit) {
        
        //pthread_cond_wait the queue_2 to have at least one elem
        pthread_mutex_lock(&queue_2);
        while (My402ListLength(my_list_q2)==0) {
             pthread_cond_wait(&read_queue_2,&queue_2);
        }
        pthread_mutex_unlock(&queue_2);
        
        
        //unlink the first elem in queue2 and enter some information into this my_packet type object
        //disable the SIGINT
        
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,&old_type_signal);
        pthread_mutex_lock(&queue_2);
        My402ListElem* elem;
        elem=My402ListFirst(my_list_q2);
        gettimeofday(&get_now_time,NULL);
        ((my_packet*)(elem->obj))->leave_q2_time=get_now_time;
        ((my_packet*)(elem->obj))->have_served=1;
        My402ListUnlink(my_list_q2,elem);
        pthread_mutex_unlock(&queue_2);
        //unlink the first elem in queue2 and enter some information into this my_packet type object
        
        
        //append this elem into my_list_q3 for contacting this elem later
        pthread_mutex_lock(&queue_3);
        My402ListAppend(my_list_q3,(my_packet*)(elem->obj));
         pthread_mutex_unlock(&queue_3);
        
        //enter some information into this my_packet type object
        gettimeofday(&get_now_time,NULL);
        ((my_packet*)(elem->obj))->enter_S_time=get_now_time;
        
        pthread_mutex_lock(&printf_mutex);
        printf("%s%s begin service at S time in Q2 = %s\n",show_ms_time(&get_now_time,get_time_char),((my_packet*)(elem->obj))->name,print_interval_time(count_interval_time(&(((my_packet*)(elem->obj))->enter_q2_time),&(((my_packet*)(elem->obj))->leave_q2_time)),get_time_char_2));
        pthread_mutex_unlock(&printf_mutex);
        
        usleep(((my_packet*)(elem->obj))->mu);
        
        gettimeofday(&get_now_time,NULL);
        ((my_packet*)(elem->obj))->leave_S_time=get_now_time;
        
        
        gettimeofday(&get_now_time,NULL);
        ((my_packet*)(elem->obj))->response_time=get_now_time;
        //enter some information into this my_packet type object
        
        //print some information on the console
        pthread_mutex_lock(&printf_mutex);
        printf("%s%s departs from S service = %s,\n                time in system = %s\n",show_ms_time(&get_now_time,get_time_char),((my_packet*)(elem->obj))->name,print_interval_time(count_interval_time(&(((my_packet*)(elem->obj))->enter_S_time),&(((my_packet*)(elem->obj))->leave_S_time)),get_time_char_3),print_interval_time(count_interval_time(&(((my_packet*)(elem->obj))->arrive_time),&(((my_packet*)(elem->obj))->response_time)),get_time_char_2));
        pthread_mutex_unlock(&printf_mutex);
        //print some information on the console
        
        given_time++;
        
        
        pthread_setcancelstate(old_type_signal,0);

        
        //usleep(my_reg_input.token_interval_time*1000/10);   //sleep for some time in order to avoid busy-waiting
     }
    return 0;
}
