#include "shell_sort.h"

void shell_sort(int* arr, size_t arr_size)
{
    int step_k = 1;
    while (step_k < arr_size / 3) step_k = step_k * 3 + 1;  // последовательность Кнута

    
    while (step_k > 0)
    {
        for (size_t i = step_k; i < arr_size; i += step_k)
        {
            int current_elem = arr[i];
            size_t current_ind =  i;

            while (current_ind >= step_k && arr[current_ind - step_k] > current_elem)
            {
                arr[current_ind] = arr[current_ind - step_k];
                current_ind -= step_k;
            }
            
            arr[current_ind] = current_elem;
        }
        
        step_k /= 3;
    }
}