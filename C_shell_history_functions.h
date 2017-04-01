// SHELL HISTORY RELATED FUNCTIONS
// Ahmet Can Turgut - Damla Övek

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 80

int isOurValue(char *arg2){

  if(strncmp(arg2,"!",1) != 0){
    return -1;

  }else{

    char str2[sizeof(arg2)-1];
    if(strlen(arg2) > 0){

      strcpy(str2, &(arg2[1]));

    }else{
      strcpy(str2, arg2);

    }

    return atoi(str2);
  }
}

void store_history(char *filepath, char *args[]){

  FILE *fp = fopen(filepath, "a");
  char tempData[MAX_LINE] = "";

  if (fp != NULL){

    int countW = 0;
    if(args[countW] != NULL)

    while(args[countW] != NULL){

      strcat(tempData, args[countW]);
      strcat(tempData, " ");

      countW++;
    }

    strcat(tempData,"\n");

    if(strncmp(args[0],"history",7) != 0){

      fprintf(fp,"%s",tempData);

    }
  }

  fclose(fp);
}

void executeOperation(char *line, char temp_cwd[],char temp_directory[],char cwd[],char directory[]){

  int argc = 0;
  char *args[MAX_LINE];
  char *pointer;

  pointer = strtok(line, " ");

  while (pointer && argc < MAX_LINE-1){

    //printf("DEBUGER -executeOP \n");
    args[argc++] = pointer;
    pointer = strtok(NULL, " ");

  }

  args[argc-1] = NULL;
  args[argc] = NULL;

  //printf("DEBUGER args0 --> %s\n", args[0]);
  //printf("DEBUGER args1 --> %s\n", args[1]);
  //printf("DEBUGER args2 --> %s\n", args[2]);

  if(strcmp(args[0], "cd") == 0){

    execv_cd(args, temp_cwd, temp_directory, cwd, directory);

  }else if(strcmp(args[0], "muzik") == 0){

    muzikCommand(args);

  }else if(strcmp(args[0], "bookmark") == 0){

    printf("C_SHELL --> SAYS --> bookmark op not executable from history\n");

  }else if(strcmp(args[0], "codesearch") == 0){

    codesearch_comments(args,cwd);

  }else{

    linux_Comments(args);
  }
}
