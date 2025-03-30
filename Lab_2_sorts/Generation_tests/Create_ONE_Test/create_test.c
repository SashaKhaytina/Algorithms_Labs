#include "create_test.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generation_test(int size, uint32_t max_num)
{
    for (int i = 0; i < size; i++)
    {
        uint32_t num = rand() % (max_num + 1);
        printf("%d\n", num);

    }
}


int main(int argc, char* argv[])
{
    srand(atoi(argv[2]));
    int size = atoi(argv[1]);
    // uint32_t max_num = atoi(argv[2]);
    generation_test(size, MAX_RAND);
}