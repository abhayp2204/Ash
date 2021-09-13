#include "../include/functions.h"
#include "../include/variables.h"

int no_argument();
int multiple_arguments();
char* extract_path();
int valid_path();

void ash_cd()
{
    // printf("parsed input = %s\n", parsed_input);
    if(no_argument()) return;
    if(multiple_arguments()) return;
    char *path = extract_path();

}

int no_argument()
{
    if(strlen(parsed_input) <= 3)
    {
        printf("ash_cd : No argument was given\n");
        return 1;
    }
    return 0;
}

int multiple_arguments()
{
    for(int i = 3 ; i < strlen(parsed_input) ; i++)
    {
        if(is_space(parsed_input[i]))
        {
            printf("ash_cd : Too many arguments were given\n");
            return 1;
        }
    }
    return 0;
}

char* extract_path()
{
    char* path = malloc(strlen(parsed_input-3));
    for(int i = 3 ; i < strlen(parsed_input) ; i++)
    {
        path[i-3] = parsed_input[i];
    }
    return path;
}

int valid_path()
{
    struct stat st;
}