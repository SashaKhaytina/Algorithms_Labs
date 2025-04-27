#include "sort_test.h"

#include <stdlib.h>
#include <stdint.h>

int compare(const void* elem1, const void* elem2);


void sort_test(FILE* input, int size)
{
    uint32_t array[MAX_BUFFER_SIZE] = {};
    
    for (int i = 0; i < size; i++)
    {
        uint32_t num = 0;
        fscanf(input, "%d", &num);
        array[i] = num;
    }

    qsort(array, size, sizeof(uint32_t), compare);

    for (int i = 0; i < size; i++)
    {
        printf("%d\n", array[i]);
    }
}


int compare(const void* elem1, const void* elem2)
{
    return (*((uint32_t*)elem1) - *((uint32_t*)elem2));
}


int main(int argc, char* argv[])
{
    FILE* input = fopen(argv[1], "r");
    int size = atoi(argv[2]);

    sort_test(input, size);
    
    fclose(input);
}