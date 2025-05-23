#ifndef COMMON_H
#define COMMON_H


#define CHECK_STATUS_OK(status) if (status != OK) return status;


#define GLUING(a, b) a##b
#define DEFENITION(base_name, line) GLUING(base_name, line)
#define CHECK_SOME_IS_NULL(error, ... )\
                                        void* DEFENITION(args_array, __LINE__)[] = {__VA_ARGS__};\
                                        for (size_t i = 0; i < sizeof(DEFENITION(args_array, __LINE__))/ sizeof(DEFENITION(args_array, __LINE__)[0]); i++)\
                                        {\
                                            if (DEFENITION(args_array, __LINE__)[i] == NULL) return error;\
                                        }\


#define PRINTF_GREEN(string, ...)   printf("\x1b[32m" string "\x1b[0m", ##__VA_ARGS__)      /*!< Print green text. */
#define PRINTF_RED(string, ...)     printf("\x1b[31m" string "\x1b[0m", ##__VA_ARGS__)      /*!< Print red text. */


#define START_TIMER struct timeval time_start = {}; gettimeofday(&time_start, NULL);

#define END_TIMER   struct timeval time_end   = {}; gettimeofday(&time_end,   NULL);\
                    average_time += ((double) (time_end.tv_sec * 1000 + time_end.tv_usec / 1000)) - ((double) time_start.tv_sec * 1000 + time_start.tv_usec / 1000);

#define COUNT_TIME(code) START_TIMER\
                        code\
                        END_TIMER


#ifdef TESTNUM
typedef int Elem_t;
#else
typedef char* Elem_t;
#endif


enum
{
    OK = 0,                                         /*!< Everything is correct. */
    DELETE_STACK_WITHOUT_THIS_ELEMENT = 1 << 1,     /*!< Delete elem, whose not in the Hash table. */
    CALLOC_NODE_ERROR = 1 << 2,                     /*!< Error memory allocation when create node for list. */
    ERROR_NULL_POINTER = 1 << 3,                    /*!< Pointer is NULL. */
    ERROR_MODE = 1 << 4,                            /*!< Нappened entry to function wich not for declared mode. */
    ERROR_RESIZE_DOWN = 1 << 5,                     /*!< Resize function have arguments wich lead to a reduction in size hash table. */
    REALLOC_RESIZE_ERROR = 1 << 6,                  /*!< Error memory allocation when resize hash table. */
    ERROR_INCLUDE_IN_HASH_TABLE = 1 << 7,           /*!< Error include element in hash table. */
    ERROR_OPEN_FILE = 1 << 8                        /*!< Error open file. */
    
} typedef TestStatus;



typedef struct Text Text;
struct Text 
{
    #ifndef TESTNUM
    char** words;
    #else
    int* words;
    #endif
    size_t count_words;
};


static const double MAX_LOAD_FACTOR = 0.2;
static const double RESIZE_COEFF = 1.5;

#endif
