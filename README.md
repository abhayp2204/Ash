# Ash - Abhay's Shell

## Introduction
This is my implementation of a shell. Initially created to develop a deeper understanding of the Linux OS. However, I intend to make this as good as, if not better than Bash. This shell was written entirely in C. Some functions were implemented from scratch, while the rest made use of the exec() family of functions.

## Built In Functions
- cd
- pwd
- echo
- ls
- pinfo
- repeat

## How to use?
- Download all the files and put them in a certain directory.
- Navigate to that directory from the terminal.
- Now just run `make`. This will create an executable `ash` file.
- Now run `./ash` to execute this file.
- `ash`  may not have execute permissions, in which case run `chmod +x ash`, and then run `./ash` again.

## File Structure

### Include
#### shell.h