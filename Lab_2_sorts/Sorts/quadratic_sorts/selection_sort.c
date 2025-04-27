#include "selection_sort.h"

void swap_(int* arr, size_t ind_1, size_t ind_2);


void selection_sort(int* arr, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        size_t min_ind = i;
        size_t cur_min = arr[min_ind];

        for (int j = i + 1; j < arr_size; j++)
        {
            if (arr[j] < cur_min)
            {
                min_ind = j;
                cur_min = arr[j];
            }
        }

        if (min_ind != i) swap_(arr, i, min_ind);
    }
}

void swap_(int* arr, size_t ind_1, size_t ind_2)
{
    int temp = arr[ind_1];
    arr[ind_1] = arr[ind_2];
    arr[ind_2] = temp;
}
