#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table/hash_table.h"
#include "testing/num_testing_hash_table.h"
#include "testing/strings_testing_hash_table.h"
#include "working_with_text/working_with_text.h"

const int   HASH_TABLE_SIZE = 50;
const char* PROCESSED_FILE_NAME = "processed_file.txt";



int main()
{
    printf("Something\n");

    FILE* file = fopen(PROCESSED_FILE_NAME, "r");
    Text* words = get_elements(file);

    printf("I done. I am molodec :=( \n");

    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);

    #ifdef TESTNUM
    num_test_hash_table(hash_table);
    #else
    str_test_hash_table(hash_table, words);
    #endif

    hash_table_dtor(hash_table);
}