#include "num_testing_hash_table.h"

#include <stdlib.h>


#ifdef TESTNUM
const int    ELEMENTS_COUNT = 100;
const Elem_t MAX_ELEM       = 100;
#endif

#ifdef TEST_HASH_FUNCTION
TestStatus num_test_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table, words)
    TestStatus status = OK;

    status |= num_fill_hash_table(hash_table, words);
    CHECK_STATUS_OK(status)
    
    #ifdef DEBUG
    dump_hash_table(hash_table);
    #endif

    status |= num_find_random_numbers_in_hash_table(hash_table);
    CHECK_STATUS_OK(status)

    return status;

    #else
    return ERROR_MODE;
    #endif
}



TestStatus num_fill_hash_table(Hash_Table* hash_table, Text* words)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    for (int i = 0; i < words->count_words; i++)
    {
        CHECK_STATUS_OK(status)
        status = hash_table_insert(hash_table, words->words[i]);
    }

    return status;

    #else
    return ERROR_MODE;
    #endif
}



TestStatus num_find_random_numbers_in_hash_table(Hash_Table* hash_table)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        int element = rand() % (MAX_ELEM + 1);
        if (hash_table_find(hash_table, element)) 
        {
            #ifdef DEBUG
            PRINTF_GREEN("There is element - "); printf("%d", element); PRINTF_GREEN(" in hash table\n");
            #endif
        }
        else 
        {
            #ifdef DEBUG
            PRINTF_RED("There is no element - "); printf("%d", element); PRINTF_RED(" in hash table\n");
            #endif
        }
    }

    return status;

    #else
    return ERROR_MODE;
    #endif
}



#elif TEST_HASH_TABLE_WITH_OPEN_ADDR

TestStatus num_test_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr, words)
    TestStatus status = OK;

    status |= num_fill_hash_table_open_addr(hash_table_open_addr, words);
    CHECK_STATUS_OK(status)
    
    #ifdef DEBUG
    dump_hash_table_open_addr(hash_table_open_addr);
    #endif

    status |= num_find_random_numbers_in_hash_table_open_addr(hash_table_open_addr);
    CHECK_STATUS_OK(status)

    return status;

    #else
    return ERROR_MODE;
    #endif
}



TestStatus num_fill_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    for (int i = 0; i < words->count_words; i++)
    {
        CHECK_STATUS_OK(status)
        status = hash_table_open_addr_insert(hash_table_open_addr, words->words[i]);
    }

    return status;

    #else
    return ERROR_MODE;
    #endif
}


TestStatus num_find_random_numbers_in_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr)
{
    #ifdef TESTNUM
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    for (int i = 0; i < ELEMENTS_COUNT; i++)
    {
        int element = rand() % (MAX_ELEM + 1);
        if (hash_table_open_addr_find(hash_table_open_addr, element)) 
        {
            #ifdef DEBUG
            PRINTF_GREEN("There is element - "); printf("%d", element); PRINTF_GREEN(" in hash table\n");
            #endif
        }
        else 
        {
            #ifdef DEBUG
            PRINTF_RED("There is no element - "); printf("%d", element); PRINTF_RED(" in hash table\n");
            #endif
        }
    }

    return status;

    #else
    return ERROR_MODE;
    #endif
}


#endif
