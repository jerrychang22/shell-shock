#include <stdio.h>
#include <string.h>
#include <unistd.h>

int parse(){
  
  //make all this a seperate function to call
  //it all again after command finishes

  //char **parseParams(){
  char store[256];
  char *line = store;
  printf("Hi\n");
  fgets(store, 256, stdin);

  //fix with strchr
  *(strchr(line, "\n")) = 0;
  //line[strlen(line) - 1] = 0;

  char *params[10];
  int i = 0;
  //fix so that it operates on ";" and "|" and "<<>>"
  for (i; params[i] = strsep(&line, " "); i++);
  params[i] = 0;
  //return params;
  //}



  
}