#include "quick_sort.h"

#include <stdbool.h>


void quick_lomuto_sort_recur(int* num_array, int low, int high, int (*partition)(int*, int, int));
int lomuto_partition(int* num_array, int low, int high);

void quick_hoar_sort_recur(int* num_array, int low, int high, int (*partition)(int*, int, int));
int hoar_partition(int* num_array, int low, int high);



void quick_lomuto_sort(int* num_array, size_t arr_size)
{
    quick_lomuto_sort_recur(num_array, 0, arr_size - 1, lomuto_partition);
}

void quick_lomuto_sort_recur(int* num_array, int low, int high, int (*partition)(int*, int, int))
{
    if (low < high)
    {
        int ind_part = partition(num_array, low, high);
        if (ind_part > low)  quick_lomuto_sort_recur(num_array, low, ind_part - 1, partition);
        if (ind_part < high) quick_lomuto_sort_recur(num_array, ind_part + 1, high, partition);
    }
}

int lomuto_partition(int* num_array, int low, int high) 
{
    int pivot = num_array[(low + high) / 2];

    num_array[(low + high) / 2] = num_array[high];
    num_array[high] = pivot;

    int left = low - 1;

    for (int right = low; right < high; right++)
    {
        if (num_array[right] < pivot)
        {
            left++; 

            int t = num_array[right];
            num_array[right] = num_array[left];
            num_array[left] = t;

        }
    }

    left++;

    int t = num_array[left];
    num_array[left] = num_array[high];
    num_array[high] = t;

    return left;
}
// ----------------------------------------------------------------------------------------------------------




void quick_hoar_sort(int* num_array, size_t arr_size)
{
    quick_hoar_sort_recur(num_array, 0, arr_size - 1, hoar_partition);
}

void quick_hoar_sort_recur(int* num_array, int low, int high, int (*partition)(int*, int, int))
{
    if (low < high)
    {
        int ind_part = partition(num_array, low, high);
        quick_hoar_sort_recur(num_array, low, ind_part, partition);
        if (ind_part < high) quick_hoar_sort_recur(num_array, ind_part + 1, high, partition);
    }
}

int hoar_partition(int* num_array, int low, int high)
{
    int pivot = num_array[(low + high) / 2];

    
    while (true) 
    {
        while (num_array[low] < pivot) low++;
        
        while (num_array[high] > pivot) high--;
        
        if (low >= high) return high;
        
        int t = num_array[low];
        num_array[low] = num_array[high];
        num_array[high] = t;

        low++;
        high--;
    }


}