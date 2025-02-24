#include <stdio.h>
#include <string.h>

#include "header.h"

// #include "tests.h"

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
        get_test(test_file, DYNAMIC_STACK, &dyn_stack);
        DynamicArray_Dtor(&dyn_stack);
    }
    else
    {
        struct List list = {};
        List_Ctor(&list);
        get_test(test_file, LIST, &list);
        List_Dtor(&list);
    }


    // printf("END ARRAY\n");



















    // printf("TEST DYN ARR:\n\n");

    // struct DynamicArray dyn_stack = {};
    // DynamicArray_Ctor(&dyn_stack, 4, sizeof(ElemArr_t));

    // TEST_DYN_ARR_1

    // DynamicArray_Dtor(&dyn_stack);

    //______________________________________________________

    // printf("TEST LIST:\n\n");

    // struct List list = {};
    // List_Ctor(&list);

    // TEST_LIST_1

    // List_Dtor(&list);


}