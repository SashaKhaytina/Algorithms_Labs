#include "timer.h"

void print_test_time_in_file(FILE* file, double* arr_time, int from, int to, int step)
{
    int counter_points = 0;
    for (int test_size = from; test_size < to + 1; test_size += step)
    {
        fprintf(file, "%d %f\n", test_size, arr_time[counter_points]);
        counter_points++;
    }
}