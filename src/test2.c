#include <stdio.h>
#include <signal.h>
#include <unistd.h>
void handler(int signum)
{
    printf("\nInside handler function\n");
}

int main()
{
    char str[10];
    signal(SIGINT, handler);

    for (int i = 1;; i++)
    {
        // printf("%d : Inside main function\n", i);
        printf("input : ");
        fgets(str, 10, stdin);
        // sleep(1); // Delay for 1 second
    }
}