#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void token_info(char* token);

int main()
{
    char str[] = "Hello my name is Sarah";
    char *token = (char*)malloc(strlen(str) * sizeof(char));

    // Hello my name
    token = strtok(str, " ");
    printf("token = %s\n", token);
    token = strtok(NULL, " ");
    printf("token = %s\n", token);
    token = strtok(NULL, " ");
    printf("token = %s\n", token);

    token_info(token);

    // is Sarah
    token = strtok(NULL, " ");
    printf("token = %s\n", token);
    token = strtok(NULL, " ");
    printf("token = %s\n", token);
}

void token_info(char* token)
{
    int n = strlen(token);
    strcat(token, "Trisha");
    printf("\ntoken = %s\n", token);
    printf("size = %d\n\n", n);
}