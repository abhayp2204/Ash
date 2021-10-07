#include "../include/shell.h"
#include "../include/variables.h"
#include "../include/functions.h"

int is_background();
void remove_and();

void ash_general()
{
    flag_bg = is_background();

    // If the background process pool is full
    if(flag_bg && number_of_children == MAX_BG_PROCESSES)
    {
        printf("ash_general: No space left for more background processes! :(\n");
        return;
    }

    // Create a child process
    pid_t pid = fork();

    // If fork fails
    if(pid == -1)
    {
        printf("ash_general: Child process could not be created\n");
        return;
    }

    // Child process
    // printf("pid = %d\n", pid);
    if(pid == 0)
    {
        if(flag_bg)
            remove_and();

        // Create args
        char *args[get_number_of_tokens() + 1];
        args[get_number_of_tokens()] = NULL;
        for(int i = 0; i < get_number_of_tokens() ; i++)
			args[i] = (char*)malloc(1024*sizeof(char));

        // Initialize args   
        int pos = 0, point = 0;
		for(int i = 0 ; i < strlen(parsed_input) ; i++)
		{
            if(point == get_number_of_tokens())
                break;

			if(parsed_input[i] == ' ')
			{
				args[point++][pos] = '\0';
				pos = 0;
			}
			else
				args[point][pos++] = parsed_input[i];
		}
		args[point][pos] = '\0';

        // Do not accept commands while a foreground process is running
		if(flag_bg)
			setpgid(0, 0);

        // Execute the command
        if(execvp(args[0], args) < 0)
        {
            cprint("ash_general", "Command not found");

            // Terminal failed to exit immediately after wrong command was entered
            // Hence, an extra exit was necessary
            flag_exit = 1;
            return;
        }
        return;
    }
    // Parent process
    else
    {
        // Background Process : Terminal can return
        if(flag_bg)
        {
            push_child(pid);
            return;
        }
        
        // Foreground Process : Terminal must wait
        fg_process.pid = pid;
        strcpy(fg_process.name, command);
        waitpid(pid, NULL, WUNTRACED);
        fg_process.pid = -1;
    }
}

int is_background()
{
    for(int i = 0 ; i < strlen(parsed_input) ; i++)
    {
        if(parsed_input[i] == '&')
        {
            return 1;
        }
    }
    return 0;
}

void remove_and()
{
    char *copy = malloc(strlen(parsed_input) - 3);
    int number_of_tokens = get_number_of_tokens() - 1;
    int spaces = 0;

    for(int i = 0 ; i < strlen(parsed_input) ; i++)
    {
        if(parsed_input[i] == ' ')
            spaces++;

        if(spaces == number_of_tokens)
        {
            copy[i] = '\0';
            break;
        }
        copy[i] = parsed_input[i];
    }
    strcpy(parsed_input, copy);
}