#ifndef SPARCE_TABLE_LONGER_H
#define SPARCE_TABLE_LONGER_H

#include <stdio.h>
#include "../common.h"

#define DEGENERATE_SEGMENT -1

typedef struct 
{
    Elem_t minimum;
} Node_longer;              // min in segment

typedef struct 
{
    Node_longer** table;
    int hight;              // count <---> (strings)
    int array_size;         // num element if first leevel (num elements)
} Sparse_Table_Longer;


Sparse_Table_Longer* sparse_table_longer__build             (int* array, int array_size);
void                 sparse_table_longer__fill              (Sparse_Table_Longer* sparse_table, int* array);
Elem_t               sparse_table_longer__get_min_in_segment(Sparse_Table_Longer* sparse_table, int left, int right); 
Sparse_Table_Longer* sparse_table_longer__free              (Sparse_Table_Longer* sparse_table);

void                 sparse_table_longer__dump              (Sparse_Table_Longer* st);

#endif