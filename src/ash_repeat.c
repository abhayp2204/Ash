#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// Can handle : repeat m repeat n <command>

int get_repeat_number();
char* get_repeat_command();

void ash_repeat()
{
    char *repeat_command = malloc(strlen(parsed_input));
    int repeat_number;

    repeat_number = get_repeat_number();
    strcpy(repeat_command, get_repeat_command());

    // Execute the modified parsed input n times
    for(int i = 0 ; i < repeat_number ; i++)
    {
        strcpy(parsed_input, repeat_command);
        ash_execute();
    }
}

int get_repeat_number()
{
    char *token = malloc(strlen(parsed_input));
    char *copy = malloc(strlen(parsed_input));

    strcpy(copy, parsed_input);
    token = strtok(copy, " ");
    token = strtok(NULL, " ");

    int repeat_number = (int)strtol(token, &token, 10);

    // Wrong syntax
    if(!repeat_number || repeat_number < 0)
    {
        cprint("ash_repeat", "Syntax : repeat <positive_integer> <command>");
        return 0;
    }

    return repeat_number;
}

char* get_repeat_command()
{
    // Note : Here actual command refers to the string with repeat n omitted
    // For example:
    // command        = repeat 2 cd ..
    // actual command = cd ..

    // Skip to the start of the actual command
    int start = 0;
    while(!is_space(parsed_input[start++]));
    while(!is_space(parsed_input[start++]));

    // Construct the actual command
    char *new_parsed_input = malloc(strlen(parsed_input));
    for(int i = start ; i < strlen(parsed_input) ; i++)
    {
        new_parsed_input[i-start] = parsed_input[i];
    }
    new_parsed_input[strlen(parsed_input) - start] = '\0';

    strcpy(parsed_input, new_parsed_input);
}