#include "bubble_sort.h"

void swap(int* num_array, size_t ind_1, size_t ind_2);


void bouble_sort(int* num_array, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        int difference = 0;
        for (size_t j = 0; j < arr_size - i - 1; j++)
        {
            if (num_array[j] > num_array[j + 1]) 
            {
                swap(num_array, j, j + 1);
                difference = 1;
            }
        }
        if (difference == 0) break;
    }
}

void swap(int* num_array, size_t ind_1, size_t ind_2)
{
    int temp = num_array[ind_1];
    num_array[ind_1] = num_array[ind_2];
    num_array[ind_2] = temp;
}
