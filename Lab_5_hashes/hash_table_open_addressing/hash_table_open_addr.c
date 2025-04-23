#include "hash_table_open_addr.h"

#include <malloc.h>
#include <string.h>
#include <math.h>


#ifdef TEST_HASH_TABLE_WITH_OPEN_ADDR 


static double load_factor(Hash_Table_Open_Addr* hash_table_open_addr);

const Elem_t POISON = -1;
const double MAX_LOAD_FACTOR = 0.8;
const double RESIZE_COEFF = 1.5;


Hash_Table_Open_Addr* hash_table_open_addr_ctor(size_t size)
{
    Hash_Table_Open_Addr* hash_table_open_addr = (Hash_Table_Open_Addr*) calloc(1, sizeof(Hash_Table_Open_Addr));
    CHECK_SOME_IS_NULL(NULL, hash_table_open_addr)

    hash_table_open_addr->table = (Elem_t*) calloc(size, sizeof(Elem_t));
    if (hash_table_open_addr->table == NULL)
    {
        free(hash_table_open_addr);
        return NULL;
    }

    hash_table_open_addr->size = size;
    hash_table_open_addr->count_elements = 0;

    for (size_t i = 0; i < hash_table_open_addr->size; i++) hash_table_open_addr->table[i] = POISON;

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
    if (hash_table_open_addr->table[ind % hash_table_open_addr->size] != element)
    {
        hash_table_open_addr->count_elements++;
        #ifdef DEBUG
        printf("load factor - %f\n", load_factor(hash_table_open_addr));
        printf("OLD SIZE - %ld\n", hash_table_open_addr->size);
        #endif
        
        if(load_factor(hash_table_open_addr) > MAX_LOAD_FACTOR) status = hash_table_open_addr_resize(hash_table_open_addr, (size_t)(hash_table_open_addr->size * RESIZE_COEFF));  
        
        #ifdef DEBUG
        printf("NEW SIZE - %ld\n", hash_table_open_addr->size);
        #endif


    }
    CHECK_STATUS_OK(status)

    while (hash_table_open_addr->table[ind % hash_table_open_addr->size] != POISON)
    {
        if (hash_table_open_addr->table[ind % hash_table_open_addr->size] == element) return OK;

        ind++;
        if (ind >= 2 * hash_table_open_addr->size)
        {
            #ifdef DEBUG
            printf("OLD SIZE - %ld, n - %ld\n", hash_table_open_addr->size, hash_table_open_addr->count_elements);
            #endif

            status = hash_table_open_addr_resize(hash_table_open_addr, (size_t)(int)(hash_table_open_addr->size * RESIZE_COEFF));
            CHECK_STATUS_OK(status)
            #ifdef DEBUG
            printf("NEW SIZE - %ld, n - %ld\n", hash_table_open_addr->size,  hash_table_open_addr->count_elements);
            #endif

            size_t ind = hash_function(element) % hash_table_open_addr->size;
        }
    }

    hash_table_open_addr->table[ind % hash_table_open_addr->size] = element;


    return status;
}


TestStatus hash_table_open_addr_delete(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;

    while (hash_table_open_addr->table[ind % hash_table_open_addr->size] != element && hash_table_open_addr->table[ind % hash_table_open_addr->size] != POISON)
    {
        ind++;
        if (ind >= 2 * hash_table_open_addr->size) return DELETE_STACK_WITHOUT_THIS_ELEMENT;
    }

    if (hash_table_open_addr->table[ind % hash_table_open_addr->size] != element || hash_table_open_addr->table[ind % hash_table_open_addr->size] == POISON) return DELETE_STACK_WITHOUT_THIS_ELEMENT;
    else hash_table_open_addr->table[ind % hash_table_open_addr->size] = POISON;
    hash_table_open_addr->count_elements--;


    return status;
}

bool hash_table_open_addr_find(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;


    while (hash_table_open_addr->table[ind % hash_table_open_addr->size] != element && hash_table_open_addr->table[ind % hash_table_open_addr->size] != POISON)
    {
        ind++;
        if (ind >= 2 * hash_table_open_addr->size) return false;
    }

    return (hash_table_open_addr->table[ind % hash_table_open_addr->size] == element);

}


size_t hash_function(Elem_t element) // ее использовать по модулю длины хеш-таблицы
{
    return (size_t) element;    // ┐(￣ヘ￣)┌  <(Good hash-function)
}



TestStatus hash_table_open_addr_resize(Hash_Table_Open_Addr* hash_table_open_addr, size_t new_size) //FIXME: Сделать!
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    if (new_size < hash_table_open_addr->size) return ERROR_RESIZE_DOWN;

    Elem_t* realloced_hash_table = (Elem_t*) realloc(hash_table_open_addr->table, new_size * sizeof(Elem_t));

    if (realloced_hash_table == NULL) return REALLOC_RESIZE_ERROR;

    hash_table_open_addr->table          = realloced_hash_table;
    size_t old_size = hash_table_open_addr->size;
    hash_table_open_addr->size           = new_size;
    hash_table_open_addr->count_elements = 0;

    for (size_t i = old_size; i < new_size; i++) hash_table_open_addr->table[i] = POISON;

    // rewrite elements
    for (size_t i = 0; i < old_size; i++)
    {
        CHECK_STATUS_OK(status)

        if (hash_table_open_addr->table[i] == POISON) continue;

        Elem_t current_element = hash_table_open_addr->table[i];
        hash_table_open_addr->table[i] = POISON;

        status = hash_table_open_addr_insert(hash_table_open_addr, current_element);
    }

    return status;
    return OK;
}



// _______________ DUMP __________________

void dump_hash_table_open_addr(Hash_Table_Open_Addr* hash_table_open_addr)
{
    CHECK_SOME_IS_NULL(, hash_table_open_addr)

    printf("LOAD FACTOR: %g, n - %ld\n", load_factor(hash_table_open_addr), hash_table_open_addr->count_elements);

    for (size_t i = 0; i < hash_table_open_addr->size; i++)
    {
        PRINTF_GREEN("HASH FUNC IS (mod hash table size): ");
        printf("%ld\n", i);

        PRINTF_GREEN("VALUE: ");
        printf("%d \n", hash_table_open_addr->table[i]);

    }
}


// ____________________ LOADFACTOR___________________

static double load_factor(Hash_Table_Open_Addr* hash_table_open_addr)
{
    double load_factor = ((double) hash_table_open_addr->count_elements) / ((double)hash_table_open_addr->size);
    return load_factor;
}


#endif 