#include "shell_sort.h"

void shell_sort(int* num_array, size_t arr_size)
{
    int step_k = 1;
    while (step_k < arr_size / 3) step_k = step_k * 3 + 1;  // последовательность Кнута

    
    while (step_k > 0)
    {
        for (size_t i = step_k; i < arr_size; i += step_k)
        {
            int current_elem = num_array[i];
            size_t current_ind =  i;

            while (current_ind >= step_k && num_array[current_ind - step_k] > current_elem)
            {
                num_array[current_ind] = num_array[current_ind - step_k];
                current_ind -= step_k;
            }
            
            num_array[current_ind] = current_elem;
        }
        
        step_k /= 3;
    }
}