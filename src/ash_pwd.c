#include "../include/functions.h"
#include "../include/variables.h"

void ash_pwd()
{
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
}