#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <stddef.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<sys/wait.h>

#include "../include/functions.h"
#include "general.c"

#include "ash_main.c"
#include "ash_execute.c"
#include "ash_cd.c"
#include "ash_pwd.c"
#include "ash_echo.c"
#include "ash_ls.c"
#include "ash_pinfo.c"
#include "ash_general.c"
#include "ash_signals.c"

int main()
{
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGCHLD, &sa, NULL);

    get_home();
    initialize_children();

    while(!flag_exit)
    {
        ash_main();
    }

    kill_children();
}