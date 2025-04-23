#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "hash_table/hash_table.h"
#include "hash_table_open_addressing/hash_table_open_addr.h"

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

    // printf("I done. I am molodec :=( \n");
    srand(time(NULL));

    #ifdef TEST_HASH_FUNCTION
    PRINTF_RED("TEST_HASH_FUNCTION\n");
    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);

    #ifdef TESTNUM
    PRINTF_RED("TESTNUM\n");
    num_test_hash_table(hash_table, words);
    #else
    PRINTF_RED("TEST_HASH_FUNCTION\n");
    PRINTF_RED("STRINGS (no define)\n");
    str_test_hash_table(hash_table, words);
    #endif

    hash_table_dtor(hash_table);

    #elif TEST_HASH_TABLE_WITH_OPEN_ADDR
    PRINTF_RED("TEST_HASH_TABLE_WITH_OPEN_ADDR\n");

    Hash_Table_Open_Addr* hash_table_open_addr = hash_table_open_addr_ctor(HASH_TABLE_SIZE);

    num_test_hash_table_open_addr(hash_table_open_addr, words);

    hash_table_open_addr_dtor(hash_table_open_addr);


    #endif
}