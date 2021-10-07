#include "include/shell.h"
#include "include/functions.h"
#include "include/variables.h"
#include "src/general.c"

void is_dir_st(char* path);
void invalid_target(char* path);
int is_dir(char* path);

handler* install_signal(int signum, handler* handler)
{
	struct sigaction new_action, old_action;
	
	memset(&new_action, 0, sizeof(struct sigaction));
	new_action.sa_sigaction = handler;
	sigemptyset(&new_action.sa_mask);
	
	new_action.sa_flags = SA_RESTART|SA_SIGINFO;

	if (sigaction(signum, &new_action, &old_action) < 0)
	{
		printf("ash_signals : Signal handling failed\n");
	}
    return (old_action.sa_sigaction);                                           
}

int main()
{
	install_signal(SIGINT, SIGINT_handler);
	install_signal(SIGTSTP, SIGTSTP_handler);

    while(1)
    {
        printf("Wasting your cycles: %d\n", getpid());
        sleep(1);
    }
}

void SIGINT_handler()
{
    wprint("\tI wont die! \t SIGINT\n");
}

void SIGTSTP_handler()
{
    wprint("\tI wont die! \t SIGTSTP\n");
}