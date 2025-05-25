#include "sparce_table_work.h"

#include "../Sparce_Table_longer/sparce_table_longer.h"
#include "../Sparce_Table_higher/sparce_table_higher.h"

double do_commands__sparce_table_longer(Elem_t* num_arr, int num_arr_size, Segment* seg_arr, int seg_arr_size)
{
    Sparse_Table_Longer* sparce_table = sparse_table_longer__build(num_arr, num_arr_size);
    #ifdef DEBUG
    sparse_table_longer__dump(sparce_table);
    #endif

    double average_time = 0;
    COUNT_TIME
    ( 
    for (int i = 0; i < seg_arr_size; i++)
    {
        Elem_t num = sparse_table_longer__get_min_in_segment(sparce_table, seg_arr[i].start, seg_arr[i].finish);
        #ifdef DEBUG
        printf("%d - answer in segment [%d ; %d]\n", num, seg_arr[i].start, seg_arr[i].finish);
        #endif
    }
    )

    sparse_table_longer__free(sparce_table);

    return average_time;

}



double do_commands__sparce_table_higher(Elem_t* num_arr, int num_arr_size, Segment* seg_arr, int seg_arr_size)
{
    Sparse_Table_Higher* sparce_table = sparse_table_higher__build(num_arr, num_arr_size);
    #ifdef DEBUG
    sparse_table_higher__dump(sparce_table);
    #endif
    double average_time = 0;
    COUNT_TIME
    ( 
    for (int i = 0; i < seg_arr_size; i++)
    {
        Elem_t num = sparse_table_higher__get_min_in_segment(sparce_table, seg_arr[i].start, seg_arr[i].finish);
        #ifdef DEBUG
        printf("%d - answer in segment [%d ; %d]\n", num, seg_arr[i].start, seg_arr[i].finish);
        #endif
    }
    )

    sparse_table_higher__free(sparce_table);

    return average_time;

}