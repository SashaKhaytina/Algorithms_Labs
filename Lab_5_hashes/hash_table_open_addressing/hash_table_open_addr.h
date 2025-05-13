#ifndef HASH_TABLE_OPEN_ADDRESSING_H
#define HASH_TABLE_OPEN_ADDRESSING_H


#include <stdio.h>
#include <stdbool.h>

#include "../common.h"


#ifdef TEST_HASH_TABLE_WITH_OPEN_ADDR 


/*! Type enumerate.
 * 
 *  Enumerate different regimes line or square mode hash table.
 */
enum
{
    INSERT,         /*!< Mode (line or square) use when element inserting in hash table. */
    DELETE,         /*!< Mode (line or square) use when element deleting in hash table. */
    FIND            /*!< Mode (line or square) use when element finding in hash table. */
} typedef Place_used_method;


typedef struct Hash_Table_Open_Addr Hash_Table_Open_Addr;
/*!
 * Struct hash table with open addressing.
 */
struct Hash_Table_Open_Addr
{
    Elem_t* table;                  /*!< Array with elements of hash table. */
    size_t size;                    /*!< Size of hash table. */
    size_t count_elements;          /*!< Number of elements in hash table. */
};


/*! \brief Function create hash table with open addressing.
 * \param[in] size size new hash table.
 *
 * \return Pointer to hash table.
*/
Hash_Table_Open_Addr* hash_table_open_addr_ctor(size_t size);

/*! \brief Function free memory hash table with open addressing.
 * \param[in] hash_table Pointer to hash table.
 *
 * \return NULL.
*/
Hash_Table_Open_Addr* hash_table_open_addr_dtor(Hash_Table_Open_Addr* hash_table);



/*! \brief Function insert (add) element in hash table with open addressing.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which add in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see line_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * \see square_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * 
 * \return Execution status.
*/
TestStatus hash_table_open_addr_insert(Hash_Table_Open_Addr* hash_table, Elem_t element);

/*! \brief Function delete element in hash table with open addressing.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which delete in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see line_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * \see square_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * 
 * \return Execution status.
*/
TestStatus hash_table_open_addr_delete(Hash_Table_Open_Addr* hash_table, Elem_t element);

/*! \brief Function find element in hash table with open addressing.
 * \param[in] hash_table Pointer to hash table.
 * \param[in] element Element which find in hash table.
 *
 * \see hash_function(Elem_t element)
 * \see line_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * \see square_mode(Hash_Table_Open_Addr* hash_table_open_addr, size_t* ind, Elem_t element, Place_used_method place)
 * 
 * \return True or false. If element in hash table - return true. Else - return false.
*/
bool       hash_table_open_addr_find  (Hash_Table_Open_Addr* hash_table, Elem_t element);

/*! \brief Function changes the size of hash table with open addressing.
 * \param[in] hash_table_open_addr Pointer to hash table.
 * \param[in] new_size New hash table size.
 *
 * \see hash_table_open_addr_insert(Hash_Table_Open_Addr* hash_table, Elem_t element)
 * 
 * \return Execution status.
*/
TestStatus hash_table_open_addr_resize(Hash_Table_Open_Addr* hash_table_open_addr, size_t new_size);



/*! \brief Function print info about hash table with open addressing.
 * \param[in] hash_table Pointer to hash table.
*/
void dump_hash_table_open_addr(Hash_Table_Open_Addr* hash_table);


/*! \brief Hash Function.
 * \param[in] element Element wich hash return.
 * 
 * \return Hash of element.
*/
size_t hash_function(Elem_t element); 
#endif

#endif
