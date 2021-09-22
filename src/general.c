#include "../include/shell.h"
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
	// strcpy(str, replace_tab_with_space(str));
	// printf("str = %s\n", str);

    int i, pos = 0;

	for(i = 0; str[i]; ++i)
  	{
		
		if(is_tab(str[i]))
			str[i] = ' ';

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

int is_space_str(char *str)
{
	return !strcmp(str, " ");
}

int is_tab(char c)
{
    return (c == '\t');
}

void get_command()
{
    // The command is the first word of the parsed input
    char *copy = malloc(strlen(parsed_input));
    strcpy(copy, parsed_input);
    strcpy(command, strtok(copy, " "));
}

int get_number_of_tokens()
{
	char* copy = malloc(strlen(parsed_input));
	char* token = malloc(strlen(parsed_input));

	strcpy(copy, parsed_input);
	token = strtok(copy, " ");
	int number_of_tokens = 0;

	while(token)
	{
		number_of_tokens++;
		token = strtok(NULL, " ");
	}

	return number_of_tokens;
}

int at_home(char *path)
{
	return !strcmp(path, home);
}

int subdirectory_of_home(char *sub)
{
	// A subdirectory's path must be greater than home
	if(strlen(sub) < strlen(home))
		return 0;

	// Check if the path is a subdirectory
	for(int i = 0 ; i < strlen(home) ; i++)
	{
		if(sub[i] != home[i])
			return 0;
	}
	return 1;
}

void wprint(char *str)
{
	write(STDOUT_FILENO, str, strlen(str));
}

char* substring(char* str, int a, int b)
{
	char* substr = (char*)malloc(strlen(str) * sizeof(char));
	for(int i = a ; i < b ; i++)
	{
		substr[i-a] = str[i];
	}
	substr[b-a-1] = '\0';
	return substr;
}