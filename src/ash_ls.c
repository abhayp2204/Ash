#include "../include/functions.h"
#include "../include/variables.h"

void ash_ls()
{
    printf("input = %s\n", parsed_input);

    char delimiter[] = " ";
    char* piece = strtok(parsed_input, delimiter);
    piece = strtok(NULL, delimiter);

    while(piece)
    {
        printf("piece = %s\n", piece);
        printf("piece[0] = %c\n", piece[0]);
        piece = strtok(NULL, delimiter);
    }
}