# pipex
Pipex is a project that re-creates the way two commands are piped together via | in the shell. 

The main purpose of the project is to teach what a parent process and a child process is, what functions like fork(), wait(), waitpid(), execve() do, how exactly do they work and how we can make use of them. 
These allow us to instruct the hardware of our computer to handle multiple tasks/jobs at once, from/inside a single codebase (even if the CPU doesn't have multiple cores and has a single core instead).

These should not be confused with multiprogramming concepts such as threads. For that case, there is a seperate project waiting for you ahead (Philosophers), where you are expected to solve the Dining Philosophers problem.

## description

The program takes the infile, outfile to redirect the STDIN (<), STDOUT (>) and 2 commands to pipe. 

Replicated behavior:
- < infile cmd1 | cmd2 > outfile

BONUS: 
1. the program takes the infile, outfile to redirect STDIN (<), STDOUT (>) like previous one, but multiple commands can be accepted.
2. It also supports the double angle bracket for the STDOUT (>>).

Replicated behavior:
- < infile cmd1 | cmd2 | cmd3 | ... | cmdn > outfile

Here document behavior:
- cmd1 << limiter | cmd1 | cmd2 | cmd3 | ... | cmdn >> outfile

The single angle bracket will overwite the entire file, but the double angle bracket will append after the file.

## current status of the project
This uploaded version of the project: 
- DOES NOT handle exit codes properly. I leave it up to you to do research and fix them. 
- DOES NOT handle $ in any way
- DOES NOT handle {}, [], (), *
- DOES handle ' and " inside commands.
