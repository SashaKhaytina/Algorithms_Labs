#include "testing.h"

#include <assert.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include "../timer.h"

const int   MAX_WAY_SIZE  = 200;
const int   MAX_TEST_SIZE = 1000000;
const char* GRAPH_TABLE   = "Graphic/quick_hoar_sort.txt";



int* get_test(FILE* f_input, int test_size);
void write_test_answer_and_compare(FILE* f_out, FILE* f_cmp, int* array, int test_size);
char* join_file_name(char* file_in, int test_size, int num_test, enum FileType type);
void fill_num_array(int* array, int test_size, char* text, int len_text);
size_t size_file(FILE* file);




double* test_sort(char* tests_in_way, char* tests_output_way, void (*sort)(int* arr, size_t size), int from, int to, int step)
{
    double* time_arr = (double*) calloc((to - from + 1) / step + 1, sizeof(double));
    int size_time_arr = 0;
    
    for (int test_size = from; test_size < to + 1; test_size += step)
    {
        double average_time = 0;
        for (int j = 1; j <= 5; j++)
        {
            // READ
            char* file_in = join_file_name(tests_in_way, test_size, j, IN);
            FILE* f_input = fopen(file_in, "r");
            assert(f_input);


            int* array = get_test(f_input, test_size);
            
            fclose(f_input);
            free(file_in);


            // TEST
            COUNT_TIME(sort(array, test_size);)


            // WRITE
            char* file_out =    join_file_name(tests_output_way, test_size, j, OUT);
            char* file_in_cmp = join_file_name(tests_in_way, test_size, j, OUT);
            FILE* f_out = fopen(file_out, "w");
            FILE* f_cmp = fopen(file_in_cmp, "r");

            write_test_answer_and_compare(f_out, f_cmp, array, test_size); 
            
            fclose(f_out);
            fclose(f_cmp);
            free(file_out);
            free(file_in_cmp);
            free(array);

        }
        time_arr[size_time_arr++] = average_time / 5;
    }
    FILE* graph_file = fopen(GRAPH_TABLE, "w");
    assert(graph_file);
    print_test_time_in_file(graph_file, time_arr, from, to, step);
    fclose(graph_file);

    return time_arr;
}


int* get_test(FILE* f_input, int test_size)
{

    if (test_size > MAX_TEST_SIZE) return NULL;

    int* array = (int*) calloc(test_size, sizeof(int));
    assert(array);

    // read text
    size_t len_text = size_file(f_input);
    char* text = (char*) calloc(len_text + 1, sizeof(char));
    size_t count_symbol = fread(text, sizeof(char), len_text, f_input);
    assert(len_text == count_symbol);

    fill_num_array(array, test_size, text, len_text);

    free(text);

    return array;

}

void write_test_answer_and_compare(FILE* f_out, FILE* f_cmp, int* array, int test_size)
{
    for (int i = 0; i < test_size; i++)
    {
        int num = 0;
        fscanf(f_cmp, "%d", &num);
        assert(num == array[i]);
        fprintf(f_out, "%d\n", array[i]);
    }
}

char* join_file_name(char* file_in, int test_size, int num_test, enum FileType type)
{

    char* file_name = (char*)calloc(MAX_WAY_SIZE, sizeof(char));
    assert(file_name);

    snprintf(file_name, MAX_WAY_SIZE, "%s/%d_%d%s", 
             file_in, test_size, num_test, 
             (type == IN) ? ".in" : ".out");

    return file_name;
}


void fill_num_array(int* array, int test_size, char* text, int len_text)
{
    int counter = 0;
    int current_num = 0;
    for (int i = 0; i < len_text; i++)
    {
        if (text[i] == '\n')
        {
            if (counter + 1 > test_size) return;

            array[counter] = current_num;
            counter++;
            current_num = 0;

            continue;
        }
        if (text[i] == '\0') return;

        current_num = current_num * 10 + (text[i] - 48);

    }
}



size_t size_file(FILE* file)
{
    size_t size = 0;

    fseek(file, 0, SEEK_END);
    size = (size_t) ftell(file);
    fseek(file, 0, SEEK_SET);

    return size;
}


