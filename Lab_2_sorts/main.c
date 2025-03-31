#include <stdio.h>

#include "Check_tests/testing.h"

#include "Sorts/quadratic_sorts/bubble_sort.h"
#include "Sorts/quadratic_sorts/insertion_sort.h"
#include "Sorts/quadratic_sorts/selection_sort.h"
#include "Sorts/quadratic_sorts/shell_sort.h"
#include "Sorts/Merge_sort/merge_sort.h"
#include "Sorts/Quick_sort/quick_sort.h"



void print_arr(int* arr, size_t n);


int main()
{
    // int arr[] = {4, 7, 2, 11, 89, 3, 1, 2};
    // size_t n = 8;

    // print_arr(arr, n);

    // // bouble_sort(arr, n);
    // // insertion_sort(arr, n);
    // // selection_sort(arr, n);
    // shell_sort(arr, n);
    // quick_lomuto_sort(arr, n);
    
    // print_arr(arr, n);
    
    char str1[] = "Generation_tests/TESTS";
    char str2[] = "Program_return_tests";


    test_sort(str1, str2, quick_hoar_sort, 1, 1000000, 10000);


}


void print_arr(int* arr, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    printf("\n");
}