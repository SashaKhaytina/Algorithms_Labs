#include "merge_sort.h"

#include <malloc.h>


void merge(int* base_array, int* arr1, size_t n1, int* arr2, size_t n2);


void merge_recursive_sort(int* num_array, size_t arr_size)
{
    size_t mid = arr_size / 2;
    if (mid == 0) return;

    int* left = num_array;
    int* right = num_array + mid;

    merge_recursive_sort(left, mid);
    merge_recursive_sort(right, arr_size - mid);

    merge(num_array, left, mid, right, arr_size - mid);
}


void merge_iterative_sort(int* num_array, size_t arr_size)
{
    for (size_t size_subarr = 1; size_subarr < arr_size; size_subarr *= 2)
    {
        for (size_t left = 0; left < arr_size; left += 2 * size_subarr)
        {
            size_t arr_size1 = size_subarr;
            if (arr_size1 + left > arr_size) arr_size1 = arr_size - left;

            size_t right = left + arr_size1;
            size_t arr_size2 = size_subarr;
            if (arr_size2 + right > arr_size) arr_size2 = arr_size - right;

            merge(num_array + left, num_array + left, arr_size1, num_array + right, arr_size2);
        }
    }
}


void merge(int* base_array, int* arr1, size_t arr_size1, int* arr2, size_t arr_size2)
{
    size_t pointer1 = 0;
    size_t pointer2 = 0;
    size_t counter = 0;

    int* sorted_array = (int*) calloc(arr_size1 + arr_size2, sizeof(int));

    while (pointer1 < arr_size1 || pointer2 < arr_size2)
    {
        if (pointer1 == arr_size1) sorted_array[counter++] = arr2[pointer2++];
        else if (pointer2 == arr_size2) sorted_array[counter++] = arr1[pointer1++];

        else if (arr1[pointer1] < arr2[pointer2]) sorted_array[counter++] = arr1[pointer1++];
        else sorted_array[counter++] = arr2[pointer2++];
    }


    for (size_t i = 0; i < arr_size1 + arr_size2; i++)
    {
        base_array[i] = sorted_array[i];
    }
    free(sorted_array);
}