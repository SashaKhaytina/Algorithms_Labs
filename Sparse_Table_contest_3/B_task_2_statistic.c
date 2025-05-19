#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <malloc.h>

#define MAX 1000000007




typedef struct 
{
    int value;
    int index_in_arr;
} Pair;

typedef struct 
{
    Pair node[2];
} Node; // 2 min элемента

typedef struct 
{
    Node** table;
    int log_size; // количество СТРОК!
    int array_size; // начальный массив 
} Sparse_Table;



void          fill_sparse_table(Sparse_Table* sparse_table, int* array);
Sparse_Table* sparse_table_build(int* array, int array_size);
void          find_two_minimums(Node* first_node, Node* second_node, Pair* result);
int           get_second_min_in_segment(Sparse_Table* sparse_table, int left, int right);

int cmp_pairs(const void* a, const void* b);


int main() 
{
    int array_size, m;
    scanf("%d %d", &array_size, &m);

    int* array = (int*) calloc(array_size, sizeof(int));

    for (int i = 0; i < array_size; ++i) 
    {
        scanf("%d", &array[i]);
    }

    Sparse_Table* sparse_table = sparse_table_build(array, array_size);
    for (int i = 0; i < m; ++i) 
    {
        int left = 0;
        int right = 0;

        scanf("%d %d", &left, &right);
        left--;
        right--;
        printf("%d\n", get_second_min_in_segment(sparse_table, left, right));
    }


    for (int k = 0; k < sparse_table->log_size; ++k) free(sparse_table->table[k]);
    free(sparse_table->table);
    free(sparse_table);
    
    free(array);
    
    return 0;
}


//--------------------------------------------------------------------

void find_two_minimums(Node* first_node, Node* second_node, Pair* result) 
{
    Pair temp[5] = {first_node->node[0],
                    first_node->node[1],
                    second_node->node[0],
                    second_node->node[1],
                    {.value = MAX, .index_in_arr = MAX}
                    };

    qsort(temp, 5, sizeof(Pair), cmp_pairs);

    // for (int i = 0; i < 5; i++)
    // {
    //     printf("%d - val, %d - ind\n", temp[i].value,  temp[i].index_in_arr);
    // }

    result[0] = temp[0];
    // result[1] = {};
    for (int i = 0; i < 5; i++)
    {
        if (cmp_pairs(&temp[0], &temp[i]) != 0)
        {
            result[1] = temp[i];
            break;
        }
    }
    // result[1] = temp[1];
}



Sparse_Table* sparse_table_build(int* array, int array_size) 
{
    Sparse_Table* sparse_table = (Sparse_Table*) calloc(1, sizeof(Sparse_Table));
    sparse_table->array_size = array_size;

    // int hight = ((int) log2((double) array_size)) + 2;
    int hight = 32 - __builtin_clz(array_size);
    sparse_table->log_size = hight;
    sparse_table->table = (Node**) calloc(hight, sizeof(Node*));

    for (int k = 0; k < hight; ++k) sparse_table->table[k] = (Node*) calloc(array_size, sizeof(Node));

    fill_sparse_table(sparse_table, array);

    return sparse_table;
}

void fill_sparse_table(Sparse_Table* sparse_table, int* array)
{
    for (int i = 0; i < sparse_table->array_size; ++i) // "листья". Тут лежаат сами числа, а не отрезк и (отрезки длиной 1)
    {
        sparse_table->table[0][i].node[0].value = array[i];
        sparse_table->table[0][i].node[0].index_in_arr = i;
        sparse_table->table[0][i].node[1].value = MAX;
        sparse_table->table[0][i].node[1].index_in_arr = MAX;
    }

    for (int k = 1; k < sparse_table->log_size; ++k) 
    {
        for (int i = 0; i < sparse_table->array_size - (1 << k) + 1; ++i) 
        {
            Pair two_minimums[2] = {};

            find_two_minimums(&sparse_table->table[k - 1][i], &sparse_table->table[k - 1][i + (1 << (k - 1))], two_minimums); // ищет 2 минимума из 2 отрезков (у каждого тоже есть 2 минимума)

            sparse_table->table[k][i].node[0] = two_minimums[0];
            sparse_table->table[k][i].node[1] = two_minimums[1];
        }
    }
}

int get_second_min_in_segment(Sparse_Table* sparse_table, int left, int right) 
{
    int len = right - left + 1;

    // int needed_hight = ((int) log2((double) len)) + 2;
     int needed_hight = 31 - __builtin_clz(len);

    Pair res[2] = {};
    find_two_minimums(&sparse_table->table[needed_hight][left], &sparse_table->table[needed_hight][right - (1 << needed_hight) + 1], res);

    return res[1].value;
}



int cmp_pairs(const void* a, const void* b) 
{
    Pair* pairA = (Pair*) a;
    Pair* pairB = (Pair*) b;

    if (pairA->value != pairB->value) return pairA->value - pairB->value; // сортировка по значению
    return pairA->index_in_arr - pairB->index_in_arr; // если = то по индексу
}
