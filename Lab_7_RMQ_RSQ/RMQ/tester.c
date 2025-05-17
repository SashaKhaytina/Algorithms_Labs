#include "tester.h"

#include <assert.h>
#include <malloc.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#include "Sparce_Table_Work/sparce_table_work.h"


const int   TEST_SIZE     = 1000000;
const int   MAX_TEST_SIZE = 1000000;

const char* NAME_FILE_OF_NUMBERS_RMQ    = "TEST/RMQ_test.txt"; 
const char* NAME_FILE_OF_OPERATIONS_RMQ = "TEST/RMQ_operations.txt";



int* get_test(FILE* f_input, int test_size);
void write_test_answer_and_compare(FILE* f_out, FILE* f_cmp, int* num_array, int test_size);
void fill_num_array(int* num_array, int test_size, char* text, int len_text);


Segment* get_segments(FILE* f_input, int test_size);
void fill_segment_array(Segment* segment_array, int test_size, char* text, int len_text);

size_t size_file(FILE* file);



void testing()
{
    double average_time = 0;

    // READ
    FILE* f_input = fopen(NAME_FILE_OF_NUMBERS_RMQ, "r");
    assert(f_input);
    int* num_array = get_test(f_input, TEST_SIZE);
    fclose(f_input);

    #ifdef DEBUG
    for (int i = 0; i < TEST_SIZE; i++)
    {
        printf("%d\n", num_array[i]);
    }
    printf("\n\n");
    #endif
    

    FILE* f_input_seg = fopen(NAME_FILE_OF_OPERATIONS_RMQ, "r");
    assert(f_input_seg);
    Segment* seg_array = get_segments(f_input_seg, TEST_SIZE);
    fclose(f_input_seg);

    #ifdef DEBUG
    PRINTF_GREEN("I read all data!!!!!\n");
    #endif
    // TEST
    double time__sparce_table_longer = do_commands__sparce_table_longer(num_array, TEST_SIZE, seg_array, TEST_SIZE);
    #ifdef DEBUG
    printf("\n-----------------------\n\n");
    #endif
    double time__sparce_table_higher = do_commands__sparce_table_higher(num_array, TEST_SIZE, seg_array, TEST_SIZE);

    PRINTF_CYAN("TEST time sparce table LONGER: "); printf("%g\n", time__sparce_table_longer);
    PRINTF_CYAN("TEST time sparce table HIGHER: "); printf("%g\n", time__sparce_table_higher);

    free(num_array);
    free(seg_array);
}


int* get_test(FILE* f_input, int test_size)
{

    if (test_size > MAX_TEST_SIZE) return NULL;

    int* num_array = (int*) calloc(test_size, sizeof(int));
    assert(num_array);

    // read text
    size_t len_text = size_file(f_input);
    char* text = (char*) calloc(len_text + 1, sizeof(char));
    size_t count_symbol = fread(text, sizeof(char), len_text, f_input);
    assert(len_text == count_symbol);

    fill_num_array(num_array, test_size, text, len_text);

    free(text);

    return num_array;

}


void fill_num_array(int* num_array, int test_size, char* text, int len_text)
{
    int counter = 0;
    int current_num = 0;
    for (int i = 0; i < len_text; i++)
    {
        if (text[i] == '\n')
        {
            if (counter + 1 > test_size) return;

            num_array[counter] = current_num;
            counter++;
            current_num = 0;

            continue;
        }
        if (text[i] == '\0') return;

        current_num = current_num * 10 + (text[i] - 48);

    }
}






Segment* get_segments(FILE* f_input, int test_size)
{

    if (test_size > MAX_TEST_SIZE) return NULL;

    Segment* segment_array = (Segment*) calloc(test_size, sizeof(Segment));
    assert(segment_array);

    // read text
    size_t len_text = size_file(f_input);
    char* text = (char*) calloc(len_text + 1, sizeof(char));
    size_t count_symbol = fread(text, sizeof(char), len_text, f_input);
    assert(len_text == count_symbol);

    fill_segment_array(segment_array, test_size, text, len_text);

    free(text);

    return segment_array;

}


void fill_segment_array(Segment* segment_array, int test_size, char* text, int len_text)
{
    int counter = 0;
    int current_num_1 = 0;
    int current_num_2 = 0;
    for (int i = 0; i < len_text; i++)
    {
        if (text[i] == '\n')
        {
            if (counter + 1 > test_size) return;

            segment_array[counter].start  = current_num_1;
            segment_array[counter].finish = current_num_2;
            counter++;

            current_num_1 = 0; 
            current_num_2 = 0;

            continue;
        }

        if (text[i] == ' ')
        {
            current_num_1 = current_num_2;
            current_num_2 = 0;

            continue;
        }

        if (text[i] == '\0') return;

        current_num_2 = current_num_2 * 10 + (text[i] - 48);

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