#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int interval;
int period;
int flag_valid;

void parse_replay_input();
void replay();

void ash_replay()
{
    flag_replaying = 1;
    flag_valid = 1;
    
    interval = 0;
    period = 0;

    parse_replay_input();

    if(flag_valid)
        replay();
    flag_replaying = 0;
}

void replay()
{
    int execute_no = period / interval;

    // // Fork
    // pid_t pid = fork();
    // if(pid < 0)
    // {
    //     printf("ash_replay : Forking failed\n");
    //     return;
    // }
    // // The child waits for <interval> time, executes and repeats
    // if(pid == 0)
    // {
    //     while(1)
    //     {
    //         sleep(interval);
    //         ash_execute();
    //     }
    // }
    // // The parent waits for <period> time, kills child, returns
    // else
    // {
    //     sleep(period);
    //     usleep(execute_no*1000);    // Wait for negligible time to account for time taken by ash_execute()
    //     kill(pid, SIGTERM);
    //     return;
    // }

    for(int i = 1 ; i <= execute_no ; i++)
    {
        sleep(interval);

        if(i == execute_no)
            flag_last_replay = 1;

        ash_execute();
    }
    flag_last_replay = 0;
}

void parse_replay_input()
{
    char* copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);

    char* token = malloc(strlen(parsed_input));
    token = strtok(parsed_input, " ");

    while(token)
    {
        // Get command
        if(!strcmp(token, "-command"))
        {
            strcpy(parsed_input, "");
            token = strtok(NULL, " ");
            
            while(token)
            {
                if(!strcmp(token, "-interval") || !strcmp(token, "-period"))
                    break;

                strcat(parsed_input, token);
                strcat(parsed_input, " ");

                token = strtok(NULL," ");
            }
            trim_spaces(parsed_input);
        }

        // Empty command
        if(!strlen(parsed_input))
        {
            cprint("ash_replay", "Command field empty");
            flag_valid = 0;
            return;
        }

        // Get interval
        if(!strcmp(token, "-interval"))
        {
            token = strtok(NULL, " ");
            if(token == NULL)
            {
                cprint("ash_replay", "Interval field empty");
                flag_valid = 0;
                return;
            }
            interval = (int)strtol(token, &token, 10);
            if(!interval)
            {
                cprint("ash_replay", "Interval field empty");
                flag_valid = 0;
                return;
            }
        }

        // Get period
        if(!strcmp(token, "-period"))
        {
            token = strtok(NULL, " ");
            if(token == NULL)
            {
                cprint("ash_replay", "Period field empty");
                flag_valid = 0;
                return;
            }
            period = (int)strtol(token, &token, 10);
            if(!period)
            {
                cprint("ash_replay", "Period field empty");
                flag_valid = 0;
                return;
            }
        }

        token = strtok(NULL, " ");
    }

    if(interval == 0 || period == 0)
    {
        cprint("ash_replay", "Syntax : replay -command <command> -interval <interval> -period <period>");
        flag_valid = 0;
        return;
    }

    // printf("interval = %d\n", interval);
    // printf("period = %d\n", period);
}