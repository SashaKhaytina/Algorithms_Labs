#ifndef COMMON_H
#define COMMON_H


#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__) 
#define PRINTF_CYAN(string, ...)    printf("\x1b[36m" string "\x1b[0m", ##__VA_ARGS__)


typedef struct 
{
    int start;
    int finish;
} Segment;

typedef int Elem_t;

#define BIT_IN_INT 32

#endif