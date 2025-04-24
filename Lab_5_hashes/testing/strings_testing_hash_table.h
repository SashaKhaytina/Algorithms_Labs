#ifndef STRINGS_TESTING_HASH_TABLE_H
#define STRINGS_TESTING_HASH_TABLE_H

#include "../hash_table/hash_table.h"

#ifdef TEST_HASH_FUNCTION

TestStatus str_test_hash_table(Hash_Table* hash_table, Text* words);
TestStatus str_fill_hash_table(Hash_Table* hash_table, Text* words);
TestStatus str_find_random_words_in_hash_table(Hash_Table* hash_table);

#endif


#endif