#include "list.h"

#include <malloc.h>


static void         free_list      (struct Node* cur_node);
static struct Node* create_new_node(ElemArr_t* elem, struct Node* next, enum ProgrammStatus* status);
static void         print_nodes    (struct Node* node);


enum ProgrammStatus List_Ctor(struct List* list)
{
    assert(list);
    enum ProgrammStatus status = OK;


    list->start_list = NULL;
    list->size = 0;

    return status;
}


struct List* List_Dtor(struct List* list)
{   
    assert(list);


    struct Node* current_node = list->start_list; 
    for (size_t i = 0; i < list->size; i++)
    {
        struct Node* new_current_node = current_node->next;
        free(current_node);
        current_node = new_current_node;
        if (current_node == NULL) break;
    }

    return NULL;
}


enum ProgrammStatus list_push(struct List* list, ElemArr_t* elem)
{
    assert(list); // We can do own assert for status
    assert(elem);
    enum ProgrammStatus status = OK;

    list->start_list = create_new_node(elem, list->start_list, &status); // Это можно разбить на "создали потом присвоили (без list->start_list)" для понятности

    list->size++;


    return status;
}


enum ProgrammStatus list_pop(struct List* list)
{
    assert(list); 
    enum ProgrammStatus status = OK;


    if (list->size == 0) return POP_EMPTY_STACK;


    struct Node* pop_node = list->start_list;

    list->start_list = list->start_list->next;
    
    free(pop_node);

    list->size--;


    return status;
}


enum ProgrammStatus get_first_elem(struct List* list, ElemArr_t* elem)
{
    assert(list);
    assert(elem);
    enum ProgrammStatus status = OK;


    if (list->size == 0) status = GET_ELEM_IN_EMPTY_STACK;
    CHECK_STATUS(status);

    *elem = list->start_list->num;

    return status;
}


static struct Node* create_new_node(ElemArr_t* elem, struct Node* next, enum ProgrammStatus* status)
{
    assert(elem);
    assert(status);
    if ((*status) != OK) return NULL;


    struct Node* new_node = (struct Node*) calloc(1, sizeof(struct Node));
    if (new_node == NULL)
    {
        *status = CALLOC_NODE_ERROR;
        return NULL;
    }

    new_node->num  = *elem;
    new_node->next = next;

    return new_node;
}




void print_list(struct List* list)
{
    printf("LIST:\nsize - %lu\n", list->size);

    if (list->start_list != NULL) print_nodes(list->start_list);

    printf("\n\n");
}


static void print_nodes(struct Node* node)
{
    printf("%d ", node->num);

    if (node->next != NULL) print_nodes(node->next);
}

