#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// Functions
void get_input();
void remove_leading_semicolons();
void remove_trailing_semicolons();
void parse_and_execute();
char* get_relative_path(char cwd[]);

// Main
void ash_main()
{
    display_banner();
    get_input();
    remove_leading_semicolons();
    remove_trailing_semicolons();
    parse_and_execute();
}

void display_banner()
{
    char banner[2048];

    // Username, Hostname, cwd
    getlogin_r(username, sizeof(username));
    gethostname(hostname, sizeof(hostname));
    memset(cwd, 0, sizeof(cwd));
    getcwd(cwd, sizeof(cwd));

    // Home directory : Display ~
    if(at_home(cwd))
    {
        sprintf(banner, "<%s@%s:~> ", username, hostname);
        wprint(banner);
        return;
    }

    // Not a subdirectory : Display the entire path
    if(!subdirectory_of_home(cwd))
    {
        sprintf(banner, "<%s@%s:%s> ", username, hostname, cwd);
        wprint(banner);
        return;
    }
    
    // Subdirectory : Display relative path
    sprintf(banner, "<%s@%s:%s> ", username, hostname, get_relative_path(cwd));
    wprint(banner);
}

char* get_relative_path(char cwd[])
{
    char *relative_path = malloc(strlen(cwd) + 2);
    relative_path[0] = '~';
    relative_path[1] = '/';
    int j = 2;

    for(int i = strlen(home) + 1 ; i < strlen(cwd) ; i++)
    {
        relative_path[j++] = cwd[i];
    }
    relative_path[j] = '\0';

    return relative_path;
}

void get_input()
{
    fgets(input, sizeof(input), stdin);
}

void remove_leading_semicolons()
{
    int pos = 0;
    while(input[pos] == ';' || input[pos] == ' ')
        pos++;
    strcpy(input, substring(input, pos, strlen(input)));
}

void remove_trailing_semicolons()
{
    int pos = strlen(input) - 1;
    while(input[pos] == ';' || input[pos] == ' ')
        pos--;
    strcpy(input, substring(input, 0, pos + 2));
}

void parse_and_execute()
{
    int pos = 0;
    int pos2 = pos;
    int flag_play = 1;

    while(flag_play)
    {
        flag_child_executed = 0;
        pos2 = pos;
        while(input[pos++] != ';')
        {
            if(pos > strlen(input))
            {
                flag_play = 0;
                break;
            }
        }
        strcpy(parsed_input, substring(input, pos2, pos));
        trim_spaces(parsed_input);
        
        // Skip empty commands
        if(!strlen(parsed_input))
            continue;
        

        get_command();
        // ash_redirect();
        // ash_pipe();

        if(flag_child_executed)
            continue;

        ash_execute();
    }
}