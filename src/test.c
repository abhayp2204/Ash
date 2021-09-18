#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>

void handler(int signal);

int main()
{
    struct sigaction sa;
    sa.sa_handler = &handler;
    sa.sa_flags = SA_RESTART;
    sigaction(SIGTSTP, &sa, NULL);

    char str[10];
    
    while(1)
    {
        printf("input : ");
        fgets(str, 10, stdin);
    }
}

void handler(int signal)
{
    printf("Child killed\n");
    // exit(0);
}