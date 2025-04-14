#include "strings_testing_hash_table.h"

#include <stdlib.h>

const int SIZE_RANDOM_WORD = 20;
const size_t COUNT_TESTS_CYCLE = 1;


TestStatus str_test_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    status |= str_fill_hash_table(hash_table, words);
    CHECK_STATUS_OK(status)


    #ifdef DEBUG
    dump_hash_table(hash_table);
    #endif

    // for (size_t i = 0; i < COUNT_TESTS_CYCLE; i++)
    // {
    //     status |= str_find_random_words_in_hash_table(hash_table);
    //     CHECK_STATUS_OK(status)
    // }

    status |= str_find_random_words_in_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    return status;

    #else
    return ERROR_MDOE;
    #endif
}



TestStatus str_fill_hash_table(Hash_Table* hash_table, Text* words)
{
    // #ifndef TESTNUM
    // CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    // TestStatus status = OK;


    // // MEMORY!
    // for (int i = 0; i < 100; i++)
    // {
    //     CHECK_STATUS_OK(status)

    //     int size_word = 5 + rand() % 16;
    //     if (size_word > SIZE_RANDOM_WORD) size_word = SIZE_RANDOM_WORD;

    //     char* element = (char*) calloc(size_word, sizeof(char));

    //     for (int j = 0; j < size_word; j++)
    //     {
    //         int letter = 97 + rand() % 26;
    //         element[j] = letter;
    //     }
    //     printf("%s - new str\n", element);


    //     status |= hash_table_insert(hash_table, element);
    // }

    // return status;

    // #else
    // return ERROR_MDOE;
    // #endif

    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < words->count_words; i++)
    {
        CHECK_STATUS_OK(status)
        status |= hash_table_insert(hash_table, words->words[i]);
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}





TestStatus str_find_random_words_in_hash_table(Hash_Table* hash_table)
{
    #ifndef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;


    for (int i = 0; i < 100; i++)
    {
        int size_word = 5 + rand() % 16;
        char element[SIZE_RANDOM_WORD + 1] = {};
        if (size_word > SIZE_RANDOM_WORD) size_word = SIZE_RANDOM_WORD;


        for (int j = 0; j < size_word; j++)
        {
            int letter = 97 + rand() % 26;
            element[j] = letter;
        }

        if (hash_table_find(hash_table, element)) 
        {
            #ifdef DEBUG
            PRINTF_GREEN("There is element - "); printf("%s", element); PRINTF_GREEN(" in hash table\n");
            #endif
        }
        else 
        {
            #ifdef DEBUG
            PRINTF_RED("There is no element - "); printf("%s", element); PRINTF_RED(" in hash table\n");
            #endif
        }
    }

    return status;

    #else
    return ERROR_MDOE;
    #endif
}
