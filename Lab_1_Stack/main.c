#include <stdio.h>

#include "tests.h"

#include "dynamic_array.h"
#include "singly_linked_list/list.h"


int main()
{
    // printf("TEST DYN ARR:\n\n");

    // struct DynamicArray dyn_stack = {};
    // DynamicArray_Ctor(&dyn_stack, 4, sizeof(ElemArr_t));

    // TEST_DYN_ARR_1

    // DynamicArray_Dtor(&dyn_stack);

    //______________________________________________________

    printf("TEST LIST:\n\n");

    struct List list = {};
    List_Ctor(&list);

    TEST_LIST_1

    List_Dtor(&list);


}