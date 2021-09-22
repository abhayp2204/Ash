#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void ash_execute()
{
    get_command();
    // printf("command = %s\n", command);

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