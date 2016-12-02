#include <stdio.h>
#include <string.h>
#include <unistd.h>

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
	  for (j = 0; pipelist[j] = strsep(&commands[i], "|"), j++){
            pipelist[j] = strip(pipelist[j]);
	  }
	  parsePipe(pipelist);
	}
	
	

	//Nothing else but commands to parse
	commandSplit(command, commands[i]);
        
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



void parsePipe(char **pipelist){
  int i;
  char *command[512];
  while (*pipelist){
    commandSplit(command, *pipelist);
    
    dup2();

    pipelist++;
  }
}

/*DEPRECATED

//Splits string/commands on semicolons
char **semiBreak(char *str){
    //Count number of semicolons
    int count = 0;
    char *temp = str;
    while (temp = strstr(temp, ";")){   //Move the pointer to the next found ;
        count++;                        //Add to counter
        temp++;                         //And move pointer to next section
    }
    count++; //Min : one command

    printf("number of commands (#semis + 1) : %d\n", count);
    char *commands[count + 1]; //Number of commands + terminating null
    char **ans = commands;
    int i = 0;
    for(i; commands[i] = strsep(&str, ";"); i++);
    commands[i] = 0;
    printf("Check 1\n");

    return ans;
}

*/

//NOTE TO SELF : Create a copy of original pointer so that you can free the
//  the string later since the pointer is no longer the original malloced
//  position if you malloc
//
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
