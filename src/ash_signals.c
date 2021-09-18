#include "../include/shell.h"
#include "../include/variables.h"
#include "../include/functions.h"

void handler(int signal)
{
    // Ignore termination of foreground processes
    if(!flag_bg)
        return;

    char exit_message[1024];
    int status;
    pid_t pid;

	while((pid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		for(int i = 0; i < MAX_BG_PROCESSES ; i++)
		{
			if(child_process[i].pid == pid)
			{
				sprintf(exit_message, "\n%s with pid %d exited %s\n", child_process[i].name, pid, WIFEXITED(status) == 0 ? "abnormally" : "normally");
				wprint(exit_message);
                
				child_process[i].pid = NOT_CREATED;
				child_process[i].pos = NOT_CREATED;
				number_of_children--;
                
				break;
			}
		}
	}

    display_banner();
}

// void handler(int signal)
// {
// 	int status;
// 	int pid;
// 	char exit_message[MAX_COMM];

// 	int term = 0;
// 	while((pid = waitpid(-1, &status, WNOHANG)) > 0)
// 	{
// 		for(int i = 0; i<MAX_BG_PROCESSES; i++)
// 		{
// 			if(child_process[i].pid == pid)
// 			{
// 				term = 1;
// 				// sprintf(exit_message, "\n%s with pid %d exited %s", child_process[i].name, pid, WIFEXITED(status) == 0 ? "abnormally" : "normally");
// 				// write(1, exit_message, strlen(exit_message));
//                 printf("exited normally");
// 				child_process[i].pid = NOT_CREATED;
// 				child_process[i].pos = NOT_CREATED;
// 				number_of_children--;
// 				break;
// 			}
// 		}
// 	}
// 	if(term)
// 	{
//         int c;
//         // while((c = getchar()) != '\n');
// 		display_banner();
// 	}
//     flag_handler = 1;
// }