#ifndef TESTING_SORTS_H
#define TESTING_SORTS_H

#include <stdio.h>


enum FileType
{
    IN, 
    OUT
};


double* test_sort(char* tests_in_way, char* tests_output_way, void (*sort)(int* array, size_t size), int from, int to, int step);

#endif
