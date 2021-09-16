#include "../include/variables.h"
#include "../include/functions.h"

int is_background();
void remove_and();

void ash_general()
{
    // Implement later
    if(0)
    {
        printf("ash_general: Background process pool is full\n");
        return;
    }

    flag_bg = is_background();

    // Create a child process
    int pid = fork();

    // If fork fails
    if(pid == -1)
    {
        printf("ash_general: Child process could not be created\n");
        return;
    }

    // Child process
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
            {
                break;
            }

			if(parsed_input[i] == ' ')
			{
				args[point++][pos] = '\0';
				pos = 0;
			}
			else
				args[point][pos++] = parsed_input[i];
		}
		args[point][pos] = '\0';

        // printf("args = %s", args[2]);

        // Do not accept commands while a foreground process is running
		if(flag_bg)
			setpgid(0, 0);

        // Execute the command
        if(execvp(args[0], args) < 0)
        {
            printf("ash_general: Command not found\n");
            return;
        }
        return;
    }
    // Parent process
    else
    {
        // Background Process : Terminal can return
        if(flag_bg)
            return;
        
        // Foreground Process : Terminal must wait
        fore_proc.pid = pid;
        strcpy(fore_proc.name, command);
        waitpid(pid, NULL, 0);

        fore_proc.pid = -1;
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