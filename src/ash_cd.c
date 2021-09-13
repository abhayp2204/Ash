#include "../include/functions.h"
#include "../include/variables.h"

int no_argument();
int multiple_arguments();
char* extract_path();
int invalid_path();

void ash_cd()
{
    // printf("parsed input = %s\n", parsed_input);

    if(no_argument()) return;
    if(multiple_arguments()) return;
    extract_path();
    if(invalid_path()) return;
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
    for(int i = 3 ; i < strlen(parsed_input) ; i++)
    {
        path[i-3] = parsed_input[i];
    }
}

int invalid_path()
{
    struct stat st;
    if(stat(path, &st) != 0)
	{
		printf("ash_cd: Path specified does not exist\n");
		// newlerr();
		// suc_flag = 1;
		return 1;
	}
    return 0;
}