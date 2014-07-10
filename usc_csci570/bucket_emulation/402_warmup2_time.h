//
//  402_warmup2_time.h
//  402_warmup2
//
//  Created by linghao on 12-9-30.
//  Copyright (c) 2012年 linghao. All rights reserved.
//

#ifndef _02_warmup2__02_warmup2_time_h
#define _02_warmup2__02_warmup2_time_h
#include "header.h"
#include <string.h>
extern struct timeval ini_time;
extern struct reg_input my_reg_input;
long int interval_time(struct timeval*, struct timeval*);
char* show_ms_time(struct timeval*, char*);
long int count_interval_time(struct timeval*, struct timeval*);
char* print_interval_time(long int,char*);
unsigned int decide_sleep_time(my_packet*);
extern int msg_type;
#endif
