#ifndef HASH_TABLE_H
#define HASH_TABLE_H


#include <stdio.h>
#include <stdbool.h>

#include "../list/list.h"


#ifdef TEST_HASH_FUNCTION
typedef struct Hash_Table Hash_Table;
/*!
 * Struct hash table with linked lists.
 */
struct Hash_Table
{
    List* table;            /* Array with linked lists (there are elements in list). */
    size_t size;            /* Size of hash table. */
    size_t count_elements;  /* Number of elements in hash table. */
};


/*! \brief Function create hash table with linked lists.
 * \param[in] size size new hash table.
 *
 * \see list_ctor(List* list)
 * 
 * \return Pointer to hash table.
*/
Hash_Table* hash_table_ctor(size_t size);

/*! \brief Function free memory hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
 *
 * \return NULL.
*/
Hash_Table* hash_table_dtor(Hash_Table* hash_table);



/*! \brief Function insert (add) element in hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which add in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see list_find(List list, Elem_t element)
 * \see list_push(List* list, Elem_t elem)
 * \see load_factor(Hash_Table* hash_table)
 * \see hash_table_resize(Hash_Table* hash_table, size_t new_size)
 * 
 * \return Execution status.
*/
TestStatus hash_table_insert(Hash_Table* hash_table, Elem_t element);

/*! \brief Function delete element in hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which delete in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see list_delete(List* list, Elem_t elem)
 * 
 * \return Execution status.
*/
TestStatus hash_table_delete(Hash_Table* hash_table, Elem_t element);

/*! \brief Function find element in hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which find in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see list_find(List list, Elem_t element)
 * 
 * \return True or false. If element in hash table - return true. Else - return false.
*/
bool       hash_table_find  (Hash_Table* hash_table, Elem_t element);

/*! \brief Function changes the size of hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] new_size New hash table size.
 *
 * \see hash_table_insert(Hash_Table* hash_table, Elem_t element)
 * 
 * \return Execution status.
*/
TestStatus hash_table_resize(Hash_Table* hash_table, size_t new_size);



/*! \brief Function print info about hash table with linked lists.
 * \param[in] hash_table Pointer to hash table.
*/
void dump_hash_table        (Hash_Table* hash_table);

/*! \brief Function print table (index in hash table - element) in file.
 * \param[in] file Output file with table.
 * \param[in] hash_table Pointer to hash table.
*/
void graphic_dump_hash_table(FILE* file, Hash_Table* hash_table);



/*! \brief Hash Function.
 * \param[in] element Element wich hash return.
 * 
 * \return Hash of element.
*/
size_t hash_function(Elem_t element);


#endif 

#endif
