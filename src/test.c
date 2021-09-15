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

int main()
{
    struct dirent* d;
    DIR* dh = opendir(".");

    while(d = readdir(dh))
    {
        struct stat stats;
        stat(d->d_name, &stats);

        printf("%ld   ", stats.st_size);
        printf("%s  \n", d->d_name);
    }
}