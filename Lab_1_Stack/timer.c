#include "timer.h"

void print_test_time(enum ModeStack mode, char* file_test_name, double average_time, int num_test)
{
    if (mode == DYNAMIC_STACK) PRINTF_CYAN("DYNAMIC ARRAY:");
    else                       PRINTF_CYAN("LIST:");
    PRINTF_GREEN(" time of %s test: %g millisecond\n", file_test_name, average_time/num_test);
}
