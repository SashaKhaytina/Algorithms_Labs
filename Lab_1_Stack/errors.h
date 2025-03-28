#ifndef ERRORS_H
#define ERRORS_H


#include <assert.h>
#include <stdarg.h>
#include <stdio.h>

#define CHECK_STATUS_OK(status) if (status != OK) return status;


#define GLUING(a, b) a##b
#define DEFENITION(base_name, line) GLUING(base_name, line)
#define CHECK_SOME_IS_NULL(error, ... )\
                                        void* DEFENITION(args_array, __LINE__)[] = {__VA_ARGS__};\
                                        for (size_t i = 0; i < sizeof(DEFENITION(args_array, __LINE__))/ sizeof(DEFENITION(args_array, __LINE__)[0]); i++)\
                                        {\
                                            if (DEFENITION(args_array, __LINE__)[i] == NULL) return error;\
                                        }\

enum TestStatus
{
    OK = 0,                             /*!< Everything is correct. */
    ERROR_CTOR = 1 << 1,                /*!< Error memory allocation when craete stack. */
    POP_EMPTY_STACK = 1 << 2,           /*!< Attempt delete element when stack is empty. */
    GET_ELEM_IN_EMPTY_STACK = 1 << 3,   /*!< Attempt get element when stack is empty. */
    REALLOC_ERROR = 1 << 4,             /*!< Error memory allocation when resize stack. */
    CALLOC_NODE_ERROR = 1 << 5,         /*!< Error memory allocation when create node for linked list. */
    ERROR_OPEN_FILE = 1 << 6,           /*!< Error open file. */
    ERROR_STACK_IS_NULL = 1 << 7,       /*!< Stack pointer is NULL */
    ERROR_NULL_POINTER = 1 << 8,        /*!< Pointer is NULL */
    // ERROR_MODE_STACK = 1 << 7,       

    ERROR_COMMAND_IN_TEST = 1 << 9,     /*!< Erroк in test file (command is not correct). */
    // ERROR = 1 << 9                   /*!< Default error */
};


// enum TestStatus CHECK_SOME_IS_NULL(enum TestStatus status, ...)
// {
//     va_list args_list;
//     va_start(args_list, status);

//     ElemArr_t* arg = va_arg(args_list, ElemArr_t*);

//     while (!arg)
//     {
        
//     }

// }



#endif