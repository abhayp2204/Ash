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
        printf("ash_bg : Failed to continue the process\n");
        return;
    }
}

int get_job_number2()
{
    // Get the position
    char* token = malloc(100);
    token = strtok(duplicate, " ");

    // fg
    token = strtok(NULL, " ");
    if(token == NULL)
    {
        printf("ash_bg : Syntax : bg <process_pos>\n");
        return -1;
    }
    int job_no = strtol(token, &token, 10);
    
    // fg 1 2
    token = strtok(NULL, " ");
    if(token)
    {
        printf("ash_bg : Syntax : bg <process_pos>\n");
        return -1;
    }

    // Negative job number
    if(job_no < 0)
    {
        printf("ash_bg : job number must be positive\n");
        return -1;
    }

    // fg <invalid_no>
    if(child_process[job_no].pid == NOT_CREATED)
    {
        printf("ash_bg : No process with this job number\n");
        return -1;
    }

    return job_no;

    strcpy(duplicate, parsed_input);
}