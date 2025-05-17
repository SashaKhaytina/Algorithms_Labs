#include "sparce_table_higher.h"

#include <assert.h>
#include <malloc.h>


static Elem_t min(Node_higher* first_node, Node_higher* second_node);



Sparse_Table_Higher* sparse_table_higher__build(int* array, int array_size) 
{
    assert(array);


    Sparse_Table_Higher* sparse_table = (Sparse_Table_Higher*) calloc(1, sizeof(Sparse_Table_Higher));
    if (sparse_table == NULL) return NULL;
    sparse_table->array_size = array_size;

    int hight = array_size;
    sparse_table->hight = hight;
    sparse_table->table = (Node_higher**) calloc(hight, sizeof(Node_higher*));
    if (sparse_table->table == NULL) 
    {
        free(sparse_table);
        return NULL;
    }


    int wight = 32 - __builtin_clz(array_size);
    for (int i = 0; i < hight; i++)
    {
        sparse_table->table[i] = (Node_higher*) calloc(wight, sizeof(Node_higher));
        if (sparse_table->table[i] == NULL)
        {
            for (int j = 0; j < i; j++) free(sparse_table->table[j]);

            free(sparse_table->table);
            free(sparse_table);
            return NULL;
        }
    } 

    sparse_table_higher__fill(sparse_table, array);

    return sparse_table;
}

void sparse_table_higher__fill(Sparse_Table_Higher* sparse_table, int* array)
{
    assert(sparse_table);
    assert(sparse_table->table);
    assert(array);


    for (int i = 0; i < sparse_table->array_size; i++) // "листья". Тут лежаат сами числа, а не отрезк и (отрезки длиной 1)
    {
        sparse_table->table[i][0].minimum = array[i];
    }

    int levels_stolbs = 32 - __builtin_clz(sparse_table->array_size);
    for (int j = 1; j < levels_stolbs; j++)  
    {
        for (int i = 0; i <= sparse_table->hight - (1 << j); i++)
        {
            
            Elem_t min_in_segment = min(&sparse_table->table[i][j - 1], &sparse_table->table[i + (1 << (j - 1))][j - 1]); // ищет 2 минимума из 2 отрезков (у каждого тоже есть 2 минимума)
            sparse_table->table[i][j].minimum = min_in_segment;
        }
    }
}

Elem_t sparse_table_higher__get_min_in_segment(Sparse_Table_Higher* sparse_table, int left, int right) 
{
    assert(sparse_table);
    assert(sparse_table->table);


    int len = right - left + 1;
    if (len == 0) return DEGENERATE_SEGMENT;

    int needed_hight = 31 - __builtin_clz(len);

    Elem_t minimum_in_segment = min(&sparse_table->table[left][needed_hight], &sparse_table->table[right - (1 << needed_hight) + 1][needed_hight]);

    return minimum_in_segment;
}


Sparse_Table_Higher* sparse_table_higher__free(Sparse_Table_Higher* sparse_table) 
{
    assert(sparse_table);
    assert(sparse_table->table);

    for (int i = 0; i < sparse_table->hight; i++) free(sparse_table->table[i]);
    free(sparse_table->table);
    free(sparse_table);

    return NULL;
}


static Elem_t min(Node_higher* first_node, Node_higher* second_node)
{
    assert(first_node);
    assert(second_node);


    if (first_node->minimum < second_node->minimum) return first_node->minimum;
    else return second_node->minimum;
}






void sparse_table_higher__dump(Sparse_Table_Higher* sparse_table) 
{
    assert(sparse_table);
    
    printf("Sparse Table Dump (%d rows x %d cols):\n", sparse_table->hight, 32 - __builtin_clz(sparse_table->array_size));
    
    printf("     ");

    for (int j = 0; j < 32 - __builtin_clz(sparse_table->array_size); j++) printf("| %6d ", 1 << j);
    printf("\n");
    
    for (int j = 0; j < 32 - __builtin_clz(sparse_table->array_size) + 1; j++) printf("---------");
    printf("\n");
    

    for (int i = 0; i < sparse_table->hight; i++) 
    {
        printf(" %6d ", i);

        for (int j = 0; j < 32 - __builtin_clz(sparse_table->array_size); j++) 
        {
            if (i + (1 << j) <= sparse_table->array_size) printf("| %6d ", sparse_table->table[i][j].minimum);
            else printf("| %6s ", "-");
        }
        printf("\n");
    }
}

