#include "../include/functions.h"
#include "../include/variables.h"

void display()
{
    write(1, "\e[1;1H\e[2J", 10);
}

void display_banner()
{
    gethostname(host_name, sizeof(host_name));
    getcwd(cwd, sizeof(cwd));
    getlogin_r(username, sizeof(username));

    // If we are at home directory, display ~
    if(!strcmp(cwd, home))
    {
        printf("<%s@%s:~> ", username, host_name);
        return;
    }
    // If the current directory is not a subdirectory of the home directory, display the entire path
    if(strlen(cwd) < strlen(home))
    {
        printf("<%s@%s:%s> ", username, host_name, cwd);
        return;
    }
    // Check if the current directory is a subdirectory of home
    int sub_home = 1;
    for(int i = 0 ; i < strlen(home) ; i++)
    {
        if(cwd[i] != home[i])
        {
            sub_home = 0;
            break;
        }
    }
    // The current directory is not a subdirectory of home
    if(!sub_home)
    {
        printf("<%s@%s:%s> ", username, host_name, cwd);
        return;
    }
    // The current directory is a subdirectory of home
    // Print ~/<relative_path>
    char *dir = malloc(strlen(cwd) + 2);
    dir[0] = '~';
    dir[1] = '/';
    int j = 2;
    for(int i = strlen(home) + 1 ; i < strlen(cwd) ; i++)
    {
        dir[j++] = cwd[i];
    }
    printf("<%s@%s:%s> ", username, host_name, dir);
    free(dir);
}

void get_home()
{
    getcwd(home, sizeof(home));
}

void Input()
{
    fgets(input, sizeof(input), stdin);
    // printf("input = %s\n", input);
}

// Auth
void trim_spaces(char *str)
{
    int i, pos = 0;

	for(i = 0; str[i]; ++i)
  	{
    	if(is_space(str[i]) && (i == 0 || is_space(str[i-1])))
    		;
    	else if(is_space(str[i]))
    		str[pos++] = ' ';
    	else
    		str[pos++] = str[i];
  	}

  	str[pos] = '\0';
  	pos--;
  	while(pos>=0 && (str[pos] == ' ' || str[pos] == '\t'))
  		str[pos--] = '\0';
  	str[pos+1] = '\0';
}

int is_space(char c)
{
    return (c == ' ');
}

void get_command()
{
    // The command is the first word of the parsed input
    char *copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);
    strcpy(command, strtok(copy, " "));
}