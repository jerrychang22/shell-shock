# shell-shock

by Jerry Chang

Features : 
    Simple command parsing
        Forks when command is called
        Parses on ;
        Simple piping
        Simple redirection

Bugs : 
    Plenty.
    Piping causes the main function to loop a number of times
    Redirection is wonky?

Files :
    main.c : Simple function that starts it all
    parse.c : All the parsing functions
        void run()
            Args : None
            Return : None
            Function : Starts the continuous loop for parsing

        void parseParams();
            Args : None
            Return : None
            Function : Parses in lines and runs the commands. Calls others

        void commandSplit(char ** command, char *commands)
            Args : char ** command, char *commands
            Return : None
            Function : Splits commands by " " and places the pieces into command

        void parsePipe(char *commands)
            Args : char *commands
            Return : None
            Function : Splits commands by | then pipes the first into the second

        void parseRedir(char *commands)
            Args : char *commands
            Return : None
            Function : Splits commands by various redirection characters and
                applies the appropriate behavior

        char *strip(char *str)
            Args : char *str
            Return : char *
            Function : Takes a string and strips all leading and trailing
                whitespace

