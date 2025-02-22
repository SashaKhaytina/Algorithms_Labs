#ifndef LIST
#define LIST

#include <stdio.h>

#include "../errors.h"


// typedef int ElemArr_t;


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


enum ProgrammStatus List_Ctor(struct List* list);
struct List*        List_Dtor(struct List* list);

enum ProgrammStatus list_push     (struct List* list, ElemArr_t* elem);
enum ProgrammStatus list_pop      (struct List* list);
enum ProgrammStatus get_first_elem(struct List* list, ElemArr_t* elem);

void print_list(struct List* list);





#endif