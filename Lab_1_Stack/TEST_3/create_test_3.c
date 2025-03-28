#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <sys/time.h>
#include <time.h>

#include "../dynamic_array/dynamic_array.h"
#include "../singly_linked_list/list.h"

#include "../common.h"
#include "../input/input.h"
#include "../timer.h"



const char* NAME_FILE_TEST_3 = "test3.txt";
const int   SIZE_TEST_3      = 1000000;
const int   NUM_TESTS        = 51;

void create_file();


int main(int argc, char* argv[])
{
    enum TestStatus status = OK;

    create_file();

    FILE* test_file = fopen(argv[1], "r");


    if (strcmp(argv[2], "DYN") == 0)
    {
        double average_time = 0;

        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            struct DynamicArray dyn_stack = {};
            dynamic_array_ctor(&dyn_stack, 4, sizeof(ElemArr_t));

            for (int i = 1; i < SIZE_TEST_3 + 1; i++) { status = dynamic_array_push(&dyn_stack, &i); }
            START_TIMER
            run_test(test_file, DYNAMIC_STACK, &dyn_stack);
            END_TIMER

            dynamic_array_dtor(&dyn_stack);
        }

        // PRINTF_CYAN("DYNAMIC ARRAY:");
        // PRINT_TIME
        print_test_time(DYNAMIC_STACK, argv[1], average_time, NUM_TESTS);


        fclose(test_file);
    }
    else
    {
        double average_time = 0;
        for (size_t i = 0; i < NUM_TESTS; i++)
        {
            struct List list = {};
            list_ctor(&list);

            for (int i = 1; i < SIZE_TEST_3 + 1; i++) { status = list_push(&list, &i); }
            START_TIMER
            run_test(test_file, LIST, &list);
            END_TIMER

            list_dtor(&list);
        }

        // PRINTF_CYAN("LIST:");
        // PRINT_TIME
        print_test_time(LIST, argv[1], average_time, NUM_TESTS);

        
        fclose(test_file);
    }
}


void create_file()
{
    FILE* file = fopen(NAME_FILE_TEST_3, "w");

    for (int i = 0; i < SIZE_TEST_3; i++)
    {
        int rand_command = 0;
        rand_command = 1 + (rand() % 2);
        if (rand_command == 1) fprintf(file, "PUSH %d\n", i);
        else                   fprintf(file, "POP\n");
    }
    fclose(file);
}