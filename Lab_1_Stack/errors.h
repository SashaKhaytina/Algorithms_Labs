#ifndef ERRORS
#define ERRORS


#include <assert.h>

#define CHECK_STATUS(status) if (status != OK) return status;



// typedef int ElemArr_t; // IT IS NOT HERE!

enum ProgrammStatus
{
    OK, 
    ERROR_CTOR,
    POP_EMPTY_STACK, 
    GET_ELEM_IN_EMPTY_STACK,
    REALLOC_ERROR,
    CALLOC_NODE_ERROR,
    ERROR_OPEN_FILE,
    ERROR_MODE,

    ERROR_COMMAND_IN_TEST,
    ERROR 
};



#endif