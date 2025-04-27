#include "quick_sort.h"

#include <stdbool.h>


void quick_lomuto_sort_recur(int* arr, int low, int high, int (*partition)(int*, int, int));
int lomuto_partition(int* arr, int low, int high);

void quick_hoar_sort_recur(int* arr, int low, int high, int (*partition)(int*, int, int));
int hoar_partition(int* arr, int low, int high);



void quick_lomuto_sort(int* arr, size_t arr_size)
{
    quick_lomuto_sort_recur(arr, 0, arr_size - 1, lomuto_partition);
}

void quick_lomuto_sort_recur(int* arr, int low, int high, int (*partition)(int*, int, int))
{
    if (low < high)
    {
        int ind_part = partition(arr, low, high);
        if (ind_part > low)  quick_lomuto_sort_recur(arr, low, ind_part - 1, partition);
        if (ind_part < high) quick_lomuto_sort_recur(arr, ind_part + 1, high, partition);
    }
}

int lomuto_partition(int* arr, int low, int high) 
{
    int pivot = arr[(low + high) / 2];

    arr[(low + high) / 2] = arr[high];
    arr[high] = pivot;

    int left = low - 1;

    for (int right = low; right < high; right++)
    {
        if (arr[right] < pivot)
        {
            left++; 

            int t = arr[right];
            arr[right] = arr[left];
            arr[left] = t;

        }
    }

    left++;

    int t = arr[left];
    arr[left] = arr[high];
    arr[high] = t;

    return left;
}
// ----------------------------------------------------------------------------------------------------------




void quick_hoar_sort(int* arr, size_t arr_size)
{
    quick_hoar_sort_recur(arr, 0, arr_size - 1, hoar_partition);
}

void quick_hoar_sort_recur(int* arr, int low, int high, int (*partition)(int*, int, int))
{
    if (low < high)
    {
        int ind_part = partition(arr, low, high);
        quick_hoar_sort_recur(arr, low, ind_part, partition);
        if (ind_part < high) quick_hoar_sort_recur(arr, ind_part + 1, high, partition);
    }
}

int hoar_partition(int* arr, int low, int high)
{
    int pivot = arr[(low + high) / 2];

    
    while (true) 
    {
        while (arr[low] < pivot) low++;
        
        while (arr[high] > pivot) high--;
        
        if (low >= high) return high;
        
        int t = arr[low];
        arr[low] = arr[high];
        arr[high] = t;

        low++;
        high--;
    }


}