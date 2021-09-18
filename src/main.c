#include "../include/shell.h"

// User defined files
#include "general.c"
#include "ash_main.c"
#include "ash_execute.c"
#include "ash_cd.c"
#include "ash_pwd.c"
#include "ash_echo.c"
#include "ash_ls.c"
#include "ash_pinfo.c"
#include "ash_general.c"
#include "ash_signals.c"
#include "ash_repeat.c"

int main()
{
    // Signal Processing
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);
    
    get_home();                         // Home directory
    initialize_children();              // Background processes set to null

    // Ruh Ash Shell
    while(!flag_exit)
    {
        flag_handler = 0;

        ash_main();
    }

    // Clean
    kill_zombies();
}