#include "../include/functions.h"
#include "../include/variables.h"

void ash_execute()
{
    get_command();
    // printf("command : %s\n", command);

    // Exit
    if(!strcmp(command, "q") || !strcmp(command, "quit") || !strcmp(command, "exit"))
    {
        flag_exit = 1;
        return;
    }
    // Run commands
    if(!strcmp(command, "cd"))
        ash_cd();
    if(!strcmp(command, "pwd"))
        ash_pwd();
    if(!strcmp(command, "echo"))
        ash_echo();
}