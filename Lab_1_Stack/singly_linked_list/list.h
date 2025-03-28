#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include <stdio.h>

#include "../common.h"


struct Node
{
    ElemArr_t num;
    struct Node* next;
};


struct List
{
    struct Node* start_list;
    size_t size;
};


/*! \brief Function create linked list.
 * \param[in] list Pointer to created stack.
 *
 * \return Execution status.
*/
enum TestStatus     list_ctor(struct List* list);


/*! \brief Function free linked list.
 * \param[in] list Pointer to stack.
 *
 * \return NULL.
*/
struct List*        list_dtor(struct List* list);



/*! \brief Function push (add) element in linked list.
 * \param[in] list Pointer to stack.
 * \param[in] elem Element which push in stack.
 *
 * \see create_new_node(&elem, &next, &status)
 * 
 * \return Execution status.
*/
enum TestStatus list_push          (struct List* list, ElemArr_t* elem);


/*! \brief Function pop (delete) element in linked list.
 * \param[in] list Pointer to stack.
 * 
 * \return Execution status.
*/
enum TestStatus list_pop           (struct List* list);


/*! \brief Function put last added linked list`s element in elem.
 * \param[in] list Pointer to stack.
 * \param[in] elem Variable into which the value last added stack`s element will be placed.
 * 
 * \return Execution status.
*/
enum TestStatus list_get_first_elem(const struct List* list, ElemArr_t* elem);


/*! \brief Function print info about linked list.
 * \param[in] dyn_stack Pointer to stack.
*/
void list_print(const struct List* list);





#endif