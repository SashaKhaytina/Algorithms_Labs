#ifndef ERRORS_H
#define ERRORS_H


#include <assert.h>

#define CHECK_STATUS(status) if (status != OK) return status;


enum TestStatus
{
    OK = 0,                             /*!< Everything is correct. */
    ERROR_CTOR = 1 << 1,                /*!< Error memory allocation when craete stack. */
    POP_EMPTY_STACK = 1 << 2,           /*!< Attempt delete element when stack is empty. */
    GET_ELEM_IN_EMPTY_STACK = 1 << 3,   /*!< Attempt get element when stack is empty. */
    REALLOC_ERROR = 1 << 4,             /*!< Error memory allocation when resize stack. */
    CALLOC_NODE_ERROR = 1 << 5,         /*!< Error memory allocation when create node for linked list. */
    ERROR_OPEN_FILE = 1 << 6,           /*!< Error open file. */
    // ERROR_MODE_STACK = 1 << 7,       

    ERROR_COMMAND_IN_TEST = 1 << 8,     /*!< Erroк in test file (command is not correct). */
    // ERROR = 1 << 9                   /*!< Default error */
};



#endif