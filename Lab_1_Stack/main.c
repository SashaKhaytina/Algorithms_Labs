#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#include "dynamic_array/dynamic_array.h"
#include "singly_linked_list/list.h"

#include "input/input.h"
#include "timer.h"

const int NUM_TESTS = 51;


int main(int argc, char* argv[])
{
    if (strcmp(argv[2], "DYN") == 0)
    {
        double average_time = 0;

        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            FILE* test_file = fopen(argv[1], "r");


            struct DynamicArray dyn_stack = {};
            dynamic_array_ctor(&dyn_stack, 4, sizeof(ElemArr_t));

            COUNT_TIME(run_test(test_file, DYNAMIC_STACK, &dyn_stack);)
            
            dynamic_array_dtor(&dyn_stack);


            fclose(test_file);
        }

        // PRINTF_CYAN("DYNAMIC ARRAY:");
        // PRINT_TIME
        print_test_time(DYNAMIC_STACK, argv[1], average_time, NUM_TESTS);
    }
    else
    {
        double average_time = 0;

        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            FILE* test_file = fopen(argv[1], "r");


            struct List list = {};
            list_ctor(&list);

            COUNT_TIME(run_test(test_file, LIST, &list);)

            list_dtor(&list);


            fclose(test_file);
        }

        // PRINTF_CYAN("LIST:");
        // PRINT_TIME
        print_test_time(LIST, argv[1], average_time, NUM_TESTS);
    }

}


// void print_test_time(enum ModeStack mode, char* file_test_name, double average_time, int num_test)
// {
//     if (mode == DYNAMIC_STACK) PRINTF_CYAN("DYNAMIC ARRAY:");
//     else                       PRINTF_CYAN("LIST:");
//     PRINTF_GREEN(" time of %s test: %g millisecond\n", file_test_name, average_time/num_test);
// }