//
//  threads.c
//  402_warmup2
//
//  Created by linghao on 12-9-29.
//  Copyright (c) 2012年 linghao. All rights reserved.
//


#include "arrival_thread.h"


// decide when to stop this function: exit after the num_number packet has been sent to the Q2
void* arrival_file(){
    int given_time=0;
    //printf("here\n");
    long int count_time=0;      //to count the current time
    long int i=0;
    //long int lambda=0;
    char* temp=(char*)malloc(sizeof(char));
    char* temp_ms_time_char=(char*)malloc(20*sizeof(char));   //store the show_ms_time return value
    char* temp_ms_time_char_2=(char*)malloc(20*sizeof(char));   //store the show_ms_time return value
    struct timeval now_time,temp_time,temp_use_time;//temp_time is to store the time that q1 arrives temp_use_time is the time that store the current time
    //FILE* file=(FILE*)file_1;
    temp_time=ini_time;
    long int temp_num_enter;
    if (num_enter>500) {
        temp_num_enter=500;
    }
    else
        temp_num_enter=num_enter;
    
    my_packet* queue=(my_packet*)malloc(temp_num_enter*sizeof(my_packet));   // contruct num_enter object of the struct my_packet.
    
    //printf("here1\n");
    
    clean_char_array(temp_ms_time_char);
    fgets(temp_ms_time_char,1024,file);
    //printf("%s\n",temp_ms_time_char);
    
     //printf("here3%s\n",temp_ms_time_char);
    store_line_to_struct(temp_ms_time_char,&queue[i]);
    queue[i].inter_arrival=my_reg_input.token_interval_time;
    clean_char_array(temp_ms_time_char);
    //printf("%ld find the option\n",queue[i].org_inter_arrival);
    
    
//    //read the fisrt line; set lambda, mu, token_need
    
    while (time_to_quit) {
        gettimeofday(&now_time,NULL);
        count_time=interval_time(&temp_time,&now_time);
        if (count_time>queue[i].org_inter_arrival*1000&&(i<num_enter)) {
            
            //enter informotion
            queue[i].inter_arrival=count_time;
            gettimeofday(&temp_time,NULL);
            queue[i].arrive_time=temp_time;
            //enter informotion
            
            //print the information on the console
            pthread_mutex_lock(&printf_mutex);
            printf("%sp%ld enters Q1\n",show_ms_time(&temp_time,temp_ms_time_char),i+1);
            pthread_mutex_unlock(&printf_mutex);
            //print the information on the console
            
            
            //code below is to input information into queue
            pthread_mutex_lock(&queue_1);
            strcpy(queue[i].name,"p");
            long int temp_int=i+1;
            sprintf(temp,"%ld",temp_int);
            strcat(queue[i].name,temp);
            //queue[i].mu=my_reg_input.mu;
            //queue[i].token_need=my_reg_input.token_need;
            //queue[i].inter_arrival=my_reg_input.token_interval_time;
            My402ListAppend(my_list_q1,&queue[i]);                // append this struct into the my_queue_q1
            gettimeofday(&temp_use_time,NULL);
            queue[i].enter_q1_time=temp_use_time;                  //enter  enter_q1_time
            pthread_mutex_lock(&printf_mutex);
            //code above is to enter information into queue
            
            
            printf("%s%s arrives, needs %d tokens, inter-arrival time = %s\n",show_ms_time(&temp_use_time,temp_ms_time_char),queue[i].name,queue[i].token_need,print_interval_time(count_time,temp_ms_time_char_2));
            pthread_mutex_unlock(&printf_mutex);
            pthread_mutex_unlock(&queue_1);
            
            i=i+1;     // in order to get the next queue
            
            if(i<num_enter){
            clean_char_array(temp_ms_time_char);
            fgets(temp_ms_time_char,1024,file);
            store_line_to_struct(temp_ms_time_char,&queue[i]);
            queue[i].inter_arrival=my_reg_input.token_interval_time;
            clean_char_array(temp_ms_time_char);
            }
        }

        
        
        if(can_move==1&&(My402ListLength(my_list_q1)!=0)){
            given_time++;
            My402ListElem* elem;
            //change the global var can_move and token
            pthread_mutex_lock(&token_mutex);
            token=token-((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need;
            can_move=0;
            pthread_mutex_unlock(&token_mutex);
            //change the global var can_move and token
            
            //unlink the first element in queue_1
            pthread_mutex_lock(&queue_1);
            elem=My402ListFirst(my_list_q1);
            My402ListUnlink(my_list_q1,elem);
            gettimeofday(&temp_use_time,NULL);
            ((my_packet*)(elem->obj))->leave_q1_time=temp_use_time;  //record the leave time
            //printf("the length of my_list_q1 is %d\n", My402ListLength(my_list_q1));
            pthread_mutex_unlock(&queue_1);
            //unlink the first element in queue_1
            
            //print the information that we will append this elem into queue_2
            pthread_mutex_lock(&token_mutex);
            pthread_mutex_lock(&printf_mutex);
            printf("%s%s leaves Q1, time in Q1 = %s  token bucket now has %d token\n",show_ms_time(&((my_packet*)(elem->obj))->leave_q1_time,temp_ms_time_char),((my_packet*)(elem->obj))->name,print_interval_time(count_interval_time(&((my_packet*)(elem->obj))->enter_q1_time, &((my_packet*)(elem->obj))->leave_q1_time),temp_ms_time_char_2),token);
            pthread_mutex_unlock(&printf_mutex);
            pthread_mutex_unlock(&token_mutex);
            //print the information that we will append this elem into queue_2
            
            //enter some information into this elem and append this elem
            pthread_mutex_lock(&queue_2);
            My402ListAppend(my_list_q2,(elem->obj));
            gettimeofday(&temp_use_time,NULL);
            ((my_packet*)(elem->obj))->enter_q2_time=temp_use_time;
            //enter some information into this elem and append this elem
            
            
            //signal the service that my_list_q2 is not empty
            if (My402ListLength(my_list_q2)!=0) {
                pthread_cond_signal(&read_queue_2);
            }
            //printf("the length of my_list_q2 is %d\n", My402ListLength(my_list_q2));
            pthread_mutex_unlock(&queue_2);
            //signal the service that my_list_q2 is not empty
            
            //print some information on the console
            pthread_mutex_lock(&printf_mutex);
            printf("%s%s enters Q2\n",show_ms_time(&((my_packet*)(elem->obj))->enter_q2_time,temp_ms_time_char),((my_packet*)(elem->obj))->name);
            pthread_mutex_unlock(&printf_mutex);
        }
        if (given_time==num_enter-lose_packet) {
            leave_arrive_thread=1;
            //printf("arrival\n");
            pthread_exit((void*)1);
            
        }
        if (lose_packet==num_enter) {
            leave_arrive_thread=1;
            pthread_exit((void*)1);
            
        }
        //printf("arrival1");
        if (i>=num_enter) {
            usleep(my_reg_input.token_interval_time*1000/10);
        }
        else{
        usleep(queue[i].org_inter_arrival*1000/10);
        }
    }
    //printf("arrival2");
    return 0;
}




// decide when to stop this function: exit after the num_number packet has been sent to the Q2
//set a global struct to decide how to run
void* arrival_reg(){
    int given_time=0;
    long int count_time=0;      //to count the current time
    int i=0;
    //long int lambda=0;
    char* temp=(char*)malloc(sizeof(char));
    char* temp_ms_time_char=(char*)malloc(20*sizeof(char));   //store the show_ms_time return value
    char* temp_ms_time_char_2=(char*)malloc(20*sizeof(char));   //store the show_ms_time return value
    struct timeval now_time,temp_time,temp_use_time;//temp_time is to store the time that q1 arrives temp_use_time is the time that store the current time
    temp_time=ini_time;
    
    
    while (time_to_quit) {
        gettimeofday(&now_time,NULL);
        count_time=interval_time(&temp_time,&now_time);
        if ((count_time>my_reg_input.lambda*1000)&&i<num_enter) {
            
            //enter informotion
            //queue_interval_time[i].inter_arrival=count_time;
            my_packet* queue=(my_packet*)malloc(sizeof(my_packet));
            queue->inter_arrival=count_time;
            //queue_interval_time[i].inter_arrival=count_time;
            //My402ListAppend(my_list_q4,&queue_interval_time[i]);
            gettimeofday(&temp_time,NULL);
            queue->arrive_time=temp_time;
            //enter informotion
            
            //print the information on the console
            pthread_mutex_lock(&printf_mutex);
            printf("%sp%d enters Q1\n",show_ms_time(&temp_time,temp_ms_time_char),+1);
            pthread_mutex_unlock(&printf_mutex);
            //print the information on the console
            
            
            //code below is to input information into queue
            pthread_mutex_lock(&queue_1);
            strcpy(queue->name,"p");
            int temp_int=i+1;
            sprintf(temp,"%d",temp_int);
            strcat(queue->name,temp);
            queue->mu=my_reg_input.mu;
            queue->token_need=my_reg_input.token_need;
            queue->inter_arrival=count_time;
            My402ListAppend(my_list_q1,queue);                // append this struct into the my_queue_q1
            gettimeofday(&temp_use_time,NULL);
            queue->enter_q1_time=temp_use_time;                  //enter  enter_q1_time
            pthread_mutex_lock(&printf_mutex);
            //code above is to enter information into queue
            
            
            printf("%s%s arrives, needs 3 tokens, inter-arrival time = %s\n",show_ms_time(&temp_use_time,temp_ms_time_char),queue->name,print_interval_time(count_time,temp_ms_time_char_2));
            pthread_mutex_unlock(&printf_mutex);
            pthread_mutex_unlock(&queue_1);
            
            i=i+1;     // in order to get the next queue
            //printf("finish generate a packet\n");
            
        }
        
        
        if(can_move==1&&(My402ListLength(my_list_q1)!=0)){
            given_time++;
            //printf("i want to move\n");
            My402ListElem* elem;
            //change the global var can_move and token
            pthread_mutex_lock(&token_mutex);
            token=token-((my_packet*)(My402ListFirst(my_list_q1)->obj))->token_need;
            can_move=0;
            pthread_mutex_unlock(&token_mutex);
            //change the global var can_move and token
            
            //unlink the first element in queue_1
            pthread_mutex_lock(&queue_1);
            elem=My402ListFirst(my_list_q1);
            My402ListUnlink(my_list_q1,elem);
            gettimeofday(&temp_use_time,NULL);
            ((my_packet*)(elem->obj))->leave_q1_time=temp_use_time;  //record the leave time
            //printf("the length of my_list_q1 is %d\n", My402ListLength(my_list_q1));
            pthread_mutex_unlock(&queue_1);
            //unlink the first element in queue_1
            
            //print the information that we will append this elem into queue_2
            pthread_mutex_lock(&token_mutex);
            pthread_mutex_lock(&printf_mutex);
            printf("%s%s leaves Q1, time in Q1 = %s, token bucket now has %d token\n",show_ms_time(&((my_packet*)(elem->obj))->leave_q1_time,temp_ms_time_char),((my_packet*)(elem->obj))->name,print_interval_time(count_interval_time(&((my_packet*)(elem->obj))->enter_q1_time, &((my_packet*)(elem->obj))->leave_q1_time),temp_ms_time_char_2),token);
            pthread_mutex_unlock(&printf_mutex);
            pthread_mutex_unlock(&token_mutex);
            //print the information that we will append this elem into queue_2
            
            //enter some information into this elem and append this elem
            pthread_mutex_lock(&queue_2);
            My402ListAppend(my_list_q2,(elem->obj));
            gettimeofday(&temp_use_time,NULL);
            ((my_packet*)(elem->obj))->enter_q2_time=temp_use_time;
            //enter some information into this elem and append this elem
            
            
            //signal the service that my_list_q2 is not empty
            if (My402ListLength(my_list_q2)!=0) {
                pthread_cond_signal(&read_queue_2);
            }
            //printf("the length of my_list_q2 is %d\n", My402ListLength(my_list_q2));
            pthread_mutex_unlock(&queue_2);
            //signal the service that my_list_q2 is not empty
            
            //print some information on the console
            pthread_mutex_lock(&printf_mutex);
            printf("%s%s enters Q2\n",show_ms_time(&((my_packet*)(elem->obj))->enter_q2_time,temp_ms_time_char),((my_packet*)(elem->obj))->name);
            pthread_mutex_unlock(&printf_mutex);
            //print some information on the console
            
        }
        if (given_time==num_enter) {
            leave_arrive_thread=1;
            //printf("arrival\n");
            pthread_exit((void*)1);
            
        }
        if (lose_packet==num_enter) {
            leave_arrive_thread=1;
            pthread_exit((void*)1);
            
        }
        //printf("1\n");
        //printf("%d,",my_reg_input.lambda*1000/10);
        usleep(my_reg_input.lambda*1000/10);
    }
    return 0;
}


