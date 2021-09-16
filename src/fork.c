#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if(pid == -1)
        perror("fork");
    if(pid == 0)
        printf("Child process prints this\n");
    if(pid > 0)
    {
        if(wait(0) == -1)
        {
            perror("wait");
        }
        printf("Parent process pid = %d\n", pid);
        char* argument_list1[] = {"ls", "-l", "-a", NULL};
        char* argument_list2[] = {"gedit", NULL};
        execvp("gedit", argument_list2);
    }
}