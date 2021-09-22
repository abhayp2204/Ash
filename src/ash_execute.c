#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void get_destination();
void redirect_output(char* file_name);

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
{
    // Get the index of the start of the filename
    int pos = 0;
    while(parsed_input[pos++] != '>')
    {
        if(pos > strlen(parsed_input))
            return;
    }
    pos++;

    // Extract file name
    char* file_name = (char*)malloc(strlen(parsed_input) * sizeof(char));
    strcpy(file_name, substring(parsed_input, pos, strlen(parsed_input) + 1));
    strcpy(parsed_input, substring(parsed_input, 0, pos-2));

    // Redirect
    redirect_output(file_name);
}

void redirect_output(char* file_name)
{
    // Get file descriptor
    int fd = open(file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    if(fd == -1)
    {
        perror("ash_execute: There was a problem opening the file :(\n");
        return;
    }

    dup2(fd, STDOUT_FILENO);
    close(fd);
}