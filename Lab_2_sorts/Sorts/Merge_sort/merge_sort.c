#include "merge_sort.h"

#include <malloc.h>


void merge(int* base_array, int* arr1, size_t n1, int* arr2, size_t n2);


void merge_recursive_sort(int* arr, size_t n)
{
    size_t mid = n / 2;
    if (mid == 0) return;

    int* left = arr;
    int* right = arr + mid;

    merge_recursive_sort(left, mid);
    merge_recursive_sort(right, n - mid);

    merge(arr, left, mid, right, n - mid);
}


void merge_iterative_sort(int* arr, size_t n)
{
    for (size_t size_subarr = 1; size_subarr < n; size_subarr *= 2)
    {
        for (size_t left = 0; left < n; left += 2 * size_subarr)
        {
            size_t n1 = size_subarr;
            if (n1 + left > n) n1 = n - left;

            size_t right = left + n1;
            size_t n2 = size_subarr;
            if (n2 + right > n) n2 = n - right;

            merge(arr + left, arr + left, n1, arr + right, n2);
        }
    }
}


void merge(int* base_array, int* arr1, size_t n1, int* arr2, size_t n2)
{
    size_t pointer1 = 0;
    size_t pointer2 = 0;
    size_t counter = 0;

    int* sorted_array = (int*) calloc(n1 + n2, sizeof(int));

    while (pointer1 < n1 || pointer2 < n2)
    {
        if (pointer1 == n1) sorted_array[counter++] = arr2[pointer2++];
        else if (pointer2 == n2) sorted_array[counter++] = arr1[pointer1++];

        else if (arr1[pointer1] < arr2[pointer2]) sorted_array[counter++] = arr1[pointer1++];
        else sorted_array[counter++] = arr2[pointer2++];
    }


    for (size_t i = 0; i < n1 + n2; i++)
    {
        base_array[i] = sorted_array[i];
    }
    free(sorted_array);
}