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


enum TestStatus List_Ctor(struct List* list);
struct List*        List_Dtor(struct List* list);

enum TestStatus list_push          (struct List* list, ElemArr_t* elem);
enum TestStatus list_pop           (struct List* list);
enum TestStatus list_get_first_elem(struct List* list, ElemArr_t* elem); //const

void list_print(struct List* list); // const





#endif