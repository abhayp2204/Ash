// #ifndef SHELL_H
// #include"../include/Shell.h"
// #endif
// #ifndef VARIABLE_H
// #include"../include/Variables.h"
// #endif
// #ifndef FUNC_H
// #include"../include/Functions.h"
// #endif

// void ash_pipe()
// {
// 	// Variables for tokenization
// 	char *token;
// 	char *dup_in = (char*)malloc(MAX_COMM*sizeof(char));
// 	strcpy(dup_in, read_in);

// 	// We extract tokens by space
// 	token = strtok(dup_in, " ");
// 	if(!strcmp(token, "|"))
// 	{
// 		write(2, "ash: pipe: Pipe cannot read from NULL command", strlen("ash: pipe: Pipe cannot read from NULL command"));
// 		newlerr();
// 		suc_flag = 1;
// 		return;
// 	}

// 	int pipe_count = 0;

// 	// Count the number of pipes
// 	token = strtok(NULL, " ");
// 	while(token != NULL)
// 	{
// 		if(!strcmp(token, "|"))
// 		{
// 			pipe_count++;
// 			token = strtok(NULL, " ");
// 			if(token == NULL)
// 			{
// 				write(2, "ash: pipe: Pipe cannot write to NULL command", strlen("ash: pipe: Pipe cannot write to NULL command"));
// 				newlerr();
// 				suc_flag = 1;
// 				return;
// 			}
// 		}

// 		token = strtok(NULL, " ");
// 	}

// 	// If there's no piping, return to normal execution
// 	if(!pipe_count)
// 		return;

// 	strcpy(dup_in, read_in);
// 	token = strtok(dup_in, "|");


// 	int new_in = STDIN_FILENO;
// 	pid_t pid;

// 	// For every | character, make a pipe. The first command reads from stdin, and the last command writes to stdout
// 	// The rest of the commands read from the read end of the previous pipe, and write to the write end of their own pipe.
// 	// Redirection takes precedence over pipes, emulating bash behavior. 
// 	for(int i = 0; i<=pipe_count; i++)
// 	{
// 		int pipes[2];
// 		pipe(pipes);

// 		strcpy(read_in, token);
// 		clean_string(read_in);
// 		token = strtok(NULL, "|");

// 		pid = fork();

// 		// Error in forking
// 		if(pid < 0)
// 		{
// 			write(2, "ash: Failed to spawn new process", strlen("ash: Failed to spawn new process"));
// 			newlerr();
// 			suc_flag = 1;
// 			return;
// 		}

// 		// Child process runs the command, and creates the pipe
// 		if(pid == 0)
// 		{
// 			dup2(new_in, 0);

// 			if(i != pipe_count)
// 				dup2(pipes[1], 1);

// 			close(pipes[0]);
// 			ash_redir();
// 			if(strlen(read_in))
// 				ash_builtin();
// 			exit(0);
// 		}

// 		// Parent waits for termination of the child, and closes the unused write end of the pipe
// 		// Also sets the read end of the pipe for the next command
// 		else
// 		{
// 			waitpid(pid, NULL, 0);
// 			close(pipes[1]);
// 			new_in = pipes[0];
// 		}
// 	}

// 	// Make the command null, and free the copied variable
// 	read_in[0] = '\0';
// 	free(dup_in);
// }