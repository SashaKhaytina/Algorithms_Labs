#include "testing.h"

#include <string.h>


int* get_test(FILE* f_input);
void write_test_answer();



double* test_sort(char* tests_in_way, char* tests_output_way, void (*sort)(int* arr, size_t size), int from, int to, int step)
{
    char* file_in[MAX_WAY_SIZE] = {};
    strcpy(file_in, tests_in_way);


    for (int test_size = from; test_size < to + 1; test_size += step)
    {
        for (int j = 0; j < 5; j++)
        {
            char* file_name[30] = {};
            strcat(file_name, "/"); strcat(file_name, itoa(test_size)); strcat(file_name, "_"); strcat(file_name, itoa(j)); strcat(file_name, ".txt");// /test_size_j.txt
            strcat(file_in, file_name);

            FILE* f_input = fopen(file_in, "r");

            int* array = get_test(f_input);

            // TIME!
            sort(array, test_size);
            // put time in times[]

            write_test_answer(); // in file

            



        }
    }
}


int* get_test(FILE* f_input)
{
    /* calloc
    fread -> int*/
}

void write_test_answer()
{

}