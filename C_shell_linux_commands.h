// Linux Related Header File

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define MAX_LINE 80

void linux_Comments(char *args[]){

  //printf("DEBUGER: -a linux Comments:  \n");

  char pathf[MAX_LINE] = "-";

  //printf("DEBUGER: -b linux Comments:  \n");

  strcpy(pathf,"/usr/bin/");
  strcat(pathf, args[0]);

//  printf("DEBUGER: -c linux Comments:  \n");
//  printf("DEBUGER: -PATHF %s\n", pathf);

//  printf("DEBUGER: -access: -- %d\n", access( pathf, F_OK ));

  if(access( pathf, F_OK ) != -1) {

    execv(pathf,args);

    int i = 0;

    while (args[i] != NULL) {

//      printf("DEBUGER: -argsi -- %s\n", args[i] );

      i++;
    }

//    printf("DEBUGER: -d linux Comments:  \n");

  }else{

    strcpy(pathf,"/bin/");
    strcat(pathf,args[0]);

    if( access( pathf, F_OK ) != -1 ) {
      //printf("DEBUGER: -/bin/ OK.\n");
      execv(pathf,args);

    }else{

      printf(ANSI_COLOR_RED "C_SHELL Warning ----> \"Comment Not Found\" \n" ANSI_COLOR_RESET);

    }
  }
}
