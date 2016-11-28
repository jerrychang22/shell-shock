#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parse.h";

  
  //make all this a seperate function to call
  //it all again after command finishes

char **parseParams(){
    char store[256];
    char *line = store;

    //Make this line print pretty stuff
    printf("Please print command : ");

    //Reads in a line
    fgets(store, 256, stdin);
    //Removes the newline for interpreting
    *(strchr(line, "\n")) = 0;

    char **params = semiBreak(line);
    int i = 0;
    //fix so that it operates on ";" and "|" and "<<>>"
    
    
    for(
    int status;
    for(i; params[i] = strsep(&line, " "); i++);
    params[i] = 0;
    //return params;
    //}


}



//Splits commands on semicolons
char **semiBreak(char *str){
    //Count number of semicolons for malloc purposes
    int count = 0;
    char *temp = str;
    while (temp = strchr(temp, ";")){   //Move the pointer to the next found ;
        count++;                        //Add to counter
        temp++;                         //And move pointer to next section
    }
    free(temp);

    
    char *commands[count + 1];
    char *ans = commands;
    int i = 0;
    for(i; commands[i] = strsep(&str, ";"), i++);
    commands[i] = 0;

    return ans;
}



//NOTE TO SELF : Create a copy of original pointer so that you can free the
//  the string later since the pointer is no longer the original malloced
//  position
//
//Moves pointer to first non-whitespace character and writes a terminating
//null after last non-whitespace character
char *strip(char *str){
    
    //Move pointer to front of leading whitespace
    //isspace checks for spaces, tabs, and newlines (all whitespace)
    while(isspace(*str)) str++;

    //Make a pointer at the end of the string
    //- 1 for terminating null
    char *ending = str + strlen(str) - 1;
    while (isspace(*ending)) ending--;
    *(ending + 1) = 0;  //Write in new terminating null

    return str;
}
