#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include "errors.h"
#include "common.h"

#define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);

#define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
                    average_time += ((double) (time_end.tv_sec * 1000 + time_end.tv_usec / 1000)) - ((double) time_start.tv_sec * 1000 + time_start.tv_usec / 1000);

#define COUNT_TIME(code) START_TIMER\
                        code\
                        END_TIMER

void print_test_time(enum ModeStack mode, char* file_test_name, double average_time, int num_test);


#endif