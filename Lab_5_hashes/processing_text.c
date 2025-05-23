#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>

const char*  RETURN_FILE_NAME  = "processed_file.txt";
const int    SIZE_RANDOM_WORD  = 20;
const size_t COUNT_TESTS_CYCLE = 1000000;
// const size_t COUNT_TESTS_CYCLE = 100;
const int    MAX_RAND          = 1000;

void create_new_text(FILE* file);


int main(int argc, char* argv[])
{
    FILE* output_file = fopen(RETURN_FILE_NAME, "w");
    if (output_file == NULL) 
    {
        PRINTF_RED("ERROR open output file\n");
        return 1;
    }

    srand(time(NULL));
    #ifndef RAND_OPERATION_LINE
    create_new_text(output_file);
    #else
    create_random_line_new_text(output_file);
    #endif

    return 0;


}



void create_new_text(FILE* file)
{
    #ifndef TESTNUM
    for (int i = 0; i < COUNT_TESTS_CYCLE; i++)
    {

        int size_word = 5 + rand() % 16;
        if (size_word > SIZE_RANDOM_WORD) size_word = SIZE_RANDOM_WORD;

        char* element = (char*) calloc(size_word, sizeof(char));

        for (int j = 0; j < size_word; j++)
        {
            int letter = 97 + rand() % 26;
            element[j] = letter;
        }
        fprintf(file, "%s\n", element);
    }

    return ;

    #else
    for (int i = 0; i < COUNT_TESTS_CYCLE; i++)
    {
        int element = rand() % (MAX_RAND + 1);

        fprintf(file, "%d\n", element);
    }

    return ;
    #endif
}


void create_random_line_new_text(FILE* file)
{
    for (int i = 0; i < COUNT_TESTS_CYCLE; i++)
    {
        int operation = rand() % 3;
        char op = 0;

        if (operation == 0) op = '+';
        else if (operation == 1) op = '-';
        else op = '?';
        int element = rand() % (MAX_RAND + 1);

        fprintf(file, "%c%d\n", op, element);
    }
}