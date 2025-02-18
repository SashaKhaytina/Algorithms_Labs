#include <stdio.h>

#include "tests.h"

#include "dynamic_array.h"


int main()
{
    struct DynamicArray dyn_stack = {};
    DynamicArray_Ctor(&dyn_stack, 4, sizeof(ElemArr_t));

    TEST1

    DynamicArray_Dtor(&dyn_stack);

}