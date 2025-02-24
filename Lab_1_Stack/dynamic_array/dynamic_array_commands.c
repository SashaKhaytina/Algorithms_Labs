#include "dynamic_array.h"

#include <malloc.h>


enum ProgrammStatus DynamicArray_Ctor(struct DynamicArray* dyn_stack, size_t size, size_t element_size)
{
    assert(dyn_stack);
    enum ProgrammStatus status = OK;
    

    dyn_stack->array = (ElemArr_t*) calloc(size, element_size);
    if (dyn_stack->array == NULL) status = ERROR_CTOR;
    CHECK_STATUS(status);

    dyn_stack->size = 0;
    dyn_stack->capacity = size;

    return status;
}


struct DynamicArray* DynamicArray_Dtor(struct DynamicArray* dyn_stack)
{   
    dyn_stack->size = 0;
    dyn_stack->capacity = 0;
    free(dyn_stack->array);

    return NULL;
}


enum ProgrammStatus dynamic_array_push(struct DynamicArray* dyn_stack, ElemArr_t* elem)
{
    assert(dyn_stack);
    assert(elem);
    enum ProgrammStatus status = OK;


    if (dyn_stack->size == dyn_stack->capacity)
    {
        status = resize_dynamic_array(dyn_stack, 2 * dyn_stack->capacity);
        CHECK_STATUS(status);
    }

    dyn_stack->array[dyn_stack->size] = *elem;
    dyn_stack->size++;

    return status;
}


enum ProgrammStatus dynamic_array_pop(struct DynamicArray* dyn_stack)
{
    assert(dyn_stack);
    enum ProgrammStatus status = OK;


    if (dyn_stack->size == 0) return POP_EMPTY_STACK;

    if (4 * dyn_stack->size <= dyn_stack->capacity)
    {
        status = resize_dynamic_array(dyn_stack, dyn_stack->capacity / 4);
        CHECK_STATUS(status);
    }

    dyn_stack->size--;
    dyn_stack->array[dyn_stack->size] = 0;

    return status;
}


enum ProgrammStatus get_last_elem(struct DynamicArray* dyn_stack, ElemArr_t* elem)
{
    assert(dyn_stack);
    assert(elem);
    enum ProgrammStatus status = OK;


    if (dyn_stack->size == 0) status = GET_ELEM_IN_EMPTY_STACK;
    CHECK_STATUS(status);

    *elem = dyn_stack->array[dyn_stack->size - 1];

    return status;
}


enum ProgrammStatus resize_dynamic_array(struct DynamicArray* dyn_stack, size_t new_size)
{
    assert(dyn_stack);
    enum ProgrammStatus status = OK;


    dyn_stack->array = (ElemArr_t*) realloc(dyn_stack->array, new_size * sizeof(ElemArr_t));
    if (dyn_stack->array == NULL) status = REALLOC_ERROR;
    CHECK_STATUS(status);

    dyn_stack->capacity = new_size;

    return status;
}





void print_dyn_stack_info(struct DynamicArray* dyn_stack)
{
    assert(dyn_stack);
    printf("capacity - %lu\n", dyn_stack->capacity);
    printf("size - %lu\n", dyn_stack->size);

    for (int i = (int) dyn_stack->size - 1; i >= 0; i--)
    {
        printf("arr[%d] = %d\n", i, dyn_stack->array[i]);
    }
    
    printf("\n\n");
}
