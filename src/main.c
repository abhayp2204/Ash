#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int main()
{
    // Signal Processing
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
    
    get_home();                         // Home directory
    initialize_children();              // Background processes set to null
    stdout_fd = dup(STDOUT_FILENO);

    // Ruh Ash Shell
    while(!flag_exit)
    {
        flag_handler = 0;
        ash_main();
    }

    // Clean
    close(stdout_fd);
    kill_zombies();
}