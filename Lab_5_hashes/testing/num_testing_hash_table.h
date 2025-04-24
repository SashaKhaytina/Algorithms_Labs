#ifndef TESTING_HASH_TABLE_H
#define TESTING_HASH_TABLE_H

#include "../hash_table/hash_table.h"
#include "../hash_table_open_addressing/hash_table_open_addr.h"


#ifdef TEST_HASH_FUNCTION

TestStatus num_test_hash_table(Hash_Table* hash_table, Text* words);
TestStatus num_fill_hash_table(Hash_Table* hash_table, Text* words);
TestStatus num_find_random_numbers_in_hash_table(Hash_Table* hash_table);


#elif TEST_HASH_TABLE_WITH_OPEN_ADDR

TestStatus num_test_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words);
TestStatus num_fill_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr, Text* words);
TestStatus num_find_random_numbers_in_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr);


#endif


#endif