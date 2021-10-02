# Specification 1 : IO Redirection
## write(>)
## append(>>)
## read(<)
- Need to create escape sequence for semicolons.
- cat works but echo does not (builtin).

# Specification 2 : Pipe
- example 1:  cat file.txt | wc
- example 2:  cat sample2.txt | head -7 | tail -5

# Specification 3 : IO and Pipe

# Specification 4 : User Defined Commands

## jobs
Prints a list of all currently running background processes spawned by the shell in alphabetical order of the command name, along with their job number (a sequential number assigned by your shell), process ID and their state, which can either be running or stopped.

Flags:
-r : Print only the running processes
-s : Print only the stopped processes

## sig


## fg
## bg

# Specification 5 : Signal Handling
## Ctrl Z
## Ctrl C
## Ctrl D

# Rules
- `Forbidden`:   popen(), pclose(), system()
- `Recommended`: getenv(), signal(), dup(), dup2(), wait(), waitpid(), getpid(), kill(), execvp(),
               malloc(), strtok(), fork(), setpgid(), setenv(), getchar()
- `perror` to handle errors
- `fork()` to create child processes, `wait()` to reap

# Completion

## 1 : Yes
## 2 : Yes
## 3 : Yes
## 4 : No
## 5 : No