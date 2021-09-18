#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int get_repeat_number();
void get_repeat_command();

void ash_repeat()
{
    char *repeat_command = malloc(strlen(parsed_input));
    int repeat_number;

    repeat_number = get_repeat_number();
    get_repeat_command();

    // Execute the modified parsed input n times
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

void get_repeat_command()
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