#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void get_system_data();

void main()
{
    master_pid = getpid();
    fg_process.pid = NOT_CREATED;

    // Signal Processing
    signal(SIGCHLD, SIGCHLD_handler);
	signal(SIGINT, SIGINT_handler);
	signal(SIGTSTP, SIGTSTP_handler);

    get_system_data();                  // Gets username and hostname
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

void get_system_data()
{
    // Getting username caused inputs of length 24 and other certain lengths
    // to cause malloc error (idk why). So it was done in fork so as to
    // not interfere with the rest of the program
    int fd[2];
    if(pipe(fd) == -1)
    {
        cprint("ash_main", "Piping failed");
        return;
    }
    pid_t pid = fork();
    if(pid < 0)
    {
        cprint("ash_main", "Forking failed");
        return;
    }
    if(pid == 0)
    {
        // Not reading, close read end
        close(fd[0]);

        getlogin_r(username, sizeof(username));
        write(fd[1], &username, sizeof(username));
        close(fd[1]);
        exit(0);
    }
    else
    {
        // Not writing, close write end
        close(fd[1]);

        read(fd[0], &username, sizeof(username));
        close(fd[0]);
        waitpid(pid, NULL, WUNTRACED);
    }
    gethostname(hostname, sizeof(hostname));
}