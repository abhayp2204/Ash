#include "../include/functions.h"
#include "../include/variables.h"

void display()
{
    write(1, "\e[1;1H\e[2J", 10);
}

void get_home()
{
    getcwd(home, sizeof(home));
}

// Auth
void trim_spaces(char *str)
{
    int i, pos = 0;

	for(i = 0; str[i]; ++i)
  	{
    	if(is_space(str[i]) && (i == 0 || is_space(str[i-1])))
    		;
    	else if(is_space(str[i]))
    		str[pos++] = ' ';
    	else
    		str[pos++] = str[i];
  	}

  	str[pos] = '\0';
  	pos--;
  	while(pos>=0 && (str[pos] == ' ' || str[pos] == '\t'))
  		str[pos--] = '\0';
  	str[pos+1] = '\0';
}

int is_space(char c)
{
    return (c == ' ');
}

void get_command()
{
    // The command is the first word of the parsed input
    char *copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);
    strcpy(command, strtok(copy, " "));
}