#include "hash_table.h"

#include <malloc.h>
#include <string.h>
#include <math.h>

#ifdef TEST_HASH_FUNCTION

Hash_Table* hash_table_ctor(size_t size)
{
    Hash_Table* hash_table = (Hash_Table*) calloc(1, sizeof(Hash_Table));
    CHECK_SOME_IS_NULL(NULL, hash_table)

    hash_table->table = (List*) calloc(size, sizeof(List));
    if (hash_table->table == NULL)
    {
        free(hash_table);
        return NULL;
    }

    hash_table->size = size;

    for (size_t i = 0; i < hash_table->size; i++)
    {
        List* current_list = &(hash_table->table[i]);
        list_ctor(current_list);                        
    }

    return hash_table;
}


Hash_Table* hash_table_dtor(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(NULL, hash_table)

    for (size_t i = 0; i < hash_table->size; i++)
    {
        list_dtor(&(hash_table->table[i]));
    }
    
    free(hash_table->table); 
    free(hash_table);
    return NULL;
}





TestStatus hash_table_insert(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table->size;

    if (list_find(hash_table->table[ind], element)) return OK; // no same elements
    status = list_push(&(hash_table->table[ind]), element);

    return status;
}


TestStatus hash_table_delete(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table->size;

    status = list_delete(&(hash_table->table[ind]), element);

    return status;
}

bool hash_table_find(Hash_Table* hash_table, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table->size;

    if (list_find(hash_table->table[ind], element) == NULL) return false;
    return true;
}

#ifdef TESTNUM
size_t hash_function(Elem_t element) // ее использовать по модулю длины хеш-таблицы
{
    return (size_t) element;    // ┐(￣ヘ￣)┌  <(Good hash-function)
}
#elif TESTSTRLEN
size_t hash_function(Elem_t element)
{
    return strlen(element);    
}
#elif TESTSTRSUM
size_t hash_function(Elem_t element)
{
    size_t letter_sum = 0;
    for (int i = 0; i < strlen(element); i++)
    {
        letter_sum += element[i];
    }   

    return letter_sum;
}
#elif TESTSTRPOLIN
size_t hash_function(Elem_t element)
{
    int p = 31; // ?
    int mod = 100000; // ?
    size_t letter_sum = 0;
    for (int i = 0; i < strlen(element); i++)
    {
        letter_sum += element[i] * p;
        p *= p;
    }   

    return letter_sum;
}
#endif

// _______________ DUMP __________________

void dump_hash_table(Hash_Table* hash_table)
{
    CHECK_SOME_IS_NULL(, hash_table)

    for (size_t i = 0; i < hash_table->size; i++)
    {
        PRINTF_GREEN("HASH FUNC IS (mod hash table size): ");
        printf("%ld", i);

        list_print(&(hash_table->table[i]));
    }
}

#endif