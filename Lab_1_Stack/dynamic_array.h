#ifndef DYNARR
#define DYNARR

#include <stdio.h>

#include "errors.h"


typedef int ElemArr_t;


struct DynamicArray
{
    ElemArr_t* array;
    size_t size;
    size_t capacity;
};

// struct DynamicArray* DynamicArray_Ctor(size_t size, size_t element_size);
enum ProgrammStatus  DynamicArray_Ctor(struct DynamicArray* dyn_stack, size_t size, size_t element_size);
struct DynamicArray* DynamicArray_Dtor(struct DynamicArray* dyn_stack);

enum ProgrammStatus dynamic_array_push  (struct DynamicArray* dyn_stack, ElemArr_t* elem);
enum ProgrammStatus dynamic_array_pop   (struct DynamicArray* dyn_stack, ElemArr_t* elem); // NOT RETURN ELEM!!!!!!! ?????????????????????????
enum ProgrammStatus get_last_elem       (struct DynamicArray* dyn_stack, ElemArr_t* elem);
enum ProgrammStatus resize_dynamic_array(struct DynamicArray* dyn_stack, size_t new_size);


void print_dyn_stack_info(struct DynamicArray* dyn_stack);




#endif