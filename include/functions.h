#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// Shell functions
void ash_main();
void ash_execute();
void ash_cd();
void ash_pwd();
void ash_echo();
void ash_ls();
void ash_lsc();
void ash_pinfo();
void ash_general();
void ash_repeat();

// Utility functions
void display();
void get_home();
void trim_spaces(char *str);
int is_space(char c);
int is_tab(char c);
void get_command();
int get_number_of_tokens();

// Process handling functions
void handler(int signal);
void kill_children();

#endif