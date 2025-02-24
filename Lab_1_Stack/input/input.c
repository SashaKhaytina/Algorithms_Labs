#include "input.h"

#include <string.h>

#include "../dynamic_array/dynamic_array.h"
#include "../singly_linked_list/list.h"


enum ProgrammStatus get_test(FILE* test_file, enum Mode mode, void* stack)
{
    enum ProgrammStatus status= OK;
    if (test_file == NULL) return ERROR_OPEN_FILE;

    char command[10] = {};

    while (fscanf(test_file, "%s", command) != EOF)
    {
        CHECK_STATUS(status);

        if (strcmp(command, "PUSH") == 0)
        {
            ElemArr_t num = 0;
            fscanf(test_file, "%d", &num);

            if (mode == DYNAMIC_STACK) status = dynamic_array_push(stack, &num);
            else                       status = list_push         (stack, &num);
        }
        else if (strcmp(command, "POP") == 0)
        {
            if (mode == DYNAMIC_STACK) status = dynamic_array_pop(stack);
            else                       status = list_pop         (stack);
        }
        else if (strcmp(command, "GET_ELEM") == 0)
        {
            ElemArr_t num = 0;

            if (mode == DYNAMIC_STACK) status = get_last_elem (stack, &num);
            else                       status = get_first_elem(stack, &num);

            printf("%d - elem\n", num);
        }
        else if (strcmp(command, "OUT") == 0)
        {
            if (mode == DYNAMIC_STACK) print_dyn_stack_info (stack);
            else                       print_list(stack);
        }
        else
        {
            return ERROR_COMMAND_IN_TEST;
        }
    }
}
