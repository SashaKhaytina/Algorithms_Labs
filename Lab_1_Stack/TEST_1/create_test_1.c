#include <stdio.h>


const char* NAME_FILE_TEST_1 = "test1.txt";
const int   SIZE_TEST_1      = 1000000;


void create_first_test(FILE* file);


int main()
{
    FILE* file = fopen(NAME_FILE_TEST_1, "w");
    if (file == NULL)
    {
        printf("Error open test file\n");
        return 0;
    }

    create_first_test(file);

    fclose(file);
}


void create_first_test(FILE* file)
{

    int n = SIZE_TEST_1;

    for (int i = 1; i < n + 1; i++) { fprintf(file, "PUSH %d\n", i); }

    while (n >= 100000)
    {
        for (int i = 1; i < n/2; i++) { fprintf(file, "POP\n"); }

        for (int i = 1; i < n / 4; i++) { fprintf(file, "PUSH %d\n", i); }

        n = n - n / 2 + n / 4; 
    }
}

