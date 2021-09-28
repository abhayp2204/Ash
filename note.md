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
