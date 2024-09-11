/*
Name: Mohammad Amin Naimimohasses
Student ID: 22319951
Declaration: I acknowledge the DCU academic integrity policy.
*/

#include "myshell.h"


// Set the shell environment variable.
void setShellEnvironment() {
    char buffer[MAX_BUFFER];
    // Retrieve the full path of the shell executable.
    if (getcwd(buffer, sizeof(buffer)) != NULL) {
        // Append the shell executable name to the path.
        strcat(buffer, "/myshell");
        // Set the shell environment variable.
        setenv("shell", buffer, 1);
        setenv("PARENT", buffer, 1);

    } else {
        perror("Failed to retrieve current working directory");
    }
}

// Display the shell prompt, including the current working directory.
void displayPrompt() {
    char buffer[MAX_BUFFER];
    // Retrieve and print the current working directory.
    getcwd(buffer, sizeof(buffer));
    strcat(buffer, "> ");
    // Display the prompt.
    fputs(buffer, stdout);
}

// Change the current directory or report the current directory if no path is provided.
void cd(char *path) {   
    char cwd[1000];
    // If no path argument is provided, print the current directory.
    if (path == NULL) {
        printf("The current working directory: %s\n", getcwd(cwd, sizeof(cwd)));
    } 
    // If changing the directory fails, report the error.
    else if (chdir(path) != 0) {
        perror(path);
    } 
    // On successful directory change, update the PWD environment variable.
    else {
        setenv("PWD", path, 1);
    }
}

// Clear the terminal screen.
void clr() {        
    // Execute the clear screen command of the terminal.
    system("clear");
}

// List the contents of the directory specified, or the current directory if none specified.
void dir(char *path) {      
    char cmd[200] = "ls -al ";
    // Append the specified path or use "." for the current directory.
    if (path) {    
        strcat(cmd, path);
    } else {
        strcat(cmd, ".");  
    }
    // Execute the command using system call.
    system(cmd);
}

// Display all environment variables.
void displayEnviron() {         
    // Loop through and print all environment strings.
    while (*environ) {
        printf("%s\n", *environ++);
    } 
}

// Echo the provided arguments to the console.
void echo(char **args) {    
    // Skip the command name to get to the arguments.
    args++;
    // If no arguments, do nothing.
    if (!*args) {
        return;
    }
    // Print each argument followed by a space.
    while (*args) {
        printf("%s ", *args);
        args++;
    }
    // End with a newline.
    printf("\n"); 
}

// Exit the shell.
void quit() { 
    // Terminate the program.
    exit(0);
}

// Pause the shell until the Enter key is pressed.
void pauseExecution() {    
    printf("Press Enter to continue\n");
    // Wait for newline input.
    while (getchar() != '\n');
}

// Display the user manual.
void help() {           
    // Use the more command to paginate viewing the manual.
    system("more manual/readme.md");
}


// Attempt to execute any built-in commands.
int executeBuiltInCommands(char *program, char **args) {
    // Check for each built-in command and execute if matched.
    if (strcmp(program, "quit") == 0) {
        quit();
        return 1; // Command executed.
    }
   
    if (strcmp(program, "clr") == 0) {
        clr();
        return 1; 
    }   

    if (strcmp(program, "cd") == 0) {
        cd(args[1]);
        return 1; 
    }

    if (strcmp(program, "dir") == 0) {
        dir(args[1]);
        return 1; 
    }

    if (strcmp(program, "environ") == 0) {
        displayEnviron();
        return 1; 
    }

    if (strcmp(program, "help") == 0) {
        help();
        return 1; 
    }

    if (strcmp(program, "pause") == 0) {
        pauseExecution();
        return 1; 
    }

    if (strcmp(program, "echo") == 0) {
        echo(args);
        return 1; 
    }

    return 0; // No built-in command matched; not executed.
}


// The code below was adapted from: https://loop.dcu.ie/mod/book/view.php?id=2322719&chapterid=492183

// Fork and attempt to execute as an external program if not a built-in command.

void executeExternalCommand(char **clean_args, int background) {

    // Create a child process.
    pid_t pid = fork();

    // Handle the result of fork().
    switch(pid) {
        case -1: // If fork() returns -1, the attempt to fork failed.
            perror("fork failed"); // Print an error message.
            break;
        case 0: // Child process.
            // Attempt to execute the command passed in clean_args.
            execvp(clean_args[0], clean_args);
            // If execvp returns, it means there was an error executing the command.
            if (errno == ENOENT) { // Command not found.
                fprintf(stderr, "%s: Command not found\n", clean_args[0]);
            } else { // Other errors.
                perror("execvp failed"); // Print a general failure message.
            }
            exit(EXIT_FAILURE); // Ensure the child process exits with a failure status.
        default: // Parent process.
            // If the command is not meant to run in the background,
            // the parent waits for the child process to finish.
            if (!background) {
                int status;
                waitpid(pid, &status, 0); // Wait for the specific child process to end.
            } else {
                // If the command is meant to run in the background,
                // print the PID of the child process and do not wait for it to finish.
                printf("Running in background, PID: %d\n", pid);
            }
            break;
    }
}


// The code below was adapted from: https://stackoverflow.com/questions/52939356/redirecting-i-o-in-a-custom-shell-program-written-in-c

// Handles input/output redirection and background execution flag for a given command.

int handleIORedirection(char **args, char ***clean_args, int *background) {
    int in, out; // File descriptors for the input and output redirection files.
    static char *args_clean[MAX_ARGS]; // Temporarily stores command arguments excluding redirection operators.
    int cleanidx = 0; // Index for adding elements to args_clean.
    int size = 0; // Stores the total number of arguments in args.

    // Calculate the total number of arguments in args.
    for (size = 0; args[size] != NULL; size++);

    // Iterate through each argument in args to check for redirection operators and background flag.
    for (int j = 0; j < size; j++) {
        // Input redirection ("<")
        if (!strcmp(args[j], "<")) {
            ++j; // Move to the filename argument.
            // Open the file for reading and redirect stdin to it.
            if ((in = open(args[j], O_RDONLY)) < 0) {
                // If opening the file fails, print an error and return -1.
                fprintf(stderr, "Error opening input file: %s\n", args[j]);
                return -1;
            }
            dup2(in, STDIN_FILENO); // Redirect stdin to the file.
            close(in); // Close the file descriptor as it's no longer needed.
            continue;
        }
        // Output redirection (">")
        if (!strcmp(args[j], ">")) {
            ++j; // Move to the filename argument.
            // Create the file for writing and redirect stdout to it.
            out = creat(args[j], 0644);
            dup2(out, STDOUT_FILENO); // Redirect stdout to the file.
            close(out); // Close the file descriptor as it's no longer needed.
            continue;
        }
        // Append output redirection (">>")
        if (!strcmp(args[j], ">>")) {
            ++j; // Move to the filename argument.
            // Open the file for append mode and redirect stdout to it.
            int append = open(args[j], O_CREAT | O_RDWR | O_APPEND, 0644);
            dup2(append, STDOUT_FILENO); // Redirect stdout to the file.
            close(append); // Close the file descriptor as it's no longer needed.
            continue;
        }
        // Background execution ("&")
        if (!strcmp(args[j], "&")) {
            *background = 1; // Set the background execution flag.
            continue; // Skip adding "&" to clean arguments.
        }
        // If the argument is not a redirection operator or "&", add it to args_clean.
        args_clean[cleanidx++] = args[j];
    }
    // Mark the end of the arguments in args_clean.
    args_clean[cleanidx] = NULL;

    // Update the pointer to point to the cleaned arguments array.
    *clean_args = args_clean;

    return 0; // Indicate success.
}


// Check if a command is intended to run in the background.
int checkForBackgroundExecution(char **args) {
    while (*args != NULL) {
        if (strcmp(*args, "&") == 0) {
            *args = NULL; // Set the argument to NULL to mark the end of the command.
            return 1; // Return 1 to indicate background execution.
        }
        args++; // Move to the next argument.
    }
    return 0; // Return 0 if background execution flag is not found.
}


void restoreStdInOut(int orig_in, int orig_out) {
    // Restore stdin and stdout from the saved file descriptors.
    dup2(orig_in, STDIN_FILENO);
    close(orig_in);
    dup2(orig_out, STDOUT_FILENO);
    close(orig_out);
}


void executeProgram(char *program, char **args) {
    // Check if the command should run in the background.
    int background = checkForBackgroundExecution(args);

    // Save the current stdin and stdout file descriptors.
    int orig_in = dup(STDIN_FILENO), orig_out = dup(STDOUT_FILENO);
    char **clean_args;

    // handleIORedirection(args, &clean_args, &background); 
    if (handleIORedirection(args, &clean_args, &background) < 0) {
        restoreStdInOut(orig_in, orig_out); // Restore the original stdin and stdout.
        return; // Return to prompt without executing the program.
    }

    // Check if the command is a built-in command and execute if so.
    if (executeBuiltInCommands(program, clean_args)) {
        restoreStdInOut(orig_in, orig_out);
        return;
    }

    // Fork and attempt to execute as an external program if not a built-in command.
    executeExternalCommand(clean_args, background);
    restoreStdInOut(orig_in, orig_out);
    return;
}