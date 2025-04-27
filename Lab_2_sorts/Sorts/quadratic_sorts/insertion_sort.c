#include "insertion_sort.h"

void insertion_sort(int* arr, size_t arr_size)
{
    for (size_t i = 0; i < arr_size; i++)
    {
        int current_elem = arr[i];

        size_t current_ind =  i - 1;
        while (current_ind >= 0 && arr[current_ind] > current_elem)
        {
            arr[current_ind + 1] = arr[current_ind];
            current_ind--;
        }
        
        arr[current_ind + 1] = current_elem;
    }
}