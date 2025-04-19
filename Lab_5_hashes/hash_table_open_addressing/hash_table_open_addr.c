#include "hash_table_open_addr.h"

#include <malloc.h>
#include <string.h>
#include <math.h>


// #ifdef COMPARE_HASH_TABLES // FIXME: поставить

const Elem_t POISON = -1;
const size_t MAX_LOAD_FACTOR = 100;


Hash_Table_Open_Addr* hash_table_open_addr_ctor(size_t size)
{
    Hash_Table_Open_Addr* hash_table_open_addr = (Hash_Table_Open_Addr*) calloc(1, sizeof(Hash_Table_Open_Addr));
    CHECK_SOME_IS_NULL(NULL, hash_table_open_addr)

    hash_table_open_addr->table = (Node_Hash_Table*) calloc(size, sizeof(Node_Hash_Table));
    if (hash_table_open_addr->table == NULL)
    {
        free(hash_table_open_addr);
        return NULL;
    }

    hash_table_open_addr->size = size;

    for (size_t i = 0; i < hash_table_open_addr->size; i++)
    {
        hash_table_open_addr->table[i].value = POISON;
        hash_table_open_addr->table[i].load_factor = 0;
    }

    return hash_table_open_addr;
}


Hash_Table_Open_Addr* hash_table_open_addr_dtor(Hash_Table_Open_Addr* hash_table_open_addr)
{
    CHECK_SOME_IS_NULL(NULL, hash_table_open_addr, hash_table_open_addr->table)
    
    free(hash_table_open_addr->table); 
    free(hash_table_open_addr);
    return NULL;
}





TestStatus hash_table_open_addr_insert(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;
    if (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != element)
    {
        if(++hash_table_open_addr->table[ind % hash_table_open_addr->size].load_factor > MAX_LOAD_FACTOR);  // resize_hash_table_open_addr(hash_table_open_addr) // FIXME: Сделать
    }

    // if (hash_table_open_addr_find(hash_table_open_addr, element)) return OK; // no same elements

    while (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != POISON)
    {
        if (hash_table_open_addr->table[ind % hash_table_open_addr->size].value == element) return OK;

        ind++;
        if (ind >= 2 * hash_table_open_addr->size)
        {
            // resize_hash_table_open_addr(hash_table_open_addr) // FIXME: Сделать (во время resize все элементы должны пересчитать свои места? ДА!)
            break;
        }
    }

    hash_table_open_addr->table[ind % hash_table_open_addr->size].value = element;
    

    return status;
}


TestStatus hash_table_open_addr_delete(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;

    while (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != element && hash_table_open_addr->table[ind % hash_table_open_addr->size].value != POISON)
    {
        ind++;
        if (ind >= 2 * hash_table_open_addr->size) return DELETE_STACK_WITHOUT_THIS_ELEMENT;
    }

    if (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != POISON) return DELETE_STACK_WITHOUT_THIS_ELEMENT;
    else hash_table_open_addr->table[ind % hash_table_open_addr->size].value = POISON;


    return status;
}

bool hash_table_open_addr_find(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;


    while (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != element && hash_table_open_addr->table[ind % hash_table_open_addr->size].value != POISON)
    {
        ind++;
        if (ind >= 2 * hash_table_open_addr->size) return false;
    }

    if (hash_table_open_addr->table[ind % hash_table_open_addr->size].value != POISON) return false;
    return ind % hash_table_open_addr->size;
}


size_t hash_function(Elem_t element) // ее использовать по модулю длины хеш-таблицы
{
    return (size_t) element;    // ┐(￣ヘ￣)┌  <(Good hash-function)
}



TestStatus hash_table_open_addr_resize(Hash_Table_Open_Addr* hash_table_open_addr, size_t new_size) //FIXME: Сделать!
{

}



// _______________ DUMP __________________

void dump_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr)
{
    CHECK_SOME_IS_NULL(, hash_table_open_addr)

    for (size_t i = 0; i < hash_table_open_addr->size; i++)
    {
        PRINTF_GREEN("HASH FUNC IS (mod hash table size): ");
        printf("%ld\n", i);

        PRINTF_GREEN("VALUE: ");
        printf("%ld\n", hash_table_open_addr->table[i]);

    }
}






// #endif // FIXME: поставить