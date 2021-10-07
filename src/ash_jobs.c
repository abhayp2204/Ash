#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void ash_jobs()
{
    char* stat_file = malloc(100);
    char* pid_str = malloc(100);
    char* token = malloc(100);
    char* status = malloc(100);

    char ch;
    int spaces = 0;

    token = strtok(duplicate, " ");
    token = strtok(NULL, " ");

    int flag_r = 0;
    int flag_s = 0;
    int flag_invalid = 0;

    while(token)
    {
        if(token[0] != '-')
        {
            token = strtok(NULL, " ");
            continue;
        }

        // printf("token = %s\n", token);
        // printf("len = %ld\n", strlen(token));
        // printf("token[0] = %c\n", token[0]);

        for(int i = 1 ; i < strlen(token) ; i++)
        {
            if(token[i] == 'r')
                flag_r = 1;
            else if(token[i] == 's')
                flag_s = 1;
            else
                flag_invalid = 1;
        }

        if(flag_invalid)
        {
            cprint("ash_jobs", "Valid flags are -r and -s");
            return;
        }

        token = strtok(NULL, " ");
    }
    strcpy(duplicate, parsed_input);

    for(int i = 0 ; i < MAX_BG_PROCESSES ; i++)
    {
        if(child_process[i].pid == NOT_CREATED)
            continue;

        sprintf(pid_str, "%d", child_process[i].pid);

        strcpy(stat_file, "/proc/");
        strcat(stat_file, pid_str);
        strcat(stat_file, "/stat");

        FILE* fd = fopen(stat_file, "r");
        if(fd == NULL)
        {
            cprint("ash_jobs", "Error opening the stat file :(");
            return;
        }

        spaces = 0;
        while(1)
        {
            // Read character
            ch = fgetc(fd);

            spaces += is_space(ch);

            // Get the status character and return
            if(spaces == 2)
            {
                ch = fgetc(fd);
                break;
            }
        }

        // printf("ch = %c\n", ch);
        if(ch == 'S' || ch == 'R')
        {
            if(!flag_r && flag_s)
                continue;
            strcpy(status, "Running");
        }
        if(ch == 'T' || ch == 'Z')
        {
            if(!flag_s && flag_r)
                continue;
            strcpy(status, "Stopped");
        }

        printf("[%d] %s %s [%d]\n", child_process[i].pos, status, child_process[i].name, child_process[i].pid);
    }
}