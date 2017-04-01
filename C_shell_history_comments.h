#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#include "C_shell_history_functions.h"

#define MAX_LINE 80

void history_Comments(char *args[], char *current_dir, char temp_cwd[],char temp_directory[],char cwd[],char directory[]){

  if(strncmp(args[0],"history",7) == 0 && args[1] == NULL){

    FILE *ptr_file;
    char buf[1000];
    ptr_file =fopen(current_dir,"r");
    int historyCounter = 0;
    int historyCounter2 = 0;
    int historyLast10Counter = 0;

    while (fgets(buf,1000, ptr_file)!=NULL){

      historyLast10Counter++; // COUNT HOW MANY HISTORY LOGS EXIST
    }

    printf("DEBUGER: -Last10 %d\n", historyLast10Counter );
    fclose(ptr_file);
    ptr_file =fopen(current_dir,"r");

    while (fgets(buf,1000, ptr_file)!=NULL){

      if(historyLast10Counter <= 10){ // IF LESS THAN 10 print ALL OF THEM

        printf("%d..............%s",historyCounter,buf);

      }else{

        if( historyCounter  >= historyLast10Counter - 10) {

          printf("%d..............%s",historyCounter2,buf);
          historyCounter2++;

        }
      }

      historyCounter++;
    }

    fclose(ptr_file);

  }else if(strncmp(args[0],"history",7) == 0 && strncmp(args[1],"-c",2) == 0 ){

    FILE *fp = fopen(current_dir, "w");
    fprintf( fp, "%s", "");
    fclose(fp);

  }else if(strncmp(args[0],"history",7) == 0 && strncmp(args[1],"!!",2) == 0 ){

    printf("DEBUGER:  -!! \n");

    FILE *ptr_file;
    char buf[1000];

    ptr_file =fopen(current_dir,"r");

    int historyCounter = 0;
    int historyLast10Counter = 0;

    while (fgets(buf,1000, ptr_file)!=NULL){

      historyLast10Counter++; // COUNT HOW MANY HISTORY LOGS EXIST
    }

    fclose(ptr_file);

    ptr_file =fopen(current_dir,"r");

    while (fgets(buf,1000, ptr_file)!=NULL){

      if( historyCounter  == historyLast10Counter - 1) {

        printf("..............%s",buf);
        executeOperation(buf, temp_cwd, temp_directory, cwd, directory);
      }

      historyCounter++;

    }

    fclose(ptr_file);

  }else if(strncmp(args[0],"history",7) == 0 && isOurValue(args[1]) != -1 ){

    FILE *ptr_file;
    char buf[1000];

    ptr_file =fopen(current_dir,"r");

    int historyCounter = 0;
    int historyCounter2 = 0;
    int historyLast10Counter = 0;

    while (fgets(buf,1000, ptr_file)!=NULL){

      historyLast10Counter++; // COUNT HOW MANY HISTORY LOGS EXIST
    }

    fclose(ptr_file);

    ptr_file =fopen(current_dir,"r");

    while (fgets(buf,1000, ptr_file)!=NULL){

      if(historyLast10Counter < 10){

        if( historyCounter  == isOurValue(args[1])) {

          printf("%d..............%s",historyCounter,buf);
          executeOperation(buf, temp_cwd, temp_directory, cwd, directory);
        }

      }else{

        if( historyCounter >= historyLast10Counter - 10) {



          if( historyCounter2  == isOurValue(args[1])) {


            printf("%d..............%s",historyCounter,buf);
            executeOperation(buf, temp_cwd, temp_directory, cwd, directory);

          }

          historyCounter2++;
        }
      }

      historyCounter++;

    }

    fclose(ptr_file);

  }
}
