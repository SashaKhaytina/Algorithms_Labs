#include <stdio.h>


const char* NAME_FILE_TEST_1 = "test1.txt";
const int   SIZE_TEST_1      = 1000000;


int main()
{
    FILE* file = fopen(NAME_FILE_TEST_1, "w");
    if (file == NULL)
    {
        printf("Error open test file\n");
        return 0;
    }

    int n = SIZE_TEST_1;

    while (n >= SIZE_TEST_1)
    {
        for (int i = 1; i < n + 1; i++) { fprintf(file, "PUSH %d\n", i); }

        for (int i = 1; i < n/2; i++)   { fprintf(file, "POP\n"); }

        for (int i = 1; i < n / 4; i++) { fprintf(file, "PUSH %d\n", i); }

        n = n - n / 2 + n / 4; 
    }

    fclose(file);
}