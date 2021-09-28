#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int mentioned_file(char* token);

void ash_redirect()
{
    // Initialize flags
    int flag_read = 0;
    int flag_write = 0;
    int flag_append = 0;
    int flag_invalid = 0;

    // Strings to store read and write files
    char* file_write = (char*)malloc(strlen(parsed_input) * sizeof(char));
    char* file_read = (char*)malloc(strlen(parsed_input) * sizeof(char));

    int fd_read;
    int fd_write;

    // Set up token
    char* copy = (char*)malloc(strlen(parsed_input) * sizeof(char));
    strcpy(copy, parsed_input);
    char* token = (char*)malloc(strlen(parsed_input) * sizeof(char));
    token = strtok(copy, " ");

    // 1. Search for <, >, >>
    // 2. Extract file name
    while(token)
    {
        // Search for <
        if(!strcmp(token, "<"))
        {
            flag_read = 1;
            token = strtok(NULL, " ");

            if(!mentioned_file(token))
                return;

            strcpy(file_read, token);
            fd_read = open(file_read, O_RDONLY);
			if(fd_read < 0)
			{
                printf("ash_redirect: Input file not found\n");
                flag_child_executed = 1;
				close(fd_read);
				return;
			}
        }

        // Search for >
        if(!strcmp(token, ">"))
        {
            flag_write = 1;
            token = strtok(NULL, " ");

            if(!mentioned_file(token))
                return;

            strcpy(file_write, token);

            int pos = 0;
            while(parsed_input[pos++] != '>');
            pos--;
            strcpy(parsed_input, substring(parsed_input, 0, pos));
        }

        // Search for >>
        if(!strcmp(token, ">>"))
        {
            flag_append = 1;
            token = strtok(NULL, " ");

            if(!mentioned_file(token))
                return;

            strcpy(file_write, token);

            int pos = 0;
            while(parsed_input[pos++] != '>');
            pos--;
            strcpy(parsed_input, substring(parsed_input, 0, pos));
        }

        // If no file is given
        if(!token)
        {
            flag_invalid = 1;
            break;
        }
        token = strtok(NULL, " ");
    }

    // No redirection necessary
    if(!flag_read && !flag_write && !flag_append)
        return;

    pid_t pid = fork();

    // Forking Failed
    if(pid < 0)
    {
        perror("ash_redirect: Forking failed :(\n");
        return;
    }
    // Child Process
    else if(pid == 0)
    {
        // printf("file name = %s\n", file_write);

        // Read
        if(flag_read)
		{
			int fd_read = open(file_read, O_RDONLY);
			dup2(fd_read, STDIN_FILENO);
			close(fd_read);
            strcpy(parsed_input, command);
		}
        // Write
        if(flag_write)
        {
            int fd_write = open(file_write, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if(fd_write < 0)
			{
				perror("ash_redirect: There was an error opening the file\n");
                exit(0);
			}

			dup2(fd_write, STDOUT_FILENO);
			close(fd_write);
        }
        // Append
        if(flag_append)
        {
            int fd_write = open(file_write, O_WRONLY | O_CREAT | O_APPEND, 0644);
			if(fd_write < 0)
			{
				perror("ash_redirect: There was an error opening the file\n");
                exit(0);
			}

			dup2(fd_write, STDOUT_FILENO);
			close(fd_write);
        }
        
        ash_execute();
        exit(0);
    }
    // Parent Process
    else
    {

        waitpid(pid, NULL, 0);
        free(file_write);
        free(file_read);
        free(copy);
        free(token);

        flag_child_executed = 1;
        return;
    }
}

int mentioned_file(char* token)
{
    if(!token)
    {
        printf("ash_redirect: You forgot to mention a file\n");
        flag_child_executed = 1;
        return 0;
    }
    return 1;
}