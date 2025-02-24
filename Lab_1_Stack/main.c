#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>


#include "header.h"

#include "dynamic_array/dynamic_array.h"
#include "singly_linked_list/list.h"

#include "input/input.h"



int main(int argc, char* argv[])
{


    FILE* test_file = fopen(argv[1], "r");

    if (strcmp(argv[2], "DYN") == 0)
    {
        struct DynamicArray dyn_stack = {};
        DynamicArray_Ctor(&dyn_stack, 4, sizeof(ElemArr_t));

        START_TIMER
        get_test(test_file, DYNAMIC_STACK, &dyn_stack);
        END_TIMER
        
        DynamicArray_Dtor(&dyn_stack);
    }
    else
    {
        struct List list = {};
        List_Ctor(&list);

        START_TIMER
        get_test(test_file, LIST, &list);
        END_TIMER

        List_Dtor(&list);
    }

}