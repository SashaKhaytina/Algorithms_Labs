#ifndef ERRORS
#define ERRORS


#include <assert.h>

#define CHECK_STATUS(status) if (status != OK) return status;

enum ProgrammStatus
{
    OK, 
    ERROR_CTOR,
    POP_EMPTY_STACK, 
    GET_ELEM_IN_EMPTY_STACK,
    REALLOC_ERROR,
    ERROR 
};



#endif