Manual for Myshell


Internal Commands:


        cd [d]
        
                Changes the current working directory to the one specified after cd.
                If the directory specified after cd does not exist, an error will be displayed.
                If a directory is not specified after cd, the current working directory is displayed.

        clr

                Clears the terminal screen

        dir [d] 

                Displays the contents of a directory specified after dir. 
                If no directory is specified, the contents of the current directory are displayed.
        
        environ

                Displays all the environment variables.

        echo [arg1 arg2...]

                Displays all the arguments which follow the echo command.

        help

                displays the user manual.

        pause 

                Pauses the operation of the shell until the Enter key is pressed.

        quit 
        
                Exits the shell.


Environment Concepts: 
       
       
        Environment variables are variable values within the system that are accessed by computer processes. They play a role in modifying how these processes operate on a computer. These variables are present across all operating systems, serving to inform the system about specific settings or conditions.

        To display all the environment variables in your shell, the 'environ' command can be employed. This command outputs a list of all the presently established environment variables. The output lists each variable on a separate line, with the variable name and its value divided by an equals sign (=).


I/O Redirection:


        I/O redirection is a feature in myshell that allows you to configure 
        how input and output streams flow between processes and files.

        To redirect input, use `commandName < fileName` to specify the input file for the command.

                cat < file.txt

        To redirect output, use `commandName > fileName` to specify the output file for the command.
        If the file already exists, the contents of the file will be overwritten.

                echo hello > file.txt

        To append the output to an existing file, use `commandName >> fileName`.

                echo goodbye >> file.txt
        


Foreground/Background Execution:


        All programs/commands which are running in the terminal are known as processes.
        
        Foreground execution runs a command in the terminal, 
        requiring users to wait for its completion before executing the next command.

        Background execution, on the other hand, allows a process to run in the background
        while the user can continue executing other commands.

        All processes which are running in the terminal are considered to be
        foreground processes unless specified otherwise.

        To run a command in the background, append an ampersand (&) at the end of the command.

                sleep 10 &


References:


        Newham, C. and Rosenblatt, B. (2005) Learning the bash shell. Beijing: O’Reilly.

        Silberschatz, A., Galvin, P.B. and Gagne, G. (2014) Operating Systems Concepts. Chichester: Wiley.

        Processes (2023) IBM Documentation. Available at: https://www.ibm.com/docs/en/aix/7.3?topic=processes- (Accessed: 14 March  2024).

        Linux man pages (no date) Section 1: user commands - Linux man pages. Available at: https://linux.die.net/man/1 (Accessed: 14 March 2024).


Name: Mohammad Amin Naimimohasses
Student ID: 22319951
Declaration: I acknowledge the DCU academic integrity policy.
