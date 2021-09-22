#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void get_destination();

void ash_execute()
{
    get_command();
    get_destination();
    // printf("command = %s\n", command);
    // printf("command length = %ld\n", strlen(command));

    // Exit
    if(!strcmp(command, "q") || !strcmp(command, "quit") || !strcmp(command, "exit"))
    {
        flag_exit = 1;
        return;
    }
    // Run commands
    if(!strcmp(command, "cd"))
        ash_cd();
    else if(!strcmp(command, "pwd"))
        ash_pwd();
    else if(!strcmp(command, "echo"))
        ash_echo();
    else if(!strcmp(command, "ls"))
        ash_lsc();
    else if(!strcmp(command, "pinfo"))
        ash_pinfo();
    else if(!strcmp(command, "repeat"))
        ash_repeat();
    else
        ash_general();
}

void get_command()
{
    // The command is the first word of the parsed input
    char *copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);
    strcpy(command, strtok(copy, " "));
}

void get_destination()
{}