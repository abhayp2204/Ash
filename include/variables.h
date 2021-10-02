#ifndef VAR_H
#define VAR_H

#define MAX_CHILDREN 1024

char username[256];
char hostname[256];
char cwd[1024];
char home[1024];
char input[1024];
char d_input[1024];
char parsed_input[1024];
char duplicate[1024];
char command[1024];
char path[1024];
char target[1024];
char prev_dir[1024];

int flag_exit;
int flag_input;
int flag_bg;
int flag_z;
int flag_handler;
int flag_executed;

int number_of_children;
int stdout_fd;

Process fg_process;
Process bg_process;
Process child_process[MAX_BG_PROCESSES];

#endif