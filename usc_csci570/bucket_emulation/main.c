//
//  main.c
//  402_warmup2
//
//  Created by linghao on 12-9-29.
//  Copyright (c) 2012年 linghao. All rights reserved.
//
//all time unit in the struct packet are ms, but in each thread their units are all nanosecond, so we need to change when we want to use.

#include "header.h"
#include "my402list.h"
#include "arrival_thread.h"
#include "token_arrival.h"
#include "server_thread.h"
#include "statistics.h"
pthread_mutex_t queue_1=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_2=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t queue_3=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t token_mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t printf_mutex=PTHREAD_MUTEX_INITIALIZER;
//pthread_cond_t read_queue_1=PTHREAD_COND_INITIALIZER;
pthread_cond_t read_queue_2=PTHREAD_COND_INITIALIZER;


int token=0;              //here we use a global var to realize sync
int can_move=0;
long int num_enter=20;
int token_amount=0;
int lose_packet=0;
int lose_token=0;
char* file_name;
int time_to_quit=1;
int given_time=0;


FILE* file;
int msg_type=1;  //indicate which type of program need to be run  default type is reg_type
struct timeval ini_time;
struct timeval end_time;

int leave_arrive_thread=0;
int leave_token_thread=0;
int leave_server_thread=0;


My402List* my_list_q1;
My402List* my_list_q2;
My402List* my_list_q3;
//My402List* my_list_q4;


pthread_t arrival_pthread;
pthread_t token_arrival_pthread;
pthread_t server_pthread;
pthread_t handle_SIGINT;
pthread_t kill_handle;
sigset_t my_signal;

struct reg_input my_reg_input={3,2000,2857,667,10};;  //all time unit is ms in main but it must change the time to nanotime
struct org_struct_input my_struct_input={"0.5","1.5","0.35","tsfile"};


void *handler(){
    int sig;
    
        sigwait(&my_signal,&sig);
        time_to_quit=0;
        //printf("done1\n");
        pthread_cancel(arrival_pthread);
        //printf("done2\n");
        pthread_cancel(token_arrival_pthread);
        //printf("done3\n");
        pthread_cancel(server_pthread);
        return 0;
    
    //return 0;
    
}
void process_file_input(char* file_name)
{
    my_list_q1=(My402List*)malloc(sizeof(My402List));
    my_list_q2=(My402List*)malloc(sizeof(My402List));
    my_list_q3=(My402List*)malloc(sizeof(My402List));
    //my_list_q4=(My402List*)malloc(sizeof(My402List));
    
    void* (*my_process)(void*);
    char* temp_printf=malloc(50*sizeof(char));
    char temp_num[5];
    //FILE* file;
    My402ListInit(my_list_q1);
    My402ListInit(my_list_q2);
    My402ListInit(my_list_q3);
    //My402ListInit(my_list_q4);
    //printf("here\n");
    if((file=fopen(file_name,"r"))==NULL){
        fprintf(stderr,"can't find the file\n");
        exit(1);
    }
    fgets(temp_num,1026,file);
    //printf("the num_enter: %s\n",temp_num);
    num_enter=atoi(temp_num);
    gettimeofday(&ini_time,NULL);
    print_header();
    printf("%semulation begins\n",show_ms_time(&ini_time,temp_printf));
    
    my_process=&arrival_file;
    sigemptyset(&my_signal);
    sigaddset(&my_signal,SIGINT);
    pthread_sigmask(SIG_BLOCK,&my_signal,NULL);
    pthread_create(&arrival_pthread,0,my_process,0);
    pthread_create(&token_arrival_pthread,0, token_arrival, 0);
    pthread_create(&server_pthread,0, server_thread,0);
    pthread_create(&handle_SIGINT,0,handler,0);
    //pthread_create(&kill_handle,0,kill_handler,0);
    pthread_join(arrival_pthread,0);
    pthread_join(token_arrival_pthread,0);
    pthread_join(server_pthread,0);
    pthread_cancel(handle_SIGINT);
    //printf("done\n");
    //pthread_join(kill_handle,0);
    //printf("done\n");
    gettimeofday(&end_time,NULL);
    print_statistics(my_list_q3);
    //printf("ok\n");
    My402ListUnlinkAll(my_list_q1);
    //printf("ok\n");
    My402ListUnlinkAll(my_list_q2);
    //printf("ok\n");
    free(temp_printf);
    fclose(file);
    //printf("ok\n");
    return ;
}

void process_without_file()
{
    my_list_q1=(My402List*)malloc(sizeof(My402List));
    my_list_q2=(My402List*)malloc(sizeof(My402List));
    my_list_q3=(My402List*)malloc(sizeof(My402List));
    //my_list_q4=(My402List*)malloc(sizeof(My402List));
    
    char* temp_printf=malloc(50*sizeof(char));
    My402ListInit(my_list_q1);
    My402ListInit(my_list_q2);
    My402ListInit(my_list_q3);
    //My402ListInit(my_list_q4);
    //void* arrival();
    gettimeofday(&ini_time,NULL);
    //token_arrival();
    print_header();
    printf("%semulation begins\n",show_ms_time(&ini_time,temp_printf));
    //if (my_reg_input.token_need>my_reg_input.token_max) {
      //  fprintf(stderr,"every packet's needed tokens excesses the maximum tokens stored in the buffer, program exits.\n");
       // exit(1);
    //}
    
    sigemptyset(&my_signal);
    sigaddset(&my_signal,SIGINT);
    pthread_sigmask(SIG_BLOCK,&my_signal,NULL);
    pthread_create(&arrival_pthread,0,arrival_reg,0);
    pthread_create(&token_arrival_pthread,0, token_arrival, 0);
    pthread_create(&server_pthread,0, server_thread,0);
    pthread_create(&handle_SIGINT,0,handler,0);
    //pthread_create(&kill_handle,0,kill_handler,0);
    pthread_join(arrival_pthread,0);
    //printf("done\n");
    pthread_join(token_arrival_pthread,0);
    //printf("done\n");
    if (lose_packet==num_enter) {
        pthread_cancel(server_pthread);
    }
    pthread_join(server_pthread,0);
    //printf("done\n");
    //printf("done in the main function\n");
    pthread_cancel(handle_SIGINT);
    //printf("done\n");
    //pthread_join(kill_handle,0);
    gettimeofday(&end_time,NULL);
    print_statistics(my_list_q3);
    My402ListUnlinkAll(my_list_q1);
    My402ListUnlinkAll(my_list_q2);
    My402ListUnlinkAll(my_list_q3);
    /*
    free(my_list_q1);
    free(my_list_q2);
    free(my_list_q3);
     */
    free(temp_printf);
    return ;
}
 
long int get_amount(char* char_amount){     //get the real time in ms
    int i=0;
    long int amount=0;
    int j=0;
    for (i=0;char_amount[i]!='.'&&i<strlen(char_amount); i++) {
        amount=amount*10+(char_amount[i]-'0');
    }
    
    if (i==strlen(char_amount)) {
        amount=amount*1000; 
        return amount;
    }
    
    for (i=i+1;i<strlen(char_amount);i++) {
        j=j+1;
        amount=amount*10+(char_amount[i]-'0');
    }
    
    if (j<3) {
        for (j=j;j<3; j++) {
            amount=amount*10;
        }
    }
    
    return amount;
}

void Usage(){
    fprintf(stderr,"please enter a file name and other arguments : warmup2 -lambda lambda -mu mu -r r\\ -B B -P P -n num \\ -t tsfile\n");
    exit(1);
}

void check_input(char* symbol,char* input,int* is_right){
    long int temp_number;
    temp_number=get_amount(input);
    if (strcmp(symbol,"-lambda")==0) {
        if (my_reg_input.lambda!=2000) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        my_reg_input.lambda=1000000/temp_number;    //unit is ms/packet
        if (my_reg_input.lambda>10000) {
            my_reg_input.lambda=10000;
        }
        strcpy(my_struct_input.lambda,input);
        //printf("%s\n",my_struct_input.lambda);
        *is_right=1;
        if (my_reg_input.lambda>=10000) {
            strcpy(my_struct_input.lambda,"0.01");
        }
    }
    
    
    if (strcmp(symbol,"-mu")==0) {
            if (my_reg_input.mu!=2857) {
                fprintf(stderr,"duplicate command");
                Usage();
            }

        my_reg_input.mu=1000000/temp_number;        //unit is ms/packet
        if (my_reg_input.mu>10000) {
            my_reg_input.mu=10000;
        }
        strcpy(my_struct_input.mu,input);
        //printf("%s\n",my_struct_input.lambda);
        *is_right=1;
        if (my_reg_input.mu>=10000) {
            strcpy(my_struct_input.mu,"0.01");
        }
    }
        

    if (strcmp(symbol,"-r")==0) {
        if (my_reg_input.token_interval_time!=667) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        my_reg_input.token_interval_time=1000000/temp_number;  //unit is packet
        if (my_reg_input.token_interval_time>10000) {
            my_reg_input.token_interval_time=10000;
        }
        //printf("here\n");
        strcpy(my_struct_input.r,input);
        *is_right=1;
        if (my_reg_input.token_interval_time>=10000) {
            strcpy(my_struct_input.r,"0.01");
        }
    }
    if (strcmp(symbol,"-B")==0) {
        if (my_reg_input.token_max!=10) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        //printf("HERE\n");
        my_reg_input.token_max=temp_number/1000;    //unit is token
        *is_right=1;
    }
    if (strcmp(symbol,"-P")==0) {
        if (my_reg_input.token_need!=3) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        my_reg_input.token_need=temp_number/1000;       //
        *is_right=1;
    }
    if (strcmp(symbol,"-n")==0) {
        if (num_enter!=20) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        num_enter=atol(input);
        //printf("%ld~~~~~~~~~~~~~\n",num_enter);
        *is_right=1;
    }
    if (strcmp(symbol,"-t")==0) {
        if (strlen(file_name)!=0) {
            fprintf(stderr,"duplicate command");
            Usage();
        }
        msg_type=2; //indicate that it will use the file input
        strcpy(file_name,input);
        *is_right=1;
        strcpy(my_struct_input.file_name,input);
    }
}

void process_option(int argc,char* argv[]){
    int is_right=0;
    argc--,argv++;
    if (argc==0) {
        //printf("here\n");
        return;
    }
    
    for (;argc>=2;) {
        check_input(*argv,*(argv+1),&is_right);
        if (is_right!=1) {
            fprintf(stderr, "incorrect format");
            Usage();
        }
        argc=argc-2;
        argv++;
        argv++;
    }
    if (argc==1) {
        fprintf(stderr, "incorrect format");
        Usage();
    }
    
}


int main(int argc,char* argv[]){
    file_name=(char*)malloc(256*sizeof(char*));
    //my_struct_input={"0.5","1.5","0.35","tsfile"};
    //my_reg_input={3,2000,2857,667,10};
    process_option(argc,argv);
    if (msg_type==1) {
        process_without_file();
    }
    if (msg_type==2) {
        process_file_input(file_name);
    }
    //printf("ok\n");
    /*
    free(my_list_q1);
    free(my_list_q2);
    free(my_list_q3);
     */
    free(file_name);
    //printf("ok~~~~\n");
    //printf("ok\n");
    return 0;
}
