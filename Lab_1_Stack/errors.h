#ifndef ERRORS_H
#define ERRORS_H


#include <assert.h>

#define CHECK_STATUS(status) if (status != OK) return status;


enum TestStatus
{
    OK = 0, 
    ERROR_CTOR = 1 << 1,
    POP_EMPTY_STACK = 1 << 2, 
    GET_ELEM_IN_EMPTY_STACK = 1 << 3,
    REALLOC_ERROR = 1 << 4,
    CALLOC_NODE_ERROR = 1 << 5,
    ERROR_OPEN_FILE = 1 << 6,
    ERROR_MODE_STACK = 1 << 7,

    ERROR_COMMAND_IN_TEST = 1 << 8,
    ERROR = 1 << 9
};



#endif