#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void is_dir_st(char* path);
void invalid_target(char* path);
int is_dir(char* path);

int main()
{
    char path[50];
    fgets(path, sizeof(path), stdin);
    path[strlen(path)-1] = '\0';

    printf("%s\n", is_dir(path)?"Valid":"Invalid");
}

int is_dir(char* path)
{    
    DIR* dir = opendir(path);
    if(!dir) return 0;
    closedir(dir);
    return 1;
}