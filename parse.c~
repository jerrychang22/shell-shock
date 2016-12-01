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
  char **params = semiBreak(line);
  
  //Loop through all ,fork and wait for child processes
  int status;
  while(params){ //While there are commands
    char *commands[256];

    //Split each line of commands by space and parse
    //Make sure each command string is stripped of whitespace before
    //splitting by spaces
    int i = 0;
    while(*params){
        strip(*params);
        commands[i] = strsep(&*params, " ");
        i++;
        printf("num args : %d\n", i);
    }
    commands[i] = 0;
    
    //fork and exec here
    if (fork() == 0){
        execvp(commands[0], commands);
    }    
    else {
        wait(&status);
    }
    //printf("Hi\n");
    params++;
  }
  
}



//Splits string/commands on semicolons
char **semiBreak(char *str){
    //Count number of semicolons
    int count = 0;
    char *temp = str;
    while (temp = strstr(temp, ";")){   //Move the pointer to the next found ;
        count++;                        //Add to counter
        temp++;                         //And move pointer to next section
    }

    
    char *commands[count + 1];
    char **ans = commands;
    int i = 0;
    for(i; commands[i] = strsep(&str, ";"); i++);
    printf("%d\n", i);
    commands[i] = 0;

    return ans;
}



//NOTE TO SELF : Create a copy of original pointer so that you can free the
//  the string later since the pointer is no longer the original malloced
//  position if you malloc
//
//Moves pointer to first non-whitespace character and writes a terminating
//null after last non-whitespace character
void strip(char *str){
    
    //Move pointer to front of leading whitespace
    //isspace checks for spaces, tabs, and newlines (all whitespace)
    while(isspace(*str)) str++;
    if (!str) return;

    //Make a pointer at the end of the string
    //- 1 for terminating null
    char *ending = str + strlen(str) - 1;
    while (isspace(*ending)) ending--;
    *(ending + 1) = 0;  //Write in new terminating null

}
