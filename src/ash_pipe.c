#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

void ash_pipe()
{
    int pipe_fd[2];

    // Create a Pipe
    if(pipe(pipe_fd) < 0)
    {
        perror("ash_pipe: Could not create pipe\n");
        return;
    }

    char* pipe_input = (char*)malloc(strlen(parsed_input) * sizeof(char));
    char* copy = (char*)malloc(strlen(parsed_input) * sizeof(char));
    strcpy(copy, parsed_input);

    int pos = 0;
    int pos2 = 0;
    int flag_play = 1;
    while(flag_play)
    {
        pos2 = pos;
        while(copy[pos++] != '|')
        {
            if(pos > strlen(copy))
            {
                flag_play = 0;
                break;
            }
        }
        strcpy(pipe_input, substring(copy, pos2, pos));
        trim_spaces(pipe_input);
        strcpy(parsed_input, pipe_input);
        get_command();
        flag_child_executed = 1;

        pid_t pid = fork();

        // Forking Failed
        if(pid < 0)
        {
            perror("ash_pipe: Forking failed :(\n");
            return;
        }
        // Child Process
        else if(pid == 0)
        {
            // printf("file name = %s\n", file_write);

            // Write
            dup2(pipe_fd[1], STDOUT_FILENO);

            // Read
            dup2(pipe_fd[0], STDIN_FILENO);

            flag_child_executed = 1;
            ash_execute();
            exit(0);
        }
        // Parent Process
        else
        {

            waitpid(pid, NULL, 0);
            close(pipe_fd[0]);
            close(pipe_fd[1]);
            free(copy);

            flag_child_executed = 1;
            return;
        }

        ash_execute();
    }
}