#include "../include/functions.h"
#include "../include/variables.h"

void find_flags();
void reset_flags();

void ash_lsc()
{
    char* token = malloc(strlen(parsed_input)*10);

    int n = get_number_of_tokens(parsed_input);
    int k = 0;

    // Input is only ls
    if(!strcmp(parsed_input, "ls"))
    {
        ash_ls(".");
        return;
    }

    // Skip first token, that is 'ls'
    while(parsed_input[k++] != ' ');

    // Parse and call ls
    int flag_ls = 0;
    for(int i = 1 ; i < n ; i++)
    {
        while(parsed_input[k] == '-')
        {
            n--;
            while(parsed_input[k++] != ' ' && k < strlen(parsed_input));

            if(k == strlen(parsed_input))
            {
                if(!flag_ls)
                    ash_ls(".");
                return;
            }
        }

        int pos = 0;
        while(parsed_input[k] != ' ' && k < strlen(parsed_input))
        {
            token[pos++] = parsed_input[k++];
        }
        k++;
        token[pos] = '\0';

        printf("%s:\n", token);

        if(!strcmp(token, "~"))
            strcpy(token, home);

        ash_ls(token);
        flag_ls = 1;
        printf("\n");
    }

    free(token);
}