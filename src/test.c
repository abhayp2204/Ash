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

int main()
{
    int pid1 = fork();
    if(pid1 == -1)
    {
        printf("Error creating process\n");
        return 1;
    }
    if(pid1 == 0)
    {
        sleep(4);
        printf("Finished execution of slow process %d!\n", getpid());

        return 0;
    }

    int pid2 = fork();
    if(pid2 == -1)
    {
        printf("Error creating process\n");
        return 1;
    }
    if(pid2 == 0)
    {
        sleep(1);
        printf("Finished execution of fast process %d!\n", getpid());

        return 0;
    }

    int p1 = waitpid(pid1, NULL, 0);
    printf("Waited for %d\n", p1);

    int p2 = waitpid(pid2, NULL, 0);
    printf("Waited for %d\n", p2);

    return 0;
}