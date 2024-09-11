/*
Name: Mohammad Amin Naimimohasses
Student ID: 22319951
Declaration: I acknowledge the DCU academic integrity policy.
*/


// The code below was adapted from: https://loop.dcu.ie/mod/book/view.php?id=2322719&chapterid=492181

#include "myshell.h"

int main(int argc, char **argv) {
    char buf[MAX_BUFFER];
    char *args[MAX_ARGS];
    char **arg;
    FILE *input = stdin; // Default to stdin

    // Set the shell environment variables.
    setShellEnvironment();

    // Check if the shell was invoked with a batch file as an argument.
    if (argc == 2) {
        // Attempt to open the batch file and set it as the input stream.
        input = fopen(argv[1], "r");
        if (input == NULL) {
            perror("Failed to open batch file");
            return 1; // Exit with error code.
        }
    }

    // Main loop to process user input from the determined input stream.
    while (!feof(input)) {
        // Display the shell prompt only if in interactive mode.
        if (input == stdin) {
            displayPrompt();
        }

        // Read a line of input.
        if (fgets(buf, MAX_BUFFER, input)) {
            // Initialize args with the first token found in buf.
            arg = args;
            *arg++ = strtok(buf, SEPARATORS);

            // Continue parsing buf and populate args with tokens found.
            while ((*arg++ = strtok(NULL, SEPARATORS)));

            // If there's at least one argument (i.e., a command was entered), execute it.
            if (args[0]) {
                executeProgram(args[0], args);
            }
        }
    }

    // Close the input stream if it's not stdin (i.e., a file in batch mode).
    if (input != stdin) {
        fclose(input);
    }

    return 0;
}
