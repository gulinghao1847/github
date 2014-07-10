//
//  arrival_token.c
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//
//in this .c file, we need to know inter_arrival time for this function to generate tokens, and every packet has the same time, so we put this var in the struct my_reg_input in the main.c file
//we also need to know the maximum number of token can be generated
#include <stdio.h>
#include "token_arrival.h"
void* token_arrival(int mu){
    //printf("token\n");
    //int token_amount=0;    // the total number of token
    char show_printf[40];
    int given_token=0;
    //printf("1\n");
    struct timeval temp_time, new_time, old_time;
    temp_time=ini_time;
    
    while (time_to_quit) {
        //printf("t");
        gettimeofday(&new_time,NULL);
        old_time=temp_time;
        
        
        //in order to see if the time equal to or larger than my_reg_input.token_interval_time
        if (interval_time(&old_time,&new_time)>my_reg_input.token_interval_time*1000) {
            gettimeofday(&temp_time,NULL);
          
            pthread_mutex_lock(&token_mutex);
            token_amount++;
            //generate token
            if (token<my_reg_input.token_max) {
                token++;
                //token_amount++;
                pthread_mutex_lock(&printf_mutex);
                printf("%stoken t%d arrives, token bucket now has %d token\n",show_ms_time(&temp_time,show_printf),token_amount, token);
                pthread_mutex_unlock(&printf_mutex);
                clean_char_array(show_printf);
                //continue;
                //printf("finish generate a token\n");
             }
            //pthread_mutex_unlock(&token_mutex);
            
            //if the token number equal to the token_max, do the following
            else{/*(token>=my_reg_input.token_max)*/
                lose_token++;
                pthread_mutex_lock(&printf_mutex);
                gettimeofday(&temp_time_use,NULL);
                printf("%stoken t%d arrives, dropped\n",show_ms_time(&temp_time_use,show_printf),token_amount);
                pthread_mutex_unlock(&printf_mutex);
                clean_char_array(show_printf);
            }
            //if the token number equal to the token_max, do the following
            pthread_mutex_unlock(&token_mutex);
            
        }
        
        
        //signal the arrival_thread that there are enough tokens for the first elem in queue_1 to go to Q2
        pthread_mutex_lock(&token_mutex);
        if (My402ListLength(my_list_q1)!=0) {
            if(/*token>=((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need&&*/can_move==0){
                My402ListElem* temp_elem;
                //pthread_mutex_lock()
                pthread_mutex_lock(&queue_1);
                while((My402ListLength(my_list_q1)>0)&&((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need>my_reg_input.token_max) {
                    //printf("get one\n");
                    //unlink and enqueue it to queue 3;
                    lose_packet++;
                    gettimeofday(&temp_time_use,NULL);
                    clean_char_array(show_printf);
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->leave_q1_time=temp_time_use;
                    
                    pthread_mutex_lock(&printf_mutex);
                    printf("%spacket %s arrives, needs %d tokens, dropped\n",show_ms_time(&temp_time_use,show_printf),((my_packet*)(My402ListFirst(my_list_q1)->obj))->name, ((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need);
                    temp_elem=My402ListFirst(my_list_q1);
                    gettimeofday(&temp_time_use,NULL);
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->response_time=temp_time_use;
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->enter_q2_time=temp_time_use;
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->enter_S_time=temp_time_use;
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->leave_S_time=temp_time_use;
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->leave_q2_time=temp_time_use;
                    ((my_packet*)(My402ListFirst(my_list_q1)->obj))->have_served=0;
                    My402ListUnlink(my_list_q1,temp_elem);
                    pthread_mutex_unlock(&printf_mutex);
                    //printf("ok\n");
                    clean_char_array(show_printf);
                    
                    pthread_mutex_lock(&queue_3);
                    My402ListAppend(my_list_q3,(my_packet*)(temp_elem->obj));
                    pthread_mutex_unlock(&queue_3);
                    //printf("ok\n");
                }
                pthread_mutex_unlock(&queue_1);
                //printf("ok\n");
                if(My402ListLength(my_list_q1)>0&&token>=((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need){
                    can_move=1;
                    given_token++;
                    //printf("%d\n",given_token);
                    //printf("%d\n",num_enter);
                    //printf("hello,3 token move\n");
                }
            }
            //printf("ok\n");
        }
        pthread_mutex_unlock(&token_mutex);
        //signal the arrival_thread that there are enough tokens for the first elem in queue_1 to go to Q2
        
        if (given_time==num_enter-lose_packet) {
            leave_token_thread=1;
            pthread_cancel(server_pthread);
            //printf("nun_enter:%ld lose_packet:%d\n",num_enter,lose_packet);
            //printf("token\n");
            pthread_exit((void*)1);
        }
        //printf("1\n");
        //printf("token\n");
        usleep(my_reg_input.token_interval_time*1000/10);    // avoid busy waiting
        //printf("here in token\n");
        }
    return 0;
}

