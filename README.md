# C_shell
  New shell with C for COMP 304 Operating System Project

This project requires mpg123 muzik player
This porject requires readLine GNU library  

please install them first

In this project, an interactive Unix­style operating system shell, named as C_Shell is implemented by using C. C_Shell is capable of reading and executing both system and user­defined commands from the user.
When C_Shell is executed, it provides a simple explanation about C_Shell operations. C_Shell also has a help command which demonstrates user­defined valid C_Shell commands to the user.

PART I:
My­shell project consists of four main parts. In the first part of the project, we are asked to interpret command­line inputs as program invocation, which should be
done by the shell forking and execing the programs as its own child processes. Furthermore, C_Shell must be developed in a way that it supports background execution of programs. An ampersand (&) at the end of the command line indicates that C_Shell is going to return the command line prompt immediately after launching that program. In order to fulfill these requirements, in the main, a child process is created by forking. When the child program is running, according to the command­line inputs, commands are executed either by using execv() function or user­implemented functions, most of which are in header files.

PART II:
In the second part, we are asked to implement history command which holds the most recently given commands by user. C_Shell is able to store commands, show them to user and execute them. Moreover, C_Shell supports scrolling through history by arrow keys. By pressing up arrow key, user gets the most recent command whereas pressing down key shows the least recent one.Note that, activation of the keyboard scroll after entering fallowing command ‘­keyboard’. Hierarchy of history command execution is as follows:
In function main, when commandline inputs starts with “history”, historyCommand() function ­implemented in C_Shell_history_command.h­ is called. HistoryCommand() method calls history related functions based on the second element of the input, i.e. ­c, !!, etc. History functions are defined in C_Shell_history_functions.h and command history is stored in a text file.

PART III:
In third part, bookmark, codesearch, muzik and disko commands are implemented.
In bookmark command, user can bookmark most often used commands, see bookmark list, remove or execute a bookmarked command.

In muzik command, a crontab is set at a user­defined time which plays a user­defined music file. Playlist is kept as a txt file and shown when desired. User can also remove a crontab by this command.

In codesearch method, a word is searched in all files in the current directory and can also be searched recursively in all the subdirectories.

Disko is our custom command which takes a time in seconds and has been changing background for this time. There are three colored images as blue, red and yellow. When user types ”disko 10” for example, backgroud turns routinely into blue, red, and yellow for 10 seconds.

PART IV:
In last part of the project, a Kernel module, called processInfo, is implemented.
When user inputs processInfo with a process pid and process priority, C_Shell loads the module and prints the following information:
­PID (process ID)
­ its parent’s ID
­ executable name,
­ its children list (their process ids and executable names), ­ its thread group list (their ids and executable names)
­ user ID,
­ process voluntary and involuntary context switch count
­ Its nice (priority)
­ Its vruntime
Once the command is called for the first time, C_Shell prompt user's sudo password
to load the module. When the module is loaded, it prints the process info from the module to the screen. Successive calls to the command notifies the user that the module is already loaded. If successive calls use a different process ID, then the previously
loaded kernel module is unloaded and re­loaded with the new arguments. In case no process ID is provided or the process ID is invalid, an error message is printed. The module is removed when C_Shell is exited.
