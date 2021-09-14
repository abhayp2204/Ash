#include "../include/functions.h"
#include "../include/variables.h"

int flag_l = 0;
int flag_a = 0;
int flag_invalid = 0;

void find_flags(char piece[]);
void reset_flags();

void ash_ls()
{
    // printf("input = %s\n", parsed_input);

    char delimiter[] = " ";
    char* piece = strtok(parsed_input, delimiter);
    piece = strtok(NULL, delimiter);

    while(piece)
    {
        // printf("piece = %s\n", piece);
        // printf("len = %ld\n", strlen(piece));
        // printf("piece[0] = %c\n", piece[0]);

        find_flags(piece);

        if(flag_invalid)
        {
            printf("ash_ls: Invalid flags were entered\n");
            reset_flags();
            return;
        }

        piece = strtok(NULL, delimiter);
    }

    printf("l? = %d\n", flag_l);
    printf("a? = %d\n", flag_a);

    reset_flags();
}

void find_flags(char piece[])
{
    for(int i = 1 ; i < strlen(piece) ; i++)
    {
        if(piece[i] == 'l')
            flag_l = 1;
        else if(piece[i] == 'a')
            flag_a = 1;
        else
            flag_invalid = 1;
    }
}

void reset_flags()
{
    flag_l = 0;
    flag_a = 0;
    flag_invalid = 0;
}