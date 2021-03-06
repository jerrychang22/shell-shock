#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

#include "parse.h"



void run(){
    while(1){

        //Make pretty
        printf("Please print command : ");
        parseParams();

    }
}


void parseParams(){
    //store = array of typed in command
    //line = pointer version of store
    //params = commands split by ;
    //commands = array for single command call


    //Reads a line
    char store[256];
    char *line = store;
    fgets(store, 256, stdin);

    //Removes the newline for interpreting
    *(strstr(line, "\n")) = 0;

    //Split all the commands by ;
    /* char **params = semiBreak(line); */

    char *commands[512];
    char *pipelist[512];
    char *redirlist[512];
    char *command[512];

    int i, j, k;
    for (i = 0; commands[i] = strsep(&line, ";"); i++) {
        commands[i] = strip(commands[i]);

	    if (strstr(commands[i], "|") != NULL){
	        parsePipe(commands[i]);
	    }

        if (strstr(commands[i], "<") != NULL || 
                strstr(commands[i], ">") != NULL) 
                    parseRedir(commands[i]);

	    //Nothing else but commands to parse
	    commandSplit(command, commands[i]);
        //printf("%s\n", command[0]);
	    
	    //Built in functions
	    if (strcmp(command[0], "exit") == 0) exit(0);
	    if (strcmp(command[0], "cd") == 0){
	    //if (command[1]
	        chdir(command[1]);
	        continue;
	    }

	    //Fork/exec
	    if (fork() == 0) {
	        execvp(command[0], command);
	    }
	    else {
	        int status;
	        wait(&status);
	    }
    }
}

//Takes a single string command and splits it
//Stores it into list
void commandSplit(char **list, char *commands){
  int i;
  for (i = 0; list[i] = strsep(&commands, " "); i++);
}



void parsePipe(char *commands){
  
    
  int i;
  char *command[512];
  char *pipelist;
  
  pipelist = strsep(&commands, "|");

  int pipes[2];
  pipe(pipes);

  if (fork() == 0){
      dup2(pipes[1], STDOUT_FILENO);
      strip(pipelist);
      commandSplit(command, pipelist);
      execvp(command[0], command);
    }
    
  else{
    if (fork() == 0){
        dup2(pipes[0], STDIN_FILENO);
        strip(commands);
        commandSplit(command, commands);
        execvp(command[0], command);
    }
    else{
        int status;
        wait(&status);
     }
  }
}

void parseRedir(char *redirlist){

    char *first = strsep(&redirlist, "<>");
    char **list;
    strip(redirlist);
    printf("%s,%s\n",first, redirlist); 

    if (strstr(redirlist, "<") != NULL){
        strip(first);
        commandSplit(list, first);
        int fd = open(redirlist, O_RDONLY);
        dup2(fd, STDIN_FILENO);
        if (fork() == 0) execvp(list[0], list);
        else{
            int status;
            wait(&status);
        }
    }


    if (strstr(redirlist, ">") != NULL){
        strip(first);
        commandSplit(list, first);
        int fd = open(redirlist, O_CREAT | O_WRONLY);
        dup2(fd, STDOUT_FILENO);
        if (fork() == 0) execvp(list[0], list);
        else{
            int status;
            wait(&status);
        }
    }


    if (strstr(redirlist, "&>") != NULL){
        char *check = first + strlen(first) - 1;
        if (!strcmp(check, "&"));
        else{
            *check = 0;
            strip(first);
            commandSplit(list, first);
            int fd = open(redirlist, O_CREAT | O_WRONLY);
            dup2(fd, STDOUT_FILENO);
            dup2(fd, STDERR_FILENO);
            if (fork() == 0) execvp(list[0],list);
            else{
                int status;
                wait(&status);
            }
        }
    }

    if (strstr(redirlist, "2>>") != NULL){
        
        char *check = first + strlen(first) - 1;
        if (!strcmp(check, ">"));
        check--;
        if (!strcmp(check, "2"));
        else{
            *check = 0;
            strip(first);
            commandSplit(list, first);
            int fd = open(redirlist, O_CREAT | O_WRONLY);
            dup2(fd, STDERR_FILENO);
            if (fork() == 0) execvp(list[0], list);
            else{
                int status;
                wait(&status);
            }
        }
    }

    if (strstr(redirlist, "2>") != NULL){ 
        char *check = first + strlen(first) - 1;
        if (!strcmp(check, "2"));
        else{
            *check = 0;
            strip(first);
            commandSplit(list, first);
            int fd = open(redirlist, O_CREAT | O_WRONLY);
            dup2(fd, STDERR_FILENO);
            if (fork() == 0) execvp(list[0], list);
            else{
                int status;
                wait(&status);
            }
        }
    }

    if (strstr(redirlist, ">>") != NULL){
        char *check = first + strlen(first) - 1;
        if (!strcmp(check, ">"));
        else{
            *check = 0;
            strip(first);
            commandSplit(list, first);
            int fd = open(redirlist, O_CREAT | O_APPEND);
            dup2(fd, STDOUT_FILENO);
            if (fork() == 0) execvp(list[0], list);
            else{
                int status;
                wait(&status);
            }
        }
    }
    


}


//Moves pointer to first non-whitespace character and writes a terminating
//null after last non-whitespace character
char *strip(char *str){

    //Move pointer to front of leading whitespace
    //isspace checks for spaces, tabs, and newlines (all whitespace)
    while(isspace(*str)) str++;
    if (str == NULL) return;

    //Make a pointer at the end of the string
    //- 1 for terminating null
    char *ending = str + strlen(str) - 1;
    while (isspace(*ending)) ending--;
    *(ending + 1) = 0;  //Write in new terminating null

    return str;
}
