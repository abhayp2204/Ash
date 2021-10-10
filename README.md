# Ash - Abhay's Shell

## Introduction
This is my implementation of a shell. Initially created to develop a deeper understanding of the Linux OS. However, I intend to make this as good as, if not better than Bash. This shell was written entirely in C. Some functions were implemented from scratch, while the rest made use of the exec() family of functions. The commands in this shell are semicolon separated. It also supports redirection and piping, and supports the `Ctrl + Z`, `Ctrl + C` and `Ctrl + D` signals.  
The shell has a `cyan` and `yellow` theme for prompt and a `red` and `magenta` theme for error messages.

## Built In Functions
- `cd`
- `pwd`
- `echo`
- `ls`
- `pinfo`
- `repeat`
- `jobs`
- `sig`
- `fg`
- `bg`
- `replay`

## How to use?
- Download all the files and put them in a certain directory
- Navigate to that directory from the terminal
- Now just run `make`. This will create an executable `ash` file
- Now run `./ash` to execute this file
- `ash`  may not have execute permissions, in which case run `chmod +x ash`, and then run `./ash` again
- That is all :)

## File Structure

### include

#### shell.h
- Includes all the necessary header files.
- Defines some global variables
- Includes a structure to handle background processes.

#### functions.h
- Defines the functions used across the shell.

#### variables.h
- Contains all the global variables used in the shell.

### src

#### main.c
- Gets the SIGCHLD signal ready
- Initializes the process structure
- Loop to run the shell
- Kills zombie children
- Calls ash_main.c

#### ash_main.c
- Displays the banner ie < uname @ hostname : cwd >
- Accepts user input
- Parsed the input to individual commands and executes each command one by one
- Calls ash_execute.c

#### ash_execute.c
- Gets the command word from the parsed input ie cd <path> ---> cd
- Calls the respective function using the command word

#### ash_cd.c
- Implements the bash cd command

#### ash_pwd.c
- Implements the bash pwd command

#### ash_echo.c
- Implements the bash echo command

#### ash_lsc.c
- Extracts the `path` from the input
- Calls ash_ls.c with `path` as input

#### ash_ls.c
- Implements the bash ls command
- This one was tough :(

#### ash_pinfo.c
- Displays Process ID
- Process Status
- Process Memory
- Process Path

#### ash_repeat.c
- Repeats a command n times

#### ash_pipe
- Supports piping

#### ash_redirect.c
- Supports redirection

#### ash_jobs
- Syntax : jobs -<flags>
- Lists the processes spawned by this shell
- -r flag lists only the running processes
- -s flag lists only the stopped processes
- -rs lists both running and stopped process, is equivalent to no flags

#### ash_sig
- Syntax : sig <process_position> <signal_number>
- Sends the specified signal to the process with the given position

#### ash_bg
- Syntax : bg <process_position>
- Changes the status of a process from stopped to running

#### ash_fg
- Syntax : fg <process_position>
- Brings a process to the foreground

#### ash_replay
- Executes a command after a certain interval for a certain period of time

#### ash_general.c
- Executes other commands using the exec family of functions
- Handles forking

#### ash_child.c
- Initializes the process structure
- Pushes a child to the process structure
- Kills zombies ie Closes running processes after ash is closed

#### ash_signals.c
- Handles SIGCHLD, SIGTSTP, SIGINT signals
- Ctrl C terminates a foreground process
- Ctrl Z pulls a foreground process to the background

#### general.c
- Contains utility type functions
- `wprint()` is basically `write()`, made for convenience
- `cprint` is a specialized `printf` to display error messages in color
- The rest have self-explanatory names

### Makefile
- Used for compilation
- Run this using `make` command

## Assumptions
- `ash` can run 1024 background processes. This can be changed in the `shell.h` file. There are certain size limitations on the length of input strings, but it is more than enough for reasonably sized commands. Any errors will soon be fixed.

## Coding Practices
- Readability was a priority while writing this code.
- Functions are named with the snake case convention ie function_name.
- The code is highly modularized. Many functions were used.