#include <stdio.h>
#include <stdlib.h>
#include <time.h>


const int MAX_RAND                  = 100000;
const int TEST_SIZE                 = 1000000;
const int NUM_OPERS                 = 1000000;
const char* NAME_FILE_OF_NUMBERS    = "RMQ_test.txt"; 
const char* NAME_FILE_OF_OPERATIONS = "RMQ_operations.txt";

void generation_test(FILE* output_file, int size, int max_num);
void generation_operations(FILE* output_file, int size, int max_num);


int main()
{
    FILE* output_file = fopen(NAME_FILE_OF_NUMBERS, "w");
    generation_test(output_file, TEST_SIZE, MAX_RAND);
    fclose(output_file);

    FILE* output_file_opers = fopen(NAME_FILE_OF_OPERATIONS, "w");
    generation_operations(output_file_opers, NUM_OPERS, TEST_SIZE);
    fclose(output_file_opers);
}




void generation_test(FILE* output_file, int size, int max_num)
{
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
        int num = 1 + rand() % max_num;
        fprintf(output_file, "%d\n", num);
    }
}


void generation_operations(FILE* output_file, int size, int max_num)
{
    srand(time(NULL));

    for (int i = 0; i < size; i++)
    {
int num1 = 1 + rand() % (max_num - 1);  
        int num2 = num1 + 1 + rand() % (max_num - num1);  
        fprintf(output_file, "%d %d\n", num1, num2);
    }
}

