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

// Colors
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define PRIMARY_COLOR ANSI_COLOR_CYAN
#define SECONDARY_COLOR ANSI_COLOR_YELLOW
#define ERROR_COLOR ANSI_COLOR_RED

// Global Variables
#define MAX_BG_PROCESSES 1024
#define NOT_CREATED -1

// typedefs
typedef struct Process_st Process;
// typedef void handler(int, siginfo_t *, void *);

// Structure : Manages Background Processees
struct Process_st
{
	pid_t pid;
	char name[256];
	int pos;
};

#endif