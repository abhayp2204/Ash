#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

int no_argument();
int multiple_arguments();
void extract_path();
void extract_target();
int invalid_target();

void ash_cd()
{
    // Handle wrong number of arguments
    if(no_argument())
    {
        chdir(home);
        return;
    }
    if(multiple_arguments()) return;

    // Get target / destination
    extract_path();
    extract_target();
    if(invalid_target()) return;

    // Used for cd -
    strcpy(prev_dir, cwd);

    // Go to target
    chdir(target);

    // Suppports combination of replay and cd commands
    if(flag_replaying)
    {
        display_banner();
        printf("\n");
    }
}

int no_argument()
{
    return strlen(parsed_input) <= 3;
}

int multiple_arguments()
{
    for(int i = 3 ; i < strlen(parsed_input) ; i++)
    {
        if(is_space(parsed_input[i]))
        {
            cprint("ash_cd", "Too many arguments were given");
            return 1;
        }
    }
    return 0;
}

void extract_path()
{
    memset(path, 0, strlen(path));
    strcpy(path, substring(parsed_input, 3, strlen(parsed_input) + 1));
}

void extract_target()
{
    if(!strcmp(path, "~"))
    {
        strcpy(target, home);
        return;
    }
    if(!strcmp(path, "-"))
    {
        wprintln(prev_dir);
        strcpy(target, prev_dir);
        return;
    }
    strcpy(target, path);
}

int invalid_target()
{
    struct stat st;
    if(stat(target, &st) != 0)
	{
		cprint("ash_cd", strcat(target, " : Path specified does not exist"));
		return 1;
	}
    return 0;
}