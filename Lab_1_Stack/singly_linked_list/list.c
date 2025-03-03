#include "list.h"

#include <malloc.h>


static struct Node* create_new_node(ElemArr_t* elem, struct Node* next, enum TestStatus* status);
static void         print_nodes    (const struct Node* node);


enum TestStatus List_Ctor(struct List* list)
{
    assert(list);
    enum TestStatus status = OK;


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


enum TestStatus list_push(struct List* list, ElemArr_t* elem)
{
    assert(list);
    assert(elem);
    enum TestStatus status = OK;

    list->start_list = create_new_node(elem, list->start_list, &status); 

    list->size++;


    return status;
}


enum TestStatus list_pop(struct List* list)
{
    assert(list); 
    enum TestStatus status = OK;


    if (list->size == 0) return POP_EMPTY_STACK;


    struct Node* pop_node = list->start_list;

    list->start_list = list->start_list->next;
    
    free(pop_node);

    list->size--;


    return status;
}


enum TestStatus list_get_first_elem(const struct List* list, ElemArr_t* elem)
{
    assert(list);
    assert(elem);
    enum TestStatus status = OK;


    if (list->size == 0) status = GET_ELEM_IN_EMPTY_STACK;
    CHECK_STATUS(status);

    *elem = list->start_list->num;

    return status;
}


static struct Node* create_new_node(ElemArr_t* elem, struct Node* next, enum TestStatus* status)
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




void list_print(const struct List* list)
{
    printf("LIST:\nsize - %lu\n", list->size);

    if (list->start_list != NULL) print_nodes(list->start_list);

    printf("\n\n");
}


static void print_nodes(const struct Node* node)
{
    printf("%d ", node->num);

    if (node->next != NULL) print_nodes(node->next);
}

