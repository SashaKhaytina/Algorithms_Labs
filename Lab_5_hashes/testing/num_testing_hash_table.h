#ifndef TESTING_HASH_TABLE_H
#define TESTING_HASH_TABLE_H

#include "../hash_table/hash_table.h"
#include "../hash_table_open_addressing/hash_table_open_addr.h"


// extern const int    ELEMENTS_COUNT = 100;
// extern const Elem_t MAX_ELEM       = 100;

// struct 
// {
//     HashTableType type;
//     #ifdef TEST_HASH_TABLE_WITH_OPEN_ADDR
//     TestStatus (*ht_insert)(Hash_Table_Open_Addr* hash_table, Elem_t element);
//     bool       (*ht_find)  (Hash_Table_Open_Addr* hash_table, Elem_t element);
//     #else
//     TestStatus (*ht_insert)(Hash_Table* hash_table, Elem_t element);
//     bool       (*ht_find)  (Hash_Table* hash_table, Elem_t element);
//     #endif

// } typedef Hash_Table_with_func;


#ifdef TEST_HASH_FUNCTION

/*!
 * \brief Print execution statistic to cmd
 *
 * DISCLAIMER: NEVER use this function (at home)
 *  
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus num_test_hash_table(Hash_Table* hash_table, Text* words);


/*!
 * \brief Fill Hash Table random nums from [0;100]
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus num_fill_hash_table(Hash_Table* hash_table, Text* words);


/*!
 * \brief Find random nums from [0;100] in Hash Table
 * 
 * \param[out] hash_table - Hash Table
 * \return return execution status (error code)
 */
TestStatus num_find_random_numbers_in_hash_table(Hash_Table* hash_table);


#elif TEST_HASH_TABLE_WITH_OPEN_ADDR

TestStatus num_test_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words);
TestStatus num_fill_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words);
TestStatus num_find_random_numbers_in_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr);


#endif


#endif