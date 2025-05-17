#include "sparce_table_longer.h"

#include <assert.h>
#include <malloc.h>

static Elem_t min(Node_longer* first_node, Node_longer* second_node);



Sparse_Table_Longer* sparse_table_longer__build(int* array, int array_size) 
{
    assert(array);


    Sparse_Table_Longer* sparse_table = (Sparse_Table_Longer*) calloc(1, sizeof(Sparse_Table_Longer));
    if (sparse_table == NULL) return NULL;
    sparse_table->array_size = array_size;

    // int hight = ((int) log2((double) array_size)) + 2;
    int hight = 32 - __builtin_clz(array_size);
    sparse_table->hight = hight;
    sparse_table->table = (Node_longer**) calloc(hight, sizeof(Node_longer*));
    if (sparse_table->table == NULL) 
    {
        free(sparse_table);
        return NULL;
    }


    for (int i = 0; i < hight; i++)
    {
        sparse_table->table[i] = (Node_longer*) calloc(array_size, sizeof(Node_longer));
        if (sparse_table->table[i] == NULL)
        {
            for (int j = 0; j < i; j++) free(sparse_table->table[j]);

            free(sparse_table->table);
            free(sparse_table);
            return NULL;
        }
    } 

    sparse_table_longer__fill(sparse_table, array);

    return sparse_table;
}

void sparse_table_longer__fill(Sparse_Table_Longer* sparse_table, int* array)
{
    assert(sparse_table);
    assert(sparse_table->table);
    assert(array);


    for (int i = 0; i < sparse_table->array_size; i++) // "листья". Тут лежаат сами числа, а не отрезк и (отрезки длиной 1)
    {
        sparse_table->table[0][i].minimum = array[i];
    }

    for (int i = 1; i < sparse_table->hight; i++) 
    {
        for (int j = 0; j < sparse_table->array_size - (1 << i) + 1; j++) 
        {
            Elem_t min_in_segment = min(&sparse_table->table[i - 1][j], &sparse_table->table[i - 1][j + (1 << (i - 1))]); // ищет 2 минимума из 2 отрезков (у каждого тоже есть 2 минимума)
            sparse_table->table[i][j].minimum = min_in_segment;
        }
    }
}

Elem_t sparse_table_longer__get_min_in_segment(Sparse_Table_Longer* sparse_table, int left, int right) 
{
    assert(sparse_table);
    assert(sparse_table->table);


    int len = right - left + 1;
    if (len == 0) return DEGENERATE_SEGMENT;

    int needed_hight = 31 - __builtin_clz(len);

    Elem_t minimum_in_segment = min(&sparse_table->table[needed_hight][left], &sparse_table->table[needed_hight][right - (1 << needed_hight) + 1]);

    return minimum_in_segment;
}

Sparse_Table_Longer* sparse_table_longer__free(Sparse_Table_Longer* sparse_table) 
{
    assert(sparse_table);
    assert(sparse_table->table);

    for (int i = 0; i < sparse_table->hight; i++) free(sparse_table->table[i]);
    free(sparse_table->table);
    free(sparse_table);

    return NULL;
}


static Elem_t min(Node_longer* first_node, Node_longer* second_node)
{
    assert(first_node);
    assert(second_node);


    if (first_node->minimum < second_node->minimum) return first_node->minimum;
    else return second_node->minimum;
}


void sparse_table_longer__dump(Sparse_Table_Longer* sparse_table) 
{
    assert(sparse_table);
    
    printf("Sparse Table Dump (%d rows x %d cols):\n", 32 - __builtin_clz(sparse_table->array_size), sparse_table->array_size);
    
    printf("     ");
    for (int j = 0; j < sparse_table->array_size; j++) printf("| %6d ", j);
    printf("\n");
    
    for (int j = 0; j < sparse_table->array_size + 1; j++) printf("---------");
    printf("\n");
    

    for (int i = 0; i < 32 - __builtin_clz(sparse_table->array_size); i++)
    {
        printf(" %6d ", 1 << i);

        for (int j = 0; j < sparse_table->array_size; j++) 
        {
            if (j + (1 << i) <= sparse_table->array_size) printf("| %6d ", sparse_table->table[i][j].minimum);
            else printf("| %6s ", "-");
        }
        printf("\n");
    }
}