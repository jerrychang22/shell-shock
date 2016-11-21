#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(){

  //make all this a seperate function to call
  //it all again after command finishes

  //char **parseParams(){
  char store[256];
  char *line = store;
  printf("Hi\n");
  fgets(store, 256, stdin);
  line[strlen(line) - 1] = 0;

  char *params[10];
  int i = 0;
  //fix so that it operates on ";"
  for (i; params[i] = strsep(&line, " "); i++);
  params[i] = 0;
  //return params;
  //}

  
  //fork here and have parent wait
  pid_t childPid = fork();

  //child successfully created
  if (childPid == 0){
    execvp(params[0], params);
    //exit();
  }
  
  //instructions for parent
  else{
    
  }
  
  return 0;

  
}
