#ifndef FUNCTIONS_H
#define FUNCTIONS_H

void ash_main();
void ash_execute();
void ash_clear();                   // Pending...
void ash_cd();
void ash_pwd();
void ash_echo();

void display();
void get_home();
void trim_spaces(char *str);
int is_space(char c);
int is_tab(char c);
void get_command();

#endif