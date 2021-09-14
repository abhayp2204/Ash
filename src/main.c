#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "../include/functions.h"
#include "general.c"
#include "ash_main.c"
#include "ash_execute.c"
#include "ash_cd.c"
#include "ash_pwd.c"
#include "ash_echo.c"

int main()
{
    get_home();

    while(!flag_exit)
    {
        ash_main();
    }
}