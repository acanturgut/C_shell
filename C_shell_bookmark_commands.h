#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 80

#include "C_shell_bookmark_functions.h"

void bookmark_comments(char *args[], char *cur_dir ,char temp_directory[],char temp_cwd[], char cwd[],char directory[],char *fp){

  if(strncmp(args[0],"bookmark",8) == 0 && args[1]==NULL && args[2]==NULL){

    printf("C_SHELL Warning ----> Try --> bookmark help command  <-- \n");

  }else if(strncmp(args[0],"bookmark",8) == 0 && args[1] != NULL && args[2]==NULL){

    if (strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"help",4) == 0 && args[2]==NULL){

      printf("bookmark \"some command\" <-- This saves your commands\n");
      printf("bookmark -l   <-- List all saved commands\n");
      printf("bookmark -i x <-- executes x'th command \n");
      printf("bookmark -d x <-- delete from bookmark\n");

    }else if (strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"-l",2) ==0 && args[2]==NULL){

      bookmark_list(fp);

    }else if (strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"-i",2) ==0 && args[2]==NULL){

      printf("C_SHELL Warning ----> Try --> bookmark help command  <-- \n");

    }else if (strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"-d",2) ==0 && args[2]==NULL){

      printf("C_SHELL Warning ----> Try --> bookmark help command  <-- \n");

    }else{

      if(bookmark_valid(args) == 1){

        bookmark_command(args[1],fp);
      }
    }
  }else if(strncmp(args[0],"bookmark",8) == 0 && args[1] != NULL && args[2] !=NULL){

    if (strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"-i",2) == 0 && args[2] !=NULL){
      // TODO: "EXECUTE SELECTED"
      int lineNo=atoi(args[2]);
      execute_bookmarked_command(args,cur_dir,lineNo,fp,cwd,temp_cwd,temp_directory,directory);

    }else if(strncmp(args[0],"bookmark",8) == 0 && strncmp(args[1],"-d",2) == 0 && args[2] !=NULL){

      int lineNo;
      lineNo=atoi(args[2]);
      clear_from_bookmark_list(lineNo,fp);

    }else{

      if(bookmark_valid(args) == 1){

        int counter;
        counter=2;
        char command2bookmark[MAX_LINE];
        if(args[counter]!=NULL){
          strcpy(command2bookmark,args[1]);
          while(args[counter]!=NULL){
            strcat(command2bookmark," ");
            strcat(command2bookmark,args[counter]);
            counter++;
          }
        }
        bookmark_command(command2bookmark,fp);
      }
    }
  }
}
