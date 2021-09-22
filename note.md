# Specification 1 : IO Redirection
## write(>)
- example : echo "Chloe Lock" > media.txt

## append(>>)

## read(<)

# Specification 2 : Pipe

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
