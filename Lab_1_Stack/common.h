#ifndef COMMON_H
#define COMMON_H

#include <stdio.h>

#include "errors.h"

#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__) 
#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)

typedef int ElemArr_t; 

enum ModeStack
{
    DYNAMIC_STACK, 
    LIST
};

#endif