#ifndef SPARCE_TABLE_WORK_H
#define SPARCE_TABLE_WORK_H

#include "../common.h"

#include <time.h>
#include <sys/time.h>

#define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);

#define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
                    average_time += ((double) (time_end.tv_sec * 1000 + time_end.tv_usec / 1000)) - ((double) time_start.tv_sec * 1000 + time_start.tv_usec / 1000);

#define COUNT_TIME(code) START_TIMER\
                        code\
                        END_TIMER


double do_commands__sparce_table_longer(Elem_t* num_arr, int num_arr_size, Segment* seg_arr, int seg_arr_size);
double do_commands__sparce_table_higher(Elem_t* num_arr, int num_arr_size, Segment* seg_arr, int seg_arr_size);


#endif