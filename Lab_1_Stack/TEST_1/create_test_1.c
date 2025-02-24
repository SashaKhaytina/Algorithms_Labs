#include <stdio.h>

int main()
{
    FILE* file = fopen("test1.txt", "w");

    int n = 1000000;

    while (n >= 100000)
    {
        for (int i = 1; i < n + 1; i++) { fprintf(file, "PUSH %d\n", i); }

        for (int i = 1; i < n/2; i++)   { fprintf(file, "POP\n"); }

        for (int i = 1; i < n / 4; i++) { fprintf(file, "PUSH %d\n", i); }

        n = n - n / 2 + n / 4; 
    }

    fclose(file);
}