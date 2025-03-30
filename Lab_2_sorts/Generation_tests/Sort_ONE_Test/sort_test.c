#include "sort_test.h"

#include <stdint.h>
#include <stdlib.h>

int compare(const void* a, const void* b);


void sort_test(FILE* input, int size)
{
    uint32_t array[MAX_BUFFER_SIZE] = {};
    
    for (int i = 0; i < size; i++)
    {
        uint32_t num = 0;
        fscanf(input, "%d", &num);
        // printf("%d - num read\n", num);
        array[i] = num;
    }

    qsort(array, size, sizeof(uint32_t), compare);

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", array[i]);
    }
}


int compare(const void* a, const void* b)
{
    return (*((uint32_t*)a) - *((uint32_t*)b));
}


int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    int size = atoi(argv[2]);

    sort_test(input, size);
    
    fclose(input);
}