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


/*! \brief Function create dynamic array.
 * \param[in] dyn_stack Pointer to created stack.
 * \param[in] size Initial stack size.
 * \param[in] element_size Size of element of stack.
 *
 * \return Execution status.
*/
enum TestStatus      Dynamic_Array_Ctor(struct DynamicArray* dyn_stack, size_t size, size_t element_size);


/*! \brief Function free dynamic array.
 * \param[in] dyn_stack Pointer to stack.
 *
 * \return NULL.
*/
struct DynamicArray* Dynamic_Array_Dtor(struct DynamicArray* dyn_stack);



/*! \brief Function push (add) element in dynamic array.
 * \param[in] dyn_stack Pointer to stack.
 * \param[in] elem Element which push in stack.
 *
 * \see resize_dynamic_array(&dyn_stack, new_size)
 * 
 * \return Execution status.
*/
enum TestStatus dynamic_array_push         (struct DynamicArray* dyn_stack, ElemArr_t* elem);


/*! \brief Function pop (delete) element in dynamic array.
 * \param[in] dyn_stack Pointer to stack.
 *
 * \see resize_dynamic_array(&dyn_stack, new_size)
 * 
 * \return Execution status.
*/
enum TestStatus dynamic_array_pop          (struct DynamicArray* dyn_stack);


/*! \brief Function put last dynamic array`s element in elem.
 * \param[in] dyn_stack Pointer to stack.
 * \param[in] elem Variable into which the value last stack`s element will be placed.
 * 
 * \return Execution status.
*/
enum TestStatus dynamic_array_get_last_elem(const struct DynamicArray* dyn_stack, ElemArr_t* elem);


/*! \brief Function print info about dynamic array.
 * \param[in] dyn_stack Pointer to stack.
*/
void dynamic_array_print_info(const struct DynamicArray* dyn_stack); 


#endif