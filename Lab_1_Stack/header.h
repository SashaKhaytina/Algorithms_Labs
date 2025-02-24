#ifndef HEADER
#define HEADER

#include <stdio.h>

#include "errors.h"

#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__) 

// #define START_TIMER time_t time_start = 0; time_start = time(&time_start);
// #define END_TIMER   time_t time_end = 0;   time_end   = time(&time_end);\
//                     PRINTF_GREEN("DYNAMIC ARRAY: time of %s test: %f\n", argv[1], difftime(time_end, time_start));

#define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);
#define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
                    PRINTF_GREEN("DYNAMIC ARRAY: time of %s test: %g millisecond\n", argv[1], ((long long) time_end.tv_sec * 1000 + time_end.tv_usec / 1000) - ((long long) time_start.tv_sec * 1000 + time_start.tv_usec / 1000));


typedef int ElemArr_t; 

enum Mode
{
    DYNAMIC_STACK, 
    LIST
};

#endif