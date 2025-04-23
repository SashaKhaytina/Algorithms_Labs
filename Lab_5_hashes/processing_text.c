#include <stdio.h>

#include <stdlib.h>
#include <ctype.h>
#include <malloc.h>
#include <time.h>

const char*  RETURN_FILE_NAME  = "processed_file.txt";
const int    SIZE_RANDOM_WORD  = 20;
// const size_t COUNT_TESTS_CYCLE = 1000000;
const size_t COUNT_TESTS_CYCLE = 100;
const int    MAX_RAND          = 100;

void create_new_text(FILE* file);


int main(int argc, char* argv[])
{

    FILE* output_file = fopen(RETURN_FILE_NAME, "w");

    srand(time(NULL));
    create_new_text(output_file);

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
