#ifndef SHELL_H
#define SHELL_H

// Standard Libraries
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <dirent.h>
#include <pwd.h>
#include <grp.h>
#include <fcntl.h>
#include <time.h>
#include <ctype.h>
#include <signal.h>
#include <stddef.h>
#include <wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/sysinfo.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

// Constraints
#define MAX_BG_PROCESSES 3
#define NOT_CREATED -1

// Child process structure with name of process and pid
typedef struct Process_st
{
	pid_t pid;
	char name[256];
	int pos;
}Process;

#endif