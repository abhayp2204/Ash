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
    char str[] = "OS Assignment is due on Friday";
    char *dup = malloc(strlen(str));
    strcpy(dup, str);

    char *token = malloc(strlen(dup));

    token = strtok(dup, " ");
    while(token)
    {
        printf("token = %s\n", token);
        token = strtok(NULL, " ");
    }
    printf("str = %s\n", str);
}