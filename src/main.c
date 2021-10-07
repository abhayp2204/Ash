#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int main()
{
    master_pid = getpid();
    fg_process.pid = NOT_CREATED;

    signal(SIGCHLD, SIGCHLD_handler);
	signal(SIGINT, SIGINT_handler);
	signal(SIGTSTP, SIGTSTP_handler);
    
    get_home();                         // Home directory
    initialize_children();              // Background processes set to null

    flag_last_replay = 0;

    // Ruh Ash Shell
    while(!flag_exit)
    {
        flag_handler = 0;
        ash_main();
    }

    // Clean
    kill_zombies();
}