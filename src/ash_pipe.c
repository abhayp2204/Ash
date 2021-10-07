#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int get_pipe_number();

void ash_pipe()
{
    int number_of_pipes = get_pipe_number();

    // If there are no pipes, just check for redirects
    if(!number_of_pipes)
    {
        ash_redirect();
        return;
    }

    flag_executed = 1;

    // Strings to tokenize
    char* copy = malloc(strlen(parsed_input) * sizeof(char));
    strcpy(copy, parsed_input);
    char* token = malloc(strlen(parsed_input) * sizeof(char));
    token = strtok(copy, "|");
    
    int new_input = STDIN_FILENO;

    // If there are n pipes, there are n+1 tokens
    // cat file.txt | head -4 | tail -2
    //      0       |    1    |    2
    for(int i = 0 ; i <= number_of_pipes ; i++)
    {
        // Create pipe
        int pipe_fd[2];
        if(pipe(pipe_fd) < 0)
        {
            cprint("ash_pipe", "Could not create pipe");
            return;
        }

        // We must execute each token
        trim_spaces(token);
        strcpy(parsed_input, token);

        // Fork
        pid_t pid = fork();
        if(pid < 0)
        {
            cprint("ash_pipe", "Forking failed :(");
            return;
        }
        // Child Process
        if(pid == 0)
        {
            // Input redirect
            dup2(new_input, STDIN_FILENO);

            // Output redirect : For all but the last token
            if(i != number_of_pipes)
            {
                dup2(pipe_fd[1], STDOUT_FILENO);
            }

            close(pipe_fd[0]);
            ash_redirect();

            // If the last token redirects output, we exit coz
            // ash_redirect has executed the command
            if(i == number_of_pipes)
            {
                for(int i = 0 ; i < strlen(token) ; i++)
                {
                    if(token[i] == '>')
                        exit(0);
                }
            }

            // Avoid multiple copies
            for(int i = 0 ; i < strlen(token) ; i++)
            {
                if(token[i] == '<')
                    exit(0);
            }

            ash_execute();
            exit(0);
        }
        // Parent Process
        else
        {
            waitpid(pid, NULL, 0);
            close(pipe_fd[1]);
            new_input = pipe_fd[0];
        }
        
        token = strtok(NULL, "|");
    }
}

int get_pipe_number()
{
    int n = 0;
    for(int i = 0 ; i < strlen(parsed_input) ; i++)
    {
        n += (parsed_input[i] == '|');
    }
    return n;
}