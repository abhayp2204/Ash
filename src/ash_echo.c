#include "../include/functions.h"
#include "../include/variables.h"

void ash_echo()
{
	char *buff;
	buff = (char*)malloc(1024);
	int pos = 0;
	for(int i = 4; i < strlen(parsed_input) ; i++)
    {
		buff[pos++] = parsed_input[i];
    }
	buff[pos] = '\0';

	trim_spaces(buff);
	printf("%s\n", buff);
	
	free(buff);
}