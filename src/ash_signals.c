#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void handler(int signal)
{
	switch(signal)
	{
		case SIGINT  : SIGINT_handler()  ; break;
		case SIGTSTP : SIGTSTP_handler() ; break;
		case SIGCHLD : SIGCHLD_handler() ; break;
	}
}

// Terminate process
void SIGCHLD_handler()
{
	// Ignore termination of foreground processes
    if(!flag_bg)
        return;

    char exit_message[1024];
    int status;
    pid_t pid;

	while((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		for(int i = 0; i < MAX_BG_PROCESSES ; i++)
		{
			if(child_process[i].pid == pid)
			{
				sprintf(exit_message, "\n%s with pid %d exited %s\n", child_process[i].name, pid, WIFEXITED(status) == 0 ? "abnormally" : "normally");
				wprint(exit_message);
                
				pop_child(i);
				break;
			}
		}
	}

    display_banner();
}

// Ctrl + Z
void SIGTSTP_handler()
{
	if(getpid() != master_pid) return;
	if(fg_process.pid == NOT_CREATED) return;

	// Check if bg process pool is full
	if(number_of_children == MAX_BG_PROCESSES)
	{
		perror("ash_signals : Background process pool is full\n");
		return;
	}

	if(kill(fg_process.pid, SIGTSTP) < 0)
	{
		perror("ash_signals : Could not send foreground process to background\n");
		return;	
	}

	strcpy(command, fg_process.name);
	push_child(fg_process.pid);
}

// Ctrl + C
void SIGINT_handler()
{
	for(int i = 0 ; i < MAX_BG_PROCESSES ; i++)
    {
        if(child_process[i].pid == NOT_CREATED)
            continue;

        kill(child_process[i].pid, SIGINT);
    }
}