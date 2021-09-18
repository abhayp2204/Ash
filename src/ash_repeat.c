#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int get_repeat_number();
void get_repeat_args();

void ash_repeat()
{
    char *repeat_command = malloc(strlen(parsed_input));
    char *alter = malloc(strlen(parsed_input));
    int repeat_number;

    repeat_number = get_repeat_number();
    for(int i = 9 ; i < strlen(parsed_input) ; i++)
        alter[i-9] = parsed_input[i];
    alter[strlen(parsed_input) - 9] = '\0';

    strcpy(parsed_input, alter);

    for(int i = 0 ; i < repeat_number ; i++)
        ash_execute();
}

int get_repeat_number()
{
    char *token = malloc(strlen(parsed_input));
    char *copy = malloc(strlen(parsed_input));

    strcpy(copy, parsed_input);
    token = strtok(copy, " ");
    token = strtok(NULL, " ");

    int repeat_number;
    sscanf(token, "%d", &repeat_number);
    return repeat_number;
}

void get_repeat_args()
{
    char *token = malloc(strlen(parsed_input));
    char *copy = malloc(strlen(parsed_input));
    char *args[10];
    for(int i = 0 ; i < 10 ; i++)
        args[i] = malloc(10);

    strcpy(copy, parsed_input);

    token = strtok(copy, " ");
    token = strtok(NULL, " ");
    token = strtok(NULL, " ");

    int pos = 0;
    while(token)
    {
        strcpy(args[pos], token);
        printf("args = %s | ", args[pos++]);
        token = strtok(NULL, " ");
    }
    args[pos] = NULL;

    for(int i = 0 ; i < 10 ; i++)
    {
        if(execvp(args[0], args) < 0)
        {
            printf("There was a problem\n");
        }
    }
}