This is my version of the **[42](https://www.42.us.org/)** cadet project `minishell` from the UNIX branch.

# minishell
A mini-shell that reads and evaluates simple commands from the user.

## Functions used
* `getcwd()` to copy the absolute pathname of the current working directory into a buffer
* `chdir()` to change directories
* `access()` to check the accessibility of a file
    * `R_OK` read permission
    * `W_OK` write permission
    * `X_OK` execute/search permission
    * `F_OK` existence test
* `execve()` to run an executable
### Processes
* `fork()` to fork the process into a parent process and child process
* `wait()` to have the parent process wait until the child processes ends
### Signals
* `kill()` to send a signal to a process
    * `sig_t` is ?
* `signal()` to catch a signal
    * `pid_t` is a signed int

## Bonuses
* `-p` flag for path prompt
* Management of signals (ctrl-C, ctrl-D)
* Separation of commands with `;`
* Management of execution rights in the PATH

### Termcaps
I begain to just barely dabble in termcaps for this project: just enough to delete the `^C` after ctrl-C.
* `<termcap.h>` needs `-lcurses` in the Makefile
* `tgetent()` loads the entry for _name_
* `tgetstr()` returns the string entry for _id_
* `tgoto()` moves the curser

## Fixes
* Account for 0 columns edgecase
* Usage
