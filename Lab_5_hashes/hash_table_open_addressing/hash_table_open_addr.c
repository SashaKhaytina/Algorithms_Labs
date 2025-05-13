#include "hash_table_open_addr.h"

#include <malloc.h>
#include <string.h>
#include <math.h>


#ifdef TEST_HASH_TABLE_WITH_OPEN_ADDR 


static double load_factor(Hash_Table_Open_Addr* hash_table_open_addr);


static bool line_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place);
static bool square_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place);



const Elem_t POISON = -1;
// const double MAX_LOAD_FACTOR = 0.8;
// const double RESIZE_COEFF = 1.5;


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
    // printf("%d - num\n", element);

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;

    #ifdef HASH_TABLE_WITH_OPEN_ADDR_LINE
    if (!line_mode(hash_table_open_addr, &ind, element, INSERT)) return ERROR_INCLUDE_IN_HASH_TABLE; // вернет true если нашел куда вставить ИЛИ ЕСЛИ В ТАБЛИЦЕ УЖЕ ЕСТЬ
    #else // #elif HASH_TABLE_WITH_OPEN_ADDR_SQUARE
    if (!square_mode(hash_table_open_addr, &ind, element, INSERT)) return ERROR_INCLUDE_IN_HASH_TABLE;
    #endif

    if (hash_table_open_addr->table[ind % hash_table_open_addr->size] == element) return status;

    hash_table_open_addr->count_elements++;
    hash_table_open_addr->table[ind % hash_table_open_addr->size] = element;


    return status;
}


TestStatus hash_table_open_addr_delete(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;

    #ifdef HASH_TABLE_WITH_OPEN_ADDR_LINE
    if (!line_mode(hash_table_open_addr, &ind, element, DELETE)) return DELETE_STACK_WITHOUT_THIS_ELEMENT; // вернет true если нашел куда вставить ИЛИ ЕСЛИ В ТАБЛИЦЕ УЖЕ ЕСТЬ
    #else // #elif HASH_TABLE_WITH_OPEN_ADDR_SQUARE
    if (!square_mode(hash_table_open_addr, &ind, element, DELETE)) return DELETE_STACK_WITHOUT_THIS_ELEMENT;
    #endif

    hash_table_open_addr->table[ind % hash_table_open_addr->size] = POISON;
    hash_table_open_addr->count_elements--;


    return status;
}

bool hash_table_open_addr_find(Hash_Table_Open_Addr* hash_table_open_addr, Elem_t element)
{
    CHECK_SOME_IS_NULL(ERROR_NULL_POINTER, hash_table_open_addr)
    TestStatus status = OK;

    
    size_t ind = hash_function(element) % hash_table_open_addr->size;

    #ifdef HASH_TABLE_WITH_OPEN_ADDR_LINE
    return line_mode(hash_table_open_addr, &ind, element, FIND);
    #else // #elif HASH_TABLE_WITH_OPEN_ADDR_SQUARE
    return square_mode(hash_table_open_addr, &ind, element, FIND);
    #endif
}


size_t hash_function(Elem_t element) // ее использовать по модулю длины хеш-таблицы
{
    return (size_t) element;    // ┐(￣ヘ￣)┌  <(Good hash-function)
}



TestStatus hash_table_open_addr_resize(Hash_Table_Open_Addr* hash_table_open_addr, size_t new_size) 
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
}



static bool line_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
{
    while (hash_table_open_addr->table[*ind % hash_table_open_addr->size] != POISON)
    {
        if (hash_table_open_addr->table[*ind % hash_table_open_addr->size] == element) return true;

        (*ind)++;

        if (*ind >= 2 * hash_table_open_addr->size) // это не очень оптимально. Можно переписать так же как square_mode через цикл
        {
            if (place == DELETE || place == FIND) return false;

            if (hash_table_open_addr_resize(hash_table_open_addr, (size_t)(int)(hash_table_open_addr->size * RESIZE_COEFF)) != OK) return false;
            *ind = hash_function(element) % hash_table_open_addr->size;
        }
    }

    if (place == DELETE || place == FIND) return false;
    return true;
}


static bool square_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
{
    for (size_t i = 1; i <= hash_table_open_addr->size; i++)
    {
        if (i == hash_table_open_addr->size && place == INSERT)
        {
            if (hash_table_open_addr_resize(hash_table_open_addr, (size_t)(int)(hash_table_open_addr->size * RESIZE_COEFF)) != OK) return false;
            *ind = hash_function(element) % hash_table_open_addr->size;
        }


        if (hash_table_open_addr->table[*ind] == element) return true;
        if (hash_table_open_addr->table[*ind] == POISON)
        {
            if (place == DELETE || place == FIND) return false;
            return true;
        }

        *ind = (*ind + i + i*i) % hash_table_open_addr->size;
    }

    if (place == DELETE || place == FIND) return false;

    PRINTF_RED("ERROR square_mode\n");
    return true; //? Этого никогда не должно случится
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