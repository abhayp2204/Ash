#include "include/shell.h"
#include "include/functions.h"
#include "include/variables.h"
#include "src/general.c"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void is_dir_st(char* path);
void invalid_target(char* path);
int is_dir(char* path);

int main()
{
    char *path = malloc(50);
    strcpy(path, "cat < note.md | wc < file.txt");

    char *token = malloc(50);
    token = strtok(path, "|");

    while(token)
    {
        printf("token = %s\n", token);
        token = strtok(NULL, "|");
    }
}