#include "input.h"

#include <string.h>

#include "../dynamic_array/dynamic_array.h"
#include "../singly_linked_list/list.h"

const int MAX_COMMAND_SIZE = 10;


enum TestStatus run_test(FILE* test_file, enum ModeStack ModeStack, void* stack)
{
    enum TestStatus status= OK;
    if (test_file == NULL) return ERROR_OPEN_FILE;

    char command[MAX_COMMAND_SIZE] = {};
    
    while (fscanf(test_file, "%10s", command) != EOF)
    {
        CHECK_STATUS_OK(status);

        if (strcmp(command, "PUSH") == 0)
        {
            ElemArr_t num = 0;
            if (fscanf(test_file, "%d", &num) == 0) return ERROR_COMMAND_IN_TEST;

            if (ModeStack == DYNAMIC_STACK) status = dynamic_array_push(stack, &num);
            else                            status = list_push         (stack, &num);
        }
        else if (strcmp(command, "POP") == 0)
        {
            if (ModeStack == DYNAMIC_STACK) status = dynamic_array_pop(stack);
            else                            status = list_pop         (stack);
        }
        else if (strcmp(command, "GET_ELEM") == 0)
        {
            ElemArr_t num = 0;

            if (ModeStack == DYNAMIC_STACK) status = dynamic_array_get_last_elem(stack, &num);
            else                            status = list_get_first_elem        (stack, &num);

            printf("%d - elem\n", num);
        }
        else if (strcmp(command, "OUT") == 0)
        {
            if (ModeStack == DYNAMIC_STACK) dynamic_array_print_info(stack);
            else                            list_print(stack);
        }
        else
        {
            return ERROR_COMMAND_IN_TEST;
        }
    }
}
