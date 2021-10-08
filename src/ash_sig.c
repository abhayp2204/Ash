#include "../include/shell.h"
#include "../include/functions.h"
#include "../include/variables.h"

// sig 2 9 : Sends signal 9 to process with position 2
void ash_sig()
{
    // Get the position and signal
    char* token = malloc(100);
    token = strtok(duplicate, " ");

    // Syntax error : No parameters
    token = strtok(NULL, " ");
    if(!token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    int pos = strtol(token, &token, 10);

    // Syntax error : Insufficient parameters
    token = strtok(NULL, " ");
    if(!token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    int signal = strtol(token, &token, 10);

    // Syntax error : Too many parameters
    token = strtok(NULL, " ");
    if(token)
    {
        cprint("ash_sig", "Syntax : sig <process_pos> <signal_no>");
        return;
    }
    strcpy(duplicate, parsed_input);

    // Invalid process position
    if(pos < 0 || child_process[pos].pid == NOT_CREATED)
    {
        cprint("ash_sig", "This process position does not exist");
        return;
    }

    // Invalid signal
    if(kill(child_process[pos].pid, signal) < 0)
    {
        cprint("ash_sig", "Invalid signal");
        return;
    }
}