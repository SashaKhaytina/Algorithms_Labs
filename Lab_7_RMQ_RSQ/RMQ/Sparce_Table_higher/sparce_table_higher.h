#ifndef SPARCE_TABLE_HIGHER_H
#define SPARCE_TABLE_HIGHER_H

#include <stdio.h>
#include "../common.h"

#define DEGENERATE_SEGMENT -1

typedef struct 
{
    int minimum;
} Node_higher;              // min in segment

typedef struct 
{
    Node_higher** table;
    int hight;              // count <---> (strings)
    int array_size;         // num element if first leevel (num elements)
} Sparse_Table_Higher;


Sparse_Table_Higher* sparse_table_higher__build             (int* array, int array_size);
void                 sparse_table_higher__fill              (Sparse_Table_Higher* sparse_table, int* array);
Elem_t               sparse_table_higher__get_min_in_segment(Sparse_Table_Higher* sparse_table, int left, int right);
Sparse_Table_Higher* sparse_table_higher__free              (Sparse_Table_Higher* sparse_table);

void                 sparse_table_higher__dump              (Sparse_Table_Higher* st);

#endif