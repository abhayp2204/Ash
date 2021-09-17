#include "../include/functions.h"

void get_input();
void display_banner();
void parse_and_execute();

void ash_main()
{
    display_banner();
    get_input();
    parse_and_execute();
}

void get_input()
{
    fgets(input, sizeof(input), stdin);
    // printf("input = %s\n", input);
}

void display_banner()
{
    gethostname(host_name, sizeof(host_name));
    memset(cwd, 0, sizeof(cwd));
    getcwd(cwd, sizeof(cwd));
    getlogin_r(username, sizeof(username));

    // If we are at home directory, display ~
    if(!strcmp(cwd, home))
    {
        printf("<%s@%s:~> ", username, host_name);
        return;
    }
    // If the current directory is not a subdirectory of the home directory, display the entire path
    if(!subdirectory_of_home(cwd))
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
    dir[j] = '\0';                                  // why tho?
    printf("<%s@%s:%s> ", username, host_name, dir);
    // printf("\n\ncwd = %s\n", cwd);
    // printf("size of cwd = %ld\n", strlen(cwd));
    free(dir);
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
        // printf("parsed_input = %s\n", parsed_input);

        ash_execute();
    }
}