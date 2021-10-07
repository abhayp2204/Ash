#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// sig 2 9 : Sends signal 9 to process with position 2
void ash_sig()
{
    // Get the position and signal
    char* token = malloc(100);
    token = strtok(duplicate, " ");

    token = strtok(NULL, " ");
    if(!token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    int pos = strtol(token, &token, 10);

    token = strtok(NULL, " ");
    if(!token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    int signal = strtol(token, &token, 10);

    token = strtok(NULL, " ");
    if(token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    strcpy(duplicate, parsed_input);

    // printf("pos = %d\n", pos);
    // printf("sg = %d\n", signal);

    if(pos < 0 || child_process[pos].pid == NOT_CREATED)
    {
        cprint("ash_sig", "This process position does not exist");
        return;
    }

    kill(child_process[pos].pid, signal);
}