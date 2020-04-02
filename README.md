## xv6_OS_Shell

> Two new system calls are added  
int exit1(int status);  
int wait1(int* status);  
These act like the existing exit and wait syscalls, except passing an exit status from the child back to the waiting parent.  

> Existing Shell is enhanced with the following additions.  

Feature 1: Shell scripts.
If “sh” is run with a single command line argument, it opens that file and reads commands from there instead of from the console.  

Feature 2: && and || operators.
These operators operate much like the “;” sequence operator, except the execution of the subcommand on the left is dependent on the exit status of the subcommand on the right.  
A command “foo && bar” will execute bar only if foo succeeds (exits with status 0).  
A command “foo || bar” will execute bar only if foo fails (exits with a non-zero status).  

Feauture 3: pwd
If "pwd" is run, the path of the current working directory is traced and printed.  

Feature 4: subshells
if "sub" command is run, it launches a subshell which has all the functions of the original shell.

