#include <stdio.h>

#include "Check_tests/testing.h"

#include "Sorts/quadratic_sorts/bubble_sort.h"
#include "Sorts/quadratic_sorts/insertion_sort.h"
#include "Sorts/quadratic_sorts/selection_sort.h"
#include "Sorts/quadratic_sorts/shell_sort.h"
#include "Sorts/Merge_sort/merge_sort.h"
#include "Sorts/Quick_sort/quick_sort.h"



void print_arr(int* num_array, size_t n);


int main()
{   
    char str1[] = "Generation_tests/TESTS";
    char str2[] = "Program_return_tests";


    test_sort(str1, str2, quick_hoar_sort, 1, 10, 2);
}


void print_arr(int* num_array, size_t n)
{
    for (size_t i = 0; i < n; i++)
    {
        printf("%d ", num_array[i]);
    }
    printf("\n");
}