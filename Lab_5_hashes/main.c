#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>

#include "hash_table/hash_table.h"
#include "hash_table_open_addressing/hash_table_open_addr.h"

#include "testing/num_testing_hash_table.h"
#include "testing/strings_testing_hash_table.h"
#include "working_with_text/working_with_text.h"

// const int   HASH_TABLE_SIZE = 2048;
const int   HASH_TABLE_SIZE = 2;

const char* PROCESSED_FILE_NAME = "processed_file.txt";


#ifdef TESTNUM

#ifdef TESTNUMMOD
const char* GRAPHIC_FILE = "hash_table_num_mod.txt";
#elif TESTNUMBIT
const char* GRAPHIC_FILE = "hash_table_num_bit.txt";
#else
const char* GRAPHIC_FILE = "hash_table_num_knyt.txt";
#endif

#else

#ifdef TESTSTRLEN
const char* GRAPHIC_FILE = "hash_table_str_len.txt";
#elif TESTSTRSUM
const char* GRAPHIC_FILE = "hash_table_str_sum.txt";
#elif TESTSTRPOLIN
const char* GRAPHIC_FILE = "hash_table_str_polin.txt";
#elif TESTSTRCRC32
const char* GRAPHIC_FILE = "hash_table_str_crc32.txt";
#elif TESTNUM
const char* GRAPHIC_FILE = "hash_table_num.txt";
#else
const char* GRAPHIC_FILE = "hash_table_graphic.txt";
#endif

#endif






int main()
{
    printf("Something\n");

    FILE* file = fopen(PROCESSED_FILE_NAME, "r");
    if (file == NULL) 
    {
        PRINTF_RED("ERROR open processed file\n");
        return ERROR_OPEN_FILE;
    }
    Text* words = get_elements(file);


    srand(time(NULL));
    double average_time = 0;

    #ifdef TEST_HASH_FUNCTION
    FILE* graphic_file = fopen(GRAPHIC_FILE, "w");
    if (graphic_file == NULL) 
    {
        PRINTF_RED("ERROR open graphic file\n");
        return ERROR_OPEN_FILE;
    }

    PRINTF_RED("TEST_HASH_FUNCTION\n");
    Hash_Table* hash_table = hash_table_ctor(HASH_TABLE_SIZE);

    #ifdef TESTNUM
    PRINTF_RED("TESTNUM\n");

    COUNT_TIME(num_test_hash_table(hash_table, words);)
    PRINTF_GREEN("TEST_NUM Time: "); printf("%f\n", average_time);

    graphic_dump_hash_table(graphic_file, hash_table);
    #else
    PRINTF_RED("TEST_HASH_FUNCTION\n");
    PRINTF_RED("STRINGS (no define)\n");

    COUNT_TIME(str_test_hash_table(hash_table, words);)
    PRINTF_GREEN("TEST_STR Time: "); printf("%f\n", average_time);

    graphic_dump_hash_table(graphic_file, hash_table);
    #endif

    hash_table_dtor(hash_table);
    fclose(file);
    fclose(graphic_file);

    #elif TEST_HASH_TABLE_WITH_OPEN_ADDR
    PRINTF_RED("TEST_HASH_TABLE_WITH_OPEN_ADDR\n");

    Hash_Table_Open_Addr* hash_table_open_addr = hash_table_open_addr_ctor(HASH_TABLE_SIZE);

    COUNT_TIME(num_test_hash_table_open_addr(hash_table_open_addr, words);)
    PRINTF_GREEN("TEST_OPEN_ADDR Time: "); printf("%f\n", average_time);

    hash_table_open_addr_dtor(hash_table_open_addr);


    #endif

    free(words->words);
    free(words);
}