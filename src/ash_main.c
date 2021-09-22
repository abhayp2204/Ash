#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// Functions
void get_input();
void parse_and_execute();
void parse_and_execute2();

void remove_leading_semicolons();
void remove_trailing_semicolons();

char* get_relative_path(char cwd[]);

// Main
void ash_main()
{
    display_banner();
    get_input();
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

void parse_and_execute()
{
    int parsing_complete = 0;
    int pos = 0;
    while(1)
    {
        // User wants to exit
        if(flag_exit)
            return;

        // Parsing complete
        if(parsing_complete)
            break;

        // There is no input
        if(!strlen(input))
            return;

        // Parse by ;
        int i = 0;
        while(input[pos] == ';')
        pos++;

        memset(parsed_input, 0, sizeof(parsed_input));
        for(; input[pos] ; pos++)
        {
            if(input[pos] == ';')
            break;

            if(input[pos] == '\n')
            {
                parsing_complete = 1;
                break;
            }

            parsed_input[i++] = input[pos];
        }
        if(pos >= strlen(input))
        parsing_complete = 1;

        trim_spaces(parsed_input);

        ash_execute();
    }
}


void remove_leading_semicolons()
{
    int pos = 0;
    while(input[pos] == ';' || input[pos] == ' ')
        pos++;
    strcpy(input, &input[pos]);
}

void remove_trailing_semicolons()
{
    int pos = strlen(input) - 2;
    while(input[pos] == ';' || input[pos] == ' ')
        pos--;
    
    strcpy(input + pos + 1, "\0");
    input[pos + 1] = '\0';
}