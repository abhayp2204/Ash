#include "../include/shell.h"
#include "../include/variables.h"
#include "../include/functions.h"

void initialize_children()
{
    for(int i = 0 ; i < MAX_BG_PROCESSES ; i++)
    {
        child_process[i].pid = NOT_CREATED;
        child_process[i].name[0] = '\0';
        child_process[i].pos = NOT_CREATED;
    }
}

void push_child(pid_t pid)
{
    int i = 0;
    for(i = 0 ; i < MAX_BG_PROCESSES ; i++)
    {
        if(child_process[i].pid == pid) return;
        if(child_process[i].pid == NOT_CREATED)
        {
            child_process[i].pid = pid;
            strcpy(child_process[i].name, command);
            child_process[i].pos = number_of_children++;

            break;
        }
    }

    // for(int j = 0 ; j < MAX_BG_PROCESSES ; j++)
    //     printf("cp %d pid = %d\n", j+1, child_process[j].pid);
    // printf("no of bg processes = %d\n", number_of_children);

    if(i == MAX_BG_PROCESSES)
        cprint("ash_tasks", "No space left for more background processes! :(\n");
}

void pop_child(int i)
{
	child_process[i].pid = NOT_CREATED;
	child_process[i].pos = NOT_CREATED;
	child_process[i].name[0] = '\0';
	number_of_children--;
}

void kill_zombies()
{
    for(int i = 0 ; i < MAX_BG_PROCESSES ; i++)
    {
        if(child_process[i].pid == NOT_CREATED)
            continue;

        kill(child_process[i].pid, SIGKILL);
    }
}