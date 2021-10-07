// #include "../include/shell.h"
// #include "../include/functions.h"
// #include "../include/variables.h"

// void handler(int signal)
// {
// 	switch(signal)
// 	{
// 		case SIGINT  : SIGINT_handler()  ; break;
// 		case SIGTSTP : SIGTSTP_handler() ; break;
// 		case SIGCHLD : SIGCHLD_handler() ; break;
// 	}
// }

// // Terminate process
// void SIGCHLD_handler()
// {
// 	// Ignore termination of foreground processes
//     if(!flag_bg)
//         return;

//     char exit_message[1024];
//     int status;
//     pid_t pid;

// 	while((pid = waitpid(-1, &status, WNOHANG)) > 0)
// 	{
// 		for(int i = 0; i < MAX_BG_PROCESSES ; i++)
// 		{
// 			if(child_process[i].pid == pid)
// 			{
// 				sprintf(exit_message, "\n%s with pid %d exited %s\n", child_process[i].name, pid, WIFEXITED(status) == 0 ? "abnormally" : "normally");
// 				wprint(exit_message);
                
// 				pop_child(i);
// 				break;
// 			}
// 		}
// 	}

//     display_banner();
// }



// // Ctrl + Z
// void SIGTSTP_handler()
// {
// 	return;
// 	printf("ombie\n");
// }

// // Ctrl + C
// void SIGINT_handler()
// {
// 	for(int i = 0 ; i < MAX_BG_PROCESSES ; i++)
//     {
//         if(child_process[i].pid == NOT_CREATED)
//             continue;

//         kill(child_process[i].pid, SIGINT);
//     }
// }

// void pop_child(int i)
// {
// 	child_process[i].pid = NOT_CREATED;
// 	child_process[i].pos = NOT_CREATED;
// 	child_process[i].name[0] = '\0';
// 	number_of_children--;
// }