#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#include "errors.h"

#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__) 
#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)


// #define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);

// #define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
//                     average_time += ((double) (time_end.tv_sec * 1000 + time_end.tv_usec / 1000)) - ((double) time_start.tv_sec * 1000 + time_start.tv_usec / 1000);


typedef int ElemArr_t; 

enum ModeStack
{
    DYNAMIC_STACK, 
    LIST
};


// void print_test_time(enum ModeStack mode, char* file_test_name, double average_time, int num_test)
// {
//     if (mode == DYNAMIC_STACK) PRINTF_CYAN("DYNAMIC ARRAY:");
//     else                       PRINTF_CYAN("LIST:");
//     PRINTF_GREEN(" time of %s test: %g millisecond\n", file_test_name, average_time/num_test);
// }

#endif