#include "../include/functions.h"

void ash_main()
{
    display_banner();
    Input();

    int parsing_complete = 0;
    int pos = 0;
    while(1)
    {
        // User wants to exit
        if(flag_exit)
        return;

        // Parsing complete
        if(parsing_complete)
        break;

        // There is no input
        if(!strlen(input))
        return;

        // Parse by ;
        int i = 0;
        while(input[pos] == ';')
        pos++;

        memset(parsed_input, 0, sizeof(parsed_input));
        for(; input[pos] ; pos++)
        {
            if(input[pos] == ';')
            break;

            if(input[pos] == '\n')
            {
                parsing_complete = 1;
                break;
            }

            parsed_input[i++] = input[pos];
        }
        if(pos >= strlen(input))
        parsing_complete = 1;

        trim_spaces(parsed_input);
        // printf("parsed_input = %s\n", parsed_input);

        ash_execute();
    }
}