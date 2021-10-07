#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int get_job_number2();

void ash_bg()
{
    int job_no = get_job_number2();
    if(job_no < 0) return;

    pid_t bg_pid = child_process[job_no].pid;

    if(kill(bg_pid, SIGCONT) < 0)
    {
        cprint("ash_bg", "Failed to continue the process");
        return;
    }
}

int get_job_number2()
{
    // Get the position
    char* token = malloc(100);
    token = strtok(duplicate, " ");

    // bg
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        cprint("ash_bg", "Syntax : bg <process_pos>");
        return -1;
    }

    // Job number must be a digit
    int flag_zero = !strcmp(token, "0");
    int job_no = strtol(token, &token, 10);
    if(!flag_zero && job_no == 0)
    {
        cprint("ash_bg", "Job number should be a digit");
        return -1;
    }
    
    // bg 1 2
    token = strtok(NULL, " ");
    if(token)
    {
        cprint("ash_bg", "Syntax : bg <process_pos>");
        return -1;
    }

    // Negative job number
    if(job_no < 0)
    {
        cprint("ash_bg", "Job number must be positive");
        return -1;
    }

    // fg <invalid_no>
    if(job_no >= MAX_BG_PROCESSES || child_process[job_no].pid == NOT_CREATED)
    {
        cprint("ash_bg", "Process with this job number does not exist");
        return -1;
    }

    return job_no;

    strcpy(duplicate, parsed_input);
}