#ifndef INPUT_H
#define INPUT_H

#include "../common.h"

// const int MAX_COMMAND_SIZE = 10;

enum TestStatus get_test(FILE* test_file, enum ModeStack ModeStack, void* stack);

#endif
