#include "selection_sort.h"

void swap_(int* num_array, size_t ind_1, size_t ind_2);


void selection_sort(int* num_array, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        size_t min_ind = i;
        size_t cur_min = num_array[min_ind];

        for (int j = i + 1; j < arr_size; j++)
        {
            if (num_array[j] < cur_min)
            {
                min_ind = j;
                cur_min = num_array[j];
            }
        }

        if (min_ind != i) swap_(num_array, i, min_ind);
    }
}

void swap_(int* num_array, size_t ind_1, size_t ind_2)
{
    int temp = num_array[ind_1];
    num_array[ind_1] = num_array[ind_2];
    num_array[ind_2] = temp;
}
