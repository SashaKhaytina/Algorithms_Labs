#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


// #include "common.h"

#include "dynamic_array/dynamic_array.h"
#include "singly_linked_list/list.h"

#include "input/input.h"

const int NUM_TESTS = 21;


int main(int argc, char* argv[])
{
    if (strcmp(argv[2], "DYN") == 0)
    {
        double average_time = 0;

        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            FILE* test_file = fopen(argv[1], "r");


            struct DynamicArray dyn_stack = {};
            Dynamic_Array_Ctor(&dyn_stack, 4, sizeof(ElemArr_t));

            START_TIMER
            get_test(test_file, DYNAMIC_STACK, &dyn_stack);
            END_TIMER
            
            Dynamic_Array_Dtor(&dyn_stack);


            fclose(test_file);
        }

        PRINTF_CYAN("DYNAMIC ARRAY:");
        PRINT_TIME
    }
    else
    {
        double average_time = 0;

        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            FILE* test_file = fopen(argv[1], "r");


            struct List list = {};
            List_Ctor(&list);

            START_TIMER
            get_test(test_file, LIST, &list);
            END_TIMER

            List_Dtor(&list);


            fclose(test_file);
        }

        PRINTF_CYAN("LIST:");
        PRINT_TIME
    }

}