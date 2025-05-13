#include "insertion_sort.h"

void insertion_sort(int* num_array, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        int current_elem = num_array[i];

        size_t current_ind =  i - 1;
        while (current_ind >= 0 && num_array[current_ind] > current_elem)
        {
            num_array[current_ind + 1] = num_array[current_ind];
            current_ind--;
        }
        
        num_array[current_ind + 1] = current_elem;
    }
}