#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Shell functions
void ash_main();
void ash_redirect();
void ash_pipe();
void ash_execute();
void ash_cd();
void ash_pwd();
void ash_echo();
void ash_ls();
void ash_lsc();
void ash_pinfo();
void ash_general();
void ash_repeat();
void ash_jobs(); 
void ash_sig(); 
void ash_fg(); 
void ash_dump();

// Utility functions
void display_banner();
void get_home();
void trim_spaces(char *str);
char* substring(char* str, int a, int b);
int is_space(char c);
int is_space_str(char* c);
int is_tab(char c);
void get_command();
void get_destination();
int get_number_of_tokens();
void wprint(char *str);
int at_home(char *path);
int subdirectory_of_home(char *sub);

// Process handling functions
void handler(int signal);
void kill_children();
void initialize_children();
void kill_zombies();
void push_child();

#endif