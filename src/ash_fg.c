#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int get_job_number();

void ash_fg()
{
    int job_no = get_job_number();
    if(job_no < 0) return;

    pid_t parent_pid = getpid();
    pid_t fg_pid = child_process[job_no].pid;
    int status;

    // Show the user the name of the process they pulled to fg
    printf("%s\n", child_process[job_no].name);
    
    // Ignore SIGTTOU and SIGTTIN
    signal(SIGTTOU, SIG_IGN);
    signal(SIGTTIN, SIG_IGN);
    tcsetpgrp(STDIN_FILENO, getpgid(fg_pid));

    flag_bg = 0;

    // Send SIGCONT signal
    if(kill(fg_pid, SIGCONT) < 0)
    {
        cprint("ash_fg", "Failed to bring process to the foreground");
        return;
    }

    // Ctrl + Z
    fg_process.pid = fg_pid;

    // Wait for the fg process to close
    waitpid(fg_pid, &status, WUNTRACED);

    // Set the signal handlers back to default
	tcsetpgrp(STDIN_FILENO, getpgid(parent_pid));
	signal(SIGTTIN, SIG_DFL);
	signal(SIGTTOU, SIG_DFL);

    if(WIFEXITED(status))
    {
        pop_child(job_no);
    }
}

int get_job_number()
{
    // Get the position
    char* token = malloc(100);
    token = strtok(duplicate, " ");

    // fg
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        cprint("ash_fg", "Syntax : fg <process_pos>");
        return -1;
    }

    // Job number must be a digit
    int flag_zero = !strcmp(token, "0");
    int job_no = strtol(token, &token, 10);
    if(!flag_zero && job_no == 0)
    {
        cprint("ash_fg", "Job number should be a digit");
        return -1;
    }
    
    // fg 1 2
    token = strtok(NULL, " ");
    if(token)
    {
        cprint("ash_fg", "Syntax : fg <process_pos>");
        return -1;
    }

    // Negative job number
    if(job_no < 0)
    {
        cprint("ash_fg", "Job number must be positive");
        return -1;
    }

    // fg <invalid_no>
    if(job_no >= MAX_BG_PROCESSES || child_process[job_no].pid == NOT_CREATED)
    {
        cprint("ash_fg", "Process with this job number does not exist");
        return -1;
    }

    return job_no;

    strcpy(duplicate, parsed_input);
}