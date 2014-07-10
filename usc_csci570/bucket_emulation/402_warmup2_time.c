//
//  402_warmup2_time.c
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include "402_warmup2_time.h"
#include "header.h"
long int interval_time(struct timeval* old_time, struct timeval*new_time){
    long int time_1;
    long int time_2;
    time_1=new_time->tv_sec-old_time->tv_sec;
    time_2=new_time->tv_usec-old_time->tv_usec;
    time_2=time_2+time_1*1000000;
    return time_2;
}

char* show_ms_time(struct timeval* now_time,char* ms_time_1){
    //printf("problem here?\n");
    long int time_1;
    long int time_2;
    int i=0;
    //char ms_time_1[20];
    char ms_time_2[10];
    char temp_ms_time[10];
    
    for (i=0;i<10;i++) {
        temp_ms_time[i]='\0';
    }
    
    time_1=now_time->tv_sec-ini_time.tv_sec;
    time_2=now_time->tv_usec-ini_time.tv_usec;
    
    if (time_2<0) {
        time_1=time_1-1;
        time_2=time_2+1000000;
    }
    sprintf(ms_time_1,"%ld",time_1);
    //printf("%s\n",temp_ms_time);
    //printf("%s\n",ms_time_1);
    //printf("%zd\n",strlen(temp_ms_time));
    for(i=0;i<5-strlen(ms_time_1);i++){
        strcat(temp_ms_time,"0");
    }
    //printf("");
    strcat(temp_ms_time,ms_time_1);
    strcpy(ms_time_1,temp_ms_time);
    
    //printf("%s\n",ms_time_1);
    for (i=0;i<10;i++) {
        temp_ms_time[i]='\0';
    }
    
    sprintf(ms_time_2,"%ld",time_2);
    //printf("length 2:%d\n",strlen(ms_time_2));
    if(strlen(ms_time_2)>=3){
        int j=0;
        for (i=0;i<6-strlen(ms_time_2);i++) {
             strcat(temp_ms_time,"0");
        }
        for (i=i;i<3;i++) {
             temp_ms_time[i]=ms_time_2[j];
             j++;
        }
        temp_ms_time[i]='.';
        for (i=i+1; i<7;i++ ) {
             temp_ms_time[i]=ms_time_2[j];
            j++;
        }
        strcat(ms_time_1,temp_ms_time);
     }
    else{
        for (i=0;i<3;i++) {
            strcat(temp_ms_time,"0");
        }
        temp_ms_time[i]='.';
        for (i=i+1;i<7-strlen(ms_time_2);i++) {
            strcat(temp_ms_time,"0");
        }
        int j=0;
        for (i=i; i<7;i++ ) {
            temp_ms_time[i]=ms_time_2[j];
            j++;
        }
        strcat(ms_time_1,temp_ms_time);
    }
    strcat(ms_time_1,"ms: ");
    return ms_time_1;
}


long int count_interval_time(struct timeval* old_time, struct timeval* new_time){
    long int time_1;
    long int time_2;
    time_1=new_time->tv_sec-old_time->tv_sec;
    time_2=new_time->tv_usec-old_time->tv_usec;
    time_2=time_2+time_1*1000000;
    return time_2;
}

char* print_interval_time(long int count_interval_time,char* print_char){
    clean_char_array(print_char);
    char temp_char[30];
    int i=0;
    for (i=0;i<strlen(print_char);i++) {
        print_char[i]='\0';
    }
    sprintf(temp_char,"%ld",count_interval_time);
    if (strlen(temp_char)>3) {
        for (i=0;i<strlen(temp_char)-3;i++) {
            print_char[i]=temp_char[i];
        }
        print_char[i]='.';
        for (i=i+1;i<strlen(temp_char)+1;i++) {
            print_char[i]=temp_char[i-1];
        }
    }
    else{
        print_char[0]='0';
        print_char[1]='.';
        for (i=2;i<5-strlen(temp_char); i++) {
            print_char[i]='0';
        }
        for (i=i;i<5;i++) {
            int j=0;
            print_char[i]=temp_char[j];
        }
    }
    strcat(print_char,"ms");
    return print_char;
    //memmove(print_char,temp_char,strlen(temp_char)-4);
}

unsigned int decide_sleep_time(my_packet* packet){
    unsigned int new_time=0;
    unsigned long int which_to_choose=my_reg_input.lambda;
    if (msg_type==1) {
       if (my_reg_input.mu<which_to_choose) {
           which_to_choose=my_reg_input.mu;
       }
    if (my_reg_input.token_interval_time<which_to_choose) {
           which_to_choose=my_reg_input.token_interval_time;
       }
    new_time=which_to_choose*1000/50;
    }
    else{
        which_to_choose=packet->org_inter_arrival;
        if (which_to_choose<packet->mu) {
            which_to_choose=packet->mu;
        }
        if (which_to_choose<my_reg_input.token_interval_time) {
            which_to_choose=my_reg_input.token_interval_time;
        }
        new_time=(unsigned)which_to_choose;
    }
    return new_time;

}


