#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "parse.h"

int main(){


  int status;
  //fork here and have parent wait
  pid_t childPid = fork();

  
  //child successfully created
  if (childPid == 0){
    execvp(params[0], params);
    //exit();
  }
  
  //instructions for parent
  else{
    wait(&status);
  }
  
  return 0;

  
}
