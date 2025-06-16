#include <stdio.h>


const char* NAME_FILE_TEST_2 = "test2.txt";
const int   SIZE_TEST_2      = 1000000;

void create_second_test(FILE* file);


int main()
{
    FILE* file = fopen(NAME_FILE_TEST_2, "w");
    if (file == NULL)
    {
        printf("Error open test file\n");
        return 0;
    }

    create_second_test(file);

    fclose(file);
}


void create_second_test(FILE* file)
{
    int n = SIZE_TEST_2;

    for (int i = 1; i < n + 1; i++) { fprintf(file, "PUSH %d\n", i); }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 10000; j++) { fprintf(file, "POP\n"); }
        for (int j = 1; j < 10001; j++) { fprintf(file, "PUSH %d\n", j); }
    }

    while (n >= SIZE_TEST_2)
    {
        for (int i = 1; i < n / 2; i++)   { fprintf(file, "POP\n"); }

        for (int i = 1; i < n / 4; i++) { fprintf(file, "PUSH %d\n", i); }

        n = n - n / 2 + n / 4; 
    }

    for (int i = 0; i < 100; i++)
    {
        for (int j = 0; j < 10000; j++) { fprintf(file, "POP\n"); }
        for (int j = 1; j < 10001; j++) { fprintf(file, "PUSH %d\n", j); }
    }
}