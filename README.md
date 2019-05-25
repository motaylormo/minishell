# minishell
A mini-shell that reads and evaluates simple commands from the user. This is my version of the **[42](https://www.42.us.org/)** cadet project `minishell`.

## Functions used
* `getcwd()` to copy the absolute pathname of the current working directory into a buffer
* `chdir()` to change directories
* `access()` to check the accessibility of a file
* `fork()` to fork the process into a parent process and child process
* `wait()` to have the parent process wait until the child processes ends
* `execve()` to run an executable
