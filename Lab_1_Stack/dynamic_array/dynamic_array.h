#ifndef DYNAMIC_ARRAY_STACK_H
#define DYNAMIC_ARRAY_STACK_H

#include <stdio.h>

#include "../common.h"


struct DynamicArray
{
    ElemArr_t* array;
    size_t size;
    size_t capacity;
};

enum TestStatus  Dynamic_Array_Ctor(struct DynamicArray* dyn_stack, size_t size, size_t element_size);
struct DynamicArray* Dynamic_Array_Dtor(struct DynamicArray* dyn_stack);

enum TestStatus dynamic_array_push         (struct DynamicArray* dyn_stack, ElemArr_t* elem);
enum TestStatus dynamic_array_pop          (struct DynamicArray* dyn_stack);
enum TestStatus dynamic_array_get_last_elem(struct DynamicArray* dyn_stack, ElemArr_t* elem); // const

void dynamic_array_print_info(struct DynamicArray* dyn_stack); // const


#endif