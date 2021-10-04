#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void ash_fg()
{
    // Get the position
    char* token = malloc(100);
    token = strtok(parsed_input, " ");

    token = strtok(NULL, " ");
    if(token == NULL)
    {
        printf("ash_fg : Syntax : fgg <process_pos>\n");
        return;
    }
    int job_no = strtol(token, &token, 10);

    token = strtok(NULL, " ");
    if(token)
    {
        printf("ash_fg : Syntax : fg <process_pos>\n");
        return;
    }

    if(child_process[job_no].pid == NOT_CREATED)
    {
        printf("ash_fg : No process with this job number\n");
        return;
    }

    strcpy(duplicate, parsed_input);
}