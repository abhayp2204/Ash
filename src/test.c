#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
    char str[] = "Let's have some fun doing this";

    char* piece = strtok(str, " ");

    while(piece)
    {
        piece++;
        printf("%s\n", piece);
        piece = strtok(NULL, " ");
    }
}