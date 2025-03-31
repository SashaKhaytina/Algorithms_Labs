#include "bubble_sort.h"

void swap(int* arr, size_t ind_1, size_t ind_2);


void bouble_sort(int* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        int difference = 0;
        for (size_t j = 0; j < n - i - 1; j++)
        {
            if (arr[j] > arr[j + 1]) 
            {
                swap(arr, j, j + 1);
                difference = 1;
            }
        }
        if (difference == 0) break;
    }
}

void swap(int* arr, size_t ind_1, size_t ind_2)
{
    int temp = arr[ind_1];
    arr[ind_1] = arr[ind_2];
    arr[ind_2] = temp;
}
