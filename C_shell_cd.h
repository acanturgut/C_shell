#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

void oneDirectoryBack(char directory[]);
void oneCWDBack(char cwd[]);
void goToMyDirectory(char temp_cwd[],char directory[],char temp_directory[]);
void goBack(char directory[], char cwd[]);
void goSomeWhere(char directory[], char cwd[], char *args[]);

void execv_cd(char *args[],char temp_cwd[],char temp_directory[],char cwd[],char directory[]){
  if(strncmp(args[0],"cd",2) == 0 && args[1]==NULL ){
    goToMyDirectory(temp_cwd,directory,temp_directory);
  }else if (strncmp(args[0],"cd",2) == 0 && strncmp(args[1],"..",2) ==0){
    goBack(directory,cwd);
  }else if(strncmp(args[0],"cd",2) == 0 && strncmp(args[1],"..",2) !=0){
    goSomeWhere(directory,cwd,args);
  }
}

void goToMyDirectory(char temp_cwd[],char directory[],char temp_directory[]){
  chdir(temp_cwd);
  strcpy(directory,temp_directory);
}

void goBack(char directory[], char cwd[]){
  oneDirectoryBack(directory);
  oneCWDBack(cwd);
  chdir(cwd);
}

void goSomeWhere(char directory[], char cwd[], char *args[]){
  strcat(cwd,"/");
  strcat(cwd,args[1]);
  if(access(cwd,F_OK)==-1){
    printf("C_SHELL Warning ---->\"Directory Not Found\"\n" );
    exit(-1);
  } else {
    chdir(cwd);
    strcat(directory,args[1]);
    strcat(directory," >> ");
  }
}

void oneDirectoryBack(char directory[]){
    char *token;
    char temp[1024];
    strcpy(temp,directory);
    token=strtok(temp," >> ");
    strcpy(directory,"");
    while(token!=NULL){
      char *nextToken;
      nextToken=strtok(NULL," >> ");
      if(nextToken!=NULL){
        strcat(directory,token);
        strcat(directory," >> ");
      }
      token=nextToken;
    }
  }

  void oneCWDBack(char cwd[]){
    char *token;
    char temp[1024];
    strcpy(temp,cwd);
    strcat(temp,"/");
    token=strtok(temp,"/");
    strcpy(cwd,"/");
    while(token!=NULL){
      char *nextToken;
      nextToken=strtok(NULL,"/");
      if(nextToken!=NULL){
        strcat(cwd,token);
        strcat(cwd,"/");
      }
      token=nextToken;
    }
  }
