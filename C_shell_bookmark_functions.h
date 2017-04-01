#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 80

int bookmark_counter=0;

void executeOperationBookmarker(char *line, char temp_cwd[],char temp_directory[],char cwd[],char directory[]){

  int argc = 0;
  char *args[MAX_LINE];
  char *pointer;

  pointer = strtok(line, " ");

  while (pointer && argc < MAX_LINE-1){

    //printf("DEBUGER -executeOP \n");
    args[argc++] = pointer;
    pointer = strtok(NULL, " ");

  }

  args[argc] = NULL;

//  printf("DEBUGER args0 --> %s\n", args[0]);
//  printf("DEBUGER args1 --> %s\n", args[1]);
//  printf("DEBUGER args2 --> %s\n", args[2]);

  if(strcmp(args[0], "cd") == 0){

    execv_cd(args, temp_cwd, temp_directory, cwd, directory);

  }else if(strcmp(args[0], "muzik") == 0){

    muzikCommand(args);

  }else if(strcmp(args[0], "codesearch") == 0){

    codesearch_comments(args,cwd);

  }else{

    linux_Comments(args);
  }
}

void bookmark_list(char fp[]){
  FILE *ptr_file;
  char buf[1000];
  ptr_file =fopen(fp,"r");
  int counter=0;
  while (fgets(buf,1000, ptr_file)!=NULL){
    printf("%d..............%s",counter,buf);
    counter++;
  }
  fclose(ptr_file);
}

void bookmark_command(char command2bookmark[],char fp[]){
  FILE *ptr_file;
  ptr_file =fopen(fp,"a");
  fprintf(ptr_file, "%s\n", command2bookmark);
  fclose(ptr_file);
}

void execute_bookmarked_command(char *args[], char *cur_dir,int lineNo,char fp[],char cwd[],char temp_cwd[], char temp_directory[],char  directory[]){
  char command2execute[MAX_LINE];
  FILE *pf;
  char buf[1000];
  pf =fopen(fp,"r");
  int ln;
  ln=0;
  while (fgets(buf,1000,pf)!=NULL){
    if(ln==lineNo){
      strcpy(command2execute,buf);
      break;
    }
    ln++;
  }
  fclose(pf);

  char str2[sizeof(command2execute)-1];
  if(strlen(command2execute) > 0){
    strcpy(str2, &(command2execute[1]));
  }else{
    strcpy(str2, command2execute);
  }

  int charIndex = 0;

  for(charIndex = 0; str2[charIndex] != '\0'; ++charIndex);

  str2[charIndex-2] = '\0';

  strcpy(command2execute,str2);

  printf("%s\n", command2execute);

  char *token;
  char *arg[MAX_LINE];
  char temp[MAX_LINE];
  strcpy(temp,command2execute);
  token=strtok(temp," ");
  char c[MAX_LINE];
  strcpy(c,token);

  if(strncmp(c,"history",7)==0){
    int i=0;
    while(token!=NULL){
      strcpy(arg[i],token);
      token=strtok(NULL," ");
      i++;
    }

    //printf("DEBUGER: HISTORY ENTER <--\n");

    history_Comments(arg, cur_dir, temp_cwd, temp_directory, cwd ,directory);

  }else{

    //printf("DEBUGER: OTHER COMMANDS - ELSE - ENTER\n");
    executeOperationBookmarker(command2execute, temp_cwd, temp_directory, cwd, directory);

  }
}

void clear_from_bookmark_list(int lineNo, char fp[]){
  FILE *ptr_file;
  FILE *temp_file;
  char buf[1000];
  ptr_file =fopen(fp,"r");
  temp_file=fopen("tempfile.txt","w");
  int index=0;
  while(fgets(buf,1000,ptr_file)!=NULL){
    if(index!=lineNo){
      fprintf(temp_file, "%s", buf);
    }
    index++;
  }
  fclose(ptr_file);
  fclose(temp_file);
  temp_file=fopen("tempfile.txt","r");
  ptr_file=fopen(fp,"w");
  while(fgets(buf,1000,temp_file)!=NULL){
    fprintf(ptr_file, "%s", buf);
  }
  fclose(temp_file);
  fclose(ptr_file);
  remove("tempfile.txt");
}

int bookmark_valid(char *args[]){

  int counter = 0;

  while(args[counter] != NULL){

    counter++;

  }

  int lastIndex = counter-1;
  int firstIndex = 1;

  //printf("DEBUGER: CS-> COUNTER:  %d\n", counter  );
  //printf("DEBUGER: CS-> LASTARGS: %s\n", args[firstIndex]);
  //printf("DEBUGER: CS-> LASTARGS: %s\n", args[lastIndex]);

  char firstString[MAX_LINE] = "-";
  char secondString[MAX_LINE] = "-";

  strcpy(firstString, args[firstIndex]);
  strcpy(secondString, args[lastIndex]);

  //printf("DBG: FS--> %s\n", firstString );
  //printf("DBG: SS--> %s\n", secondString);

  //printf("DEBUGER: CS-> LASTINDEX: %d\n", lastIndex);

  if(lastIndex == 1){

    //printf("DEBUGER: CS-> DONE OK. LASTINDEX: %d\n", lastIndex);

    char firstchar;

    firstchar = firstString[0];

    if(firstchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> First \" Missing ! <-- command\n");
      return -1;

    }

    int charIndex = 0;

    for(charIndex = 0; firstString[charIndex] != '\0'; ++charIndex);

    char endchar;

    endchar = firstString[charIndex-1];

    if(endchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> Last \" Missing ! <-- command\n");
      return -1;

    }

    //  printf("DEBUGER OK. \n");
    //  printf("DEBUGER: --> CHAR INDEX %d\n", charIndex-1 );

  }else{

    char firstchar;

    firstchar = firstString[0];

    if(firstchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> First \" Missing ! <-- command\n");
      return -1;

    }

    int charIndex = 0;

    for(charIndex = 0; secondString[charIndex] != '\0'; ++charIndex);

    char endchar;

    endchar = secondString[charIndex-1];

    if(endchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> Last \" Missing ! <-- command\n");
      return -1;

    }

    //  printf("DEBUGER OK. \n");
    //  printf("DEBUGER: --> CHAR INDEX %d\n", charIndex-1 );

  }

  return 1;
}
