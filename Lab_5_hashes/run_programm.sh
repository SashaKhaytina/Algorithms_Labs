# gcc -DDEBUG -DTEST_HASH_FUNCTION -DTESTSTRPOLIN main.c hash_table/hash_table.c list/list.c testing/num_testing_hash_table.c testing/strings_testing_hash_table.c working_with_text/working_with_text.c -o hashtable
# gcc -DDEBUG -DTEST_HASH_FUNCTION -DTESTNUM main.c hash_table/hash_table.c list/list.c testing/num_testing_hash_table.c testing/strings_testing_hash_table.c working_with_text/working_with_text.c -o hashtable
# gcc -DDEBUG -DTEST_HASH_FUNCTION -DTESTSTRCRC32 main.c hash_table/hash_table.c list/list.c testing/num_testing_hash_table.c testing/strings_testing_hash_table.c working_with_text/working_with_text.c -o hashtable



gcc -DDEBUG -DTEST_HASH_TABLE_WITH_OPEN_ADDR -DTESTNUM main.c hash_table/hash_table.c hash_table_open_addressing/hash_table_open_addr.c list/list.c testing/num_testing_hash_table.c testing/strings_testing_hash_table.c working_with_text/working_with_text.c -o hashtable
# gcc -DDEBUG -DTEST_HASH_TABLE_WITH_OPEN_ADDR -DHASH_TABLE_WITH_OPEN_ADDR_LINE -DTESTNUM main.c hash_table/hash_table.c hash_table_open_addressing/hash_table_open_addr.c list/list.c testing/num_testing_hash_table.c testing/strings_testing_hash_table.c working_with_text/working_with_text.c -o hashtable


