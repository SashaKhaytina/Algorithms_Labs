#ifndef HASH_TABLE_OPEN_ADDRESSING_H
#define HASH_TABLE_OPEN_ADDRESSING_H


#include <stdio.h>
#include <stdbool.h>

#include "../common.h"


#ifdef TEST_HASH_TABLE_WITH_OPEN_ADDR 
// typedef struct Node_Hash_Table Node_Hash_Table;
// struct Node_Hash_Table
// {
//     Elem_t value;            /* Array with linked lists (there are elem-s with same h(elem) in list) */
//     size_t load_factor;      /* Size of Hash_Table (len(array)) */
// };


typedef struct Hash_Table_Open_Addr Hash_Table_Open_Addr;
struct Hash_Table_Open_Addr
{
    // Node_Hash_Table* table;         /* Array with linked lists (there are elem-s with same h(elem) in list) */
    Elem_t* table;
    size_t size;                    /* Size of Hash_Table (len(array)) */
    size_t count_elements;
};



Hash_Table_Open_Addr* hash_table_open_addr_ctor(size_t size);
Hash_Table_Open_Addr* hash_table_open_addr_dtor(Hash_Table_Open_Addr* hash_table);

TestStatus hash_table_open_addr_insert(Hash_Table_Open_Addr* hash_table, Elem_t element);
TestStatus hash_table_open_addr_delete(Hash_Table_Open_Addr* hash_table, Elem_t element);
bool       hash_table_open_addr_find  (Hash_Table_Open_Addr* hash_table, Elem_t element);
TestStatus hash_table_open_addr_resize(Hash_Table_Open_Addr* hash_table_open_addr, size_t new_size);


void dump_hash_table_open_addr(Hash_Table_Open_Addr* hash_table);

size_t hash_function(Elem_t element); 
#endif

#endif
