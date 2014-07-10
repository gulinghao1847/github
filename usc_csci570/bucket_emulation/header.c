//
//  header.c
//  402_warmup2
//
//  Created by linghao on 12-10-6.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#include <stdio.h>
#include <string.h>

#include "header.h"
void clean_char_array(char* array){
    int j=0;
    for (j=(int)strlen(array);j>=0;j--) {
        array[j]='\0';
    }
}


void store_line_to_struct(char* one_line,my_packet* packet){
    int i=0;
    int j=0;
    //int z=0;
    char temp_char[20];
    for (i=0;one_line[i]!='\t'&&one_line[i]!=' ';i++) {
        temp_char[j]=one_line[i];
        j++;
    }
    j=0;
    packet->org_inter_arrival=atoi(one_line);
    //printf("%ld\n",packet->org_inter_arrival);
    clean_char_array(temp_char);
    
    for (;one_line[i]=='\t'||one_line[i]==' ';i++) {
    }
    for (;one_line[i]!='\t'&&one_line[i]!=' ';i++) {
        temp_char[j]=one_line[i];
        j++;
    }
    j=0;
    packet->token_need=atoi(temp_char);
    //printf("%d\n token_need\n",packet->token_need);
    clean_char_array(temp_char);
    
    for (;one_line[i]=='\t'||one_line[i]==' ';i++) {
    }
    
    for (;one_line[i]!='\0';i++) {
        temp_char[j]=one_line[i];
        j++;
    }
    
    packet->mu=atoi(temp_char);
    //printf("%d\n",packet->mu);
    clean_char_array(temp_char);
}
