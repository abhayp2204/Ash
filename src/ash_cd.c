#include "../include/functions.h"
#include "../include/variables.h"

int no_argument();
int multiple_arguments();
void extract_path();
void extract_target();
int invalid_target();

void ash_cd()
{
    // Only 1 argument must be passed
    if(no_argument()) return;
    if(multiple_arguments()) return;

    // Get target / destination
    extract_path();
    extract_target();
    if(invalid_target()) return;

    strcpy(prev_dir, cwd);
    chdir(target);
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

void extract_path()
{
    memset(path, 0, strlen(path));
    for(int i = 3 ; i < strlen(parsed_input) ; i++)
    {
        path[i-3] = parsed_input[i];
    }
    strcpy(target, path);
}

void extract_target()
{
    if(!strcmp(path, "~"))
    {
        strcpy(target, home);
    }
    if(!strcmp(path, "-"))
    {
        strcpy(target, prev_dir);
    }
}

int invalid_target()
{
    struct stat st;
    if(stat(target, &st) != 0)
	{
		printf("ash_cd: Path specified does not exist\n");
		// newlerr();
		// suc_flag = 1;
		return 1;
	}
    return 0;
}