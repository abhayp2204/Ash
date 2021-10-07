#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void get_destination();
void redirect_output(char* file_name);

int flag_append;

void ash_execute()
{
    get_command();
    // printf("pi = %s\n", parsed_input);
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
    else if(!strcmp(command, "jobs"))
        ash_jobs();
    else if(!strcmp(command, "sig"))
        ash_sig();
    else if(!strcmp(command, "fg"))
        ash_fg();
    else if(!strcmp(command, "bg"))
        ash_bg();
    else if(!strcmp(command, "replay"))
        ash_replay();
    else
        ash_general();
}

void get_command()
{
    // The command is the first word of the parsed input
    char *copy = malloc(strlen(parsed_input)*sizeof(char));
    strcpy(copy, parsed_input);
    strcpy(command, strtok(copy, " "));
    free(copy);
}