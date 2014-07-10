//
//  statistics.c
//  402_warmup2
//
//  Created by linghao on 12-10-5.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include "statistics.h"

long int avg_packet_inter_arrival_time(My402List* my_list){
    My402ListElem* elem;
    long int sum_arrival_time=0;
    int n=0;
    if (My402ListLength(my_list)!=0||My402ListLength(my_list_q1)!=0) {
        if (My402ListLength(my_list)!=0){
            for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
                 n=n+1;
                 sum_arrival_time=sum_arrival_time+((my_packet*)(elem->obj))->inter_arrival;
             }
        }
        if (My402ListLength(my_list_q1)==0) {
             return sum_arrival_time/n;
        }
        else{
           for (elem=My402ListFirst(my_list_q1); elem!=NULL;elem=My402ListNext(my_list_q1,elem)) {
                n=n+1;
                sum_arrival_time=sum_arrival_time+((my_packet*)(elem->obj))->inter_arrival;
           }
        }
    //printf("%ld in the function avg_packet_inter_arrival_time\n",sum_arrival_time/n);
    //printf("%d\n",n);
    }
    else
    {
        return 0;
    }
    //printf("%ld\n",sum_arrival_time);
    return sum_arrival_time/n;
}


long int avg_service_time(My402List* my_list){
    My402ListElem* elem;
    long int sum_service_time=0;
    int n=0;
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    //printf("ok\n");
    for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
        n=n+1;
        //printf("ok\n");
        sum_service_time=sum_service_time+count_interval_time(&((my_packet*)(elem->obj))->enter_S_time,&((my_packet*)(elem->obj))->leave_S_time);
    }
    //printf("ok1\n");
    //printf("%ld in the function avg_packet_inter_arrival_time\n",sum_service_time/n);
    if ((n-lose_packet)==0) {
        return 0;
    }
    return sum_service_time/(n-lose_packet);
}

double avg_num_packet_in_Q1(My402List* my_list){
    My402ListElem* elem;
    double sum_time_used_in_Q1=0;
    double sum_time_packet_in_Q1=0;
    sum_time_used_in_Q1=count_interval_time(&ini_time,&end_time);
    if (My402ListLength(my_list)==0) {
        return 0;
    }
        for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
            sum_time_packet_in_Q1=sum_time_packet_in_Q1+count_interval_time(&((my_packet*)(elem->obj))->enter_q1_time, &((my_packet*)(elem->obj))->leave_q1_time);
        }
    //printf("%ld  %ldin the function avg_packet_inter_arrival_time\n",sum_time_packet_in_Q1,sum_time_used_in_Q1);
    return sum_time_packet_in_Q1/sum_time_used_in_Q1;
}

double avg_num_packet_in_Q2(My402List* my_list){
    My402ListElem* elem;
    double sum_time_used_in_Q2=0;
    double sum_time_packet_in_Q2=0;
    sum_time_used_in_Q2=count_interval_time(&ini_time,&end_time);
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
        sum_time_packet_in_Q2=sum_time_packet_in_Q2+count_interval_time(&((my_packet*)(elem->obj))->enter_q2_time, &((my_packet*)(elem->obj))->leave_q2_time);
    }
        //printf("%ld  %ldin the function avg_packet_inter_arrival_time\n",sum_time_packet_in_Q2,sum_time_used_in_Q2);
    return sum_time_packet_in_Q2/sum_time_used_in_Q2;
}

double avg_num_packet_in_S(My402List* my_list){
    My402ListElem* elem;
    double sum_time_used_in_S=0;
    double sum_time_packet_in_S=0;
    sum_time_used_in_S=count_interval_time(&ini_time,&end_time);
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
        sum_time_packet_in_S=sum_time_packet_in_S+count_interval_time(&((my_packet*)(elem->obj))->enter_S_time, &((my_packet*)(elem->obj))->leave_S_time);
    }
        //printf("%ld  %ldin the function avg_packet_inter_arrival_time\n",sum_time_packet_in_S,sum_time_used_in_S);
    return sum_time_packet_in_S/sum_time_used_in_S;
}

long int avg_time_spent_in_system(My402List* my_list){
    My402ListElem* elem;
    double n=0;
    double sum_time_packet_in_system=0;
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
        if(((my_packet*)(elem->obj))->have_served==1){
        n=n+1;
        sum_time_packet_in_system=sum_time_packet_in_system+count_interval_time(&((my_packet*)(elem->obj))->arrive_time, &((my_packet*)(elem->obj))->response_time);
        }
        else
            continue;
    }
    if (n==0) {
        return 0;
    }
        //printf("%ldin the function avg_packet_inter_arrival_time\n",sum_time_packet_in_system/n);
    return sum_time_packet_in_system/n;
}

double standard_deviation(My402List* my_list){
    long int avg_time=0;
    My402ListElem* elem;
    double sum=0;
    int n=0;
    double value_return;
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    avg_time=avg_time_spent_in_system(my_list);
    for (elem=My402ListFirst(my_list); elem!=NULL;elem=My402ListNext(my_list,elem)) {
        if(((my_packet*)(elem->obj))->have_served==1){
            n=n+1;
        sum=sum+powl((count_interval_time(&((my_packet*)(elem->obj))->arrive_time,&((my_packet*)(elem->obj))->response_time)-avg_time)/1000000,2);
        }
        else
            continue;
    }
    //printf("%d\n",n);
    
    if (n==0) {
        return 0;
    }
    value_return=sqrtl(sum/n);
    //printf("%f\n",value_return);
    return value_return;
}


long int count_token_drop(){
    long int token_amount_1=token_amount;
    long int lose_token_1=lose_token;
    //printf("%ld\n",token_amount_1);
    //printf("%ld\n",lose_token_1);
    //printf("%ld\n",(lose_token_1*10000000)/token_amount_1);
    if (token_amount_1==0) {
        return 0;
    }
    return (lose_token_1*1000000)/token_amount_1;
}

long int count_packet_drop(My402List* my_list){
    if (My402ListLength(my_list)==0) {
        return 0;
    }
    return lose_packet*1000000/My402ListLength(my_list);
}

char* print_statistics_time(long int count_interval_time,char* print_char){
    clean_char_array(print_char);
    //printf("%ld\n",count_interval_time);
    char temp_char[30];
    int i=0;
    int j=0;
    //printf("ok here\n");
    sprintf(temp_char,"%ld",count_interval_time);
    //printf("%s\n",temp_char);
    if (strlen(temp_char)>6) {
        for (i=0;i<strlen(temp_char)-6;i++) {
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
        for (i=2;i<8-strlen(temp_char); i++) {
            print_char[i]='0';
        }
        j=0;
        for (i=i;i<8;i++,j++) {
            print_char[i]=temp_char[j];
        }
    }
    strcat(print_char,"s");
    return print_char;
    //memmove(print_char,temp_char,strlen(temp_char)-4);
}


//here we don't want to use float and double, so we use int*100000 in order to keep 5 digits after'.'   


char* print_avg_packets_and_drop_prob(long int org_data,char* data_char){
    clean_char_array(data_char);
    char temp_char[30];
    int i=0;
    int j=0;
    sprintf(temp_char,"%ld",org_data);
    //printf("%s\n",temp_char);
    if (strlen(temp_char)>6) {
        for (;j<strlen(temp_char)-6;i++,j++) {
            data_char[i]=temp_char[j];
        }
        data_char[i]='.';
        
        for (i=i+1;j<strlen(temp_char);i++,j++) {
            data_char[i]=temp_char[j];
        }
    }
    else{
        data_char[0]='0';
        data_char[1]='.';
        for (i=2;i<8-strlen(temp_char);i++) {
            data_char[i]='0';
        }
        for (j=0;j<strlen(temp_char);i++,j++) {
            data_char[i]=temp_char[j];
        }
    }
    return data_char;
}

void print_header(){
    printf("Emulation Parameters: \n");
    if (msg_type==1) {
        printf("     lambda=%s\n",my_struct_input.lambda);
        printf("     mu=%s\n",my_struct_input.mu);
        printf("     P=%d\n",my_reg_input.token_need);
        printf("     number to arrive=%ld\n",num_enter);
    }
    printf("     r=%s\n",my_struct_input.r);
    printf("     B=%d\n",my_reg_input.token_max);
    if (msg_type==2) {
        printf("     tsfile=%s\n",file_name);
    }

}
void print_statistics(My402List* my_list){
    char* temp_use_char=(char*)malloc(30*sizeof(char));
    printf("\nStatistics: \n");
    printf("average packet inter-arrival time = %s\n",print_statistics_time(avg_packet_inter_arrival_time(my_list),temp_use_char));
    printf("average packet service time = %s\n",print_statistics_time(avg_service_time(my_list),temp_use_char));
    //long int avg_packet_inter_arrival_time(My402List* my_list);
    //long int avg_service_time(My402List* my_list);
    printf("average number of packets in Q1 =  %.6g packets\n",avg_num_packet_in_Q1(my_list));
    //long int avg_num_packet_in_Q1(My402List* my_list);
    printf("average number of packets in Q2 =  %.6g packets\n",avg_num_packet_in_Q2(my_list));
    //long int avg_num_packet_in_Q2(My402List* my_list);
    printf("average number of packets in S =  %.6g packets\n",avg_num_packet_in_S(my_list));
    //long int avg_num_packet_in_S(My402List* my_list);
    printf("average time a packet spent in system = %s\n",print_statistics_time(avg_time_spent_in_system(my_list),temp_use_char));
    //long int avg_time_spent_in_system(My402List* my_list);
    printf("standard deviation for time spent in system = %.6gs\n",standard_deviation(my_list));
    printf("token drop probability= %s\n",print_avg_packets_and_drop_prob(count_token_drop(),temp_use_char));
    //long int 
    
    printf("packet drop probability = %s\n",print_avg_packets_and_drop_prob(count_packet_drop(my_list),temp_use_char));
    //printf("%d%d",token,token_amount);
    free(temp_use_char);
}
