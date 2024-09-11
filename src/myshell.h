/*
Name: Mohammad Amin Naimimohasses
Student ID: 22319951
Declaration: I acknowledge the DCU academic integrity policy.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <errno.h>

// Maximum buffer size for reading input.
#define MAX_BUFFER 1024
// Maximum number of arguments that can be parsed from input.
#define MAX_ARGS 200
// Characters used to separate commands and arguments in input.
#define SEPARATORS " \t\n\r"           

// External environment variables.
extern char **environ;

// Function prototypes.
void setShellEnvironment(); // Set the shell environment variables.
void displayPrompt(); // Display the shell prompt.
void clr(); // Clear the screen.
void cd(char *path); // Change the current working directory.
void dir(char *path); // List the contents of a directory.
void displayEnviron(); // Display the shell environment variables.
void help(); // Display the help menu.
void pauseExecution(); // Pause the shell until the user presses Enter.
void quit(); // Exit the shell.
void echo(char **args); // Display the arguments passed to it.
void executeProgram(char *program, char **args); // Execute a program with arguments.
void restoreStdInOut(int orig_in, int orig_out); // Restore stdin and stdout.
int executeBuiltInCommands(char *program, char **args); // Execute built-in commands.
int checkForBackgroundExecution(char **args); // Check if a command should run in the background.
int handleIORedirection(char **args, char ***clean_args, int *background); // Handle I/O redirection.
void executeExternalCommand(char **clean_args, int background); // Execute an external command.