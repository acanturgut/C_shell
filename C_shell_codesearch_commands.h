// Code Search Commands
// Ahmet Can Turgut - Damla Ovek

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>

#include "C_shell_codesearch_functions.h"

#define MAX_LINE 80

void codesearch_comments(char *args[], char cwd[]){

  printf("C_SHELL --> SAYS -->  codesearch Starts... \n");

  if(strncmp(args[0],"codesearch",10) == 0 && args[1]==NULL && args[2]==NULL){

    printf("C_SHELL Warning ----> Try --> codesearch help <-- command\n");

  }else if(strncmp(args[0],"codesearch",10) == 0 && strncmp(args[1],"help",4) == 0 && args[2]==NULL){

    printf("codesearch \"word do you want to search\"     <-- List all files which contains searched word in current dir\n");
    printf("codesearch -r \"word do you want to search\"  <-- List all files in sub-dirs which contains searched word in current dir\n");

  }else if(strncmp(args[0],"codesearch",10) == 0 && strncmp(args[1],"-r",2) == 0 && args[2] != NULL){


    int recursiveAvailbe;

    recursiveAvailbe = code_search_valid_rec(args);

    if(recursiveAvailbe == 1){

      //printf("DEBUGER: Recureive OK. \n");

      char tempData[MAX_LINE] = "";
      int countW = 2;

      if(args[countW] != NULL)

      while(args[countW] != NULL){

        strcat(tempData, args[countW]);
        strcat(tempData, " ");

        countW++;
      }

      //printf("DEBUGER 3 : TEMP DATA --> %s\n", tempData);

      char str2[sizeof(tempData)-1];
      if(strlen(tempData) > 0){

        strcpy(str2, &(tempData[1]));

      }else{

        strcpy(str2, tempData);

      }

      //printf("DEBUGER 4 : STR 2 --> %s\n", str2);

      int charIndex = 0;

      for(charIndex = 0; str2[charIndex] != '\0'; ++charIndex);

      //printf("DEBUGER CHAR INDEX --> %d\n", charIndex);

      str2[charIndex-2] = '\0';

      printf("C_SHELL --> SAYS --> Recursion Search Starts\n");

      char codesearch_save_dir[1024];
      char currentDir[1024];

      getcwd(currentDir, sizeof(currentDir));
      getcwd(codesearch_save_dir, sizeof(codesearch_save_dir));
      strcat(codesearch_save_dir, "/");


      listdir(codesearch_save_dir, 0, str2);

      printf("C_SHELL --> SAYS -->  codesearch done \n");

    }

  }else{

    if(strncmp(args[0],"codesearch",10) == 0 && args[1] != NULL ){

      //printf("DEBUGER:  args OK. \n");

      int isAvaible;

      isAvaible = code_search_valid(args);

      if(isAvaible == 1){

        //  printf("DEBUG: -- > %d\n", k);

        char tempData[MAX_LINE] = "";
        int countW = 1;

        if(args[countW] != NULL)

        while(args[countW] != NULL){

          strcat(tempData, args[countW]);
          strcat(tempData, " ");

          countW++;
        }

        //printf("DEBUGER 3 : TEMP DATA --> %s\n", tempData);

        char str2[sizeof(tempData)-1];
        if(strlen(tempData) > 0){

          strcpy(str2, &(tempData[1]));

        }else{

          strcpy(str2, tempData);

        }

        //printf("DEBUGER 4 : STR 2 --> %s\n", str2);

        int charIndex = 0;

        for(charIndex = 0; str2[charIndex] != '\0'; ++charIndex);

        //printf("DEBUGER CHAR INDEX --> %d\n", charIndex);

        str2[charIndex-2] = '\0';

        //printf("DEBUGER 5 : STR 3 --> %s\n", str2);

        DIR *d;
        struct dirent *dir;
        d = opendir(".");
        if (d){

          while ((dir = readdir(d)) != NULL){

            char temp[MAX_LINE];
            strcpy(temp, dir->d_name);
            if(strstr(temp, ".") != NULL){

              //printf("%s\n", temp);

              char codesearch_save_dir[1024];
              char currentDir[1024];

              getcwd(currentDir, sizeof(currentDir));
              getcwd(codesearch_save_dir, sizeof(codesearch_save_dir));
              strcat(codesearch_save_dir, "/");
              strcat(codesearch_save_dir, temp);

              int display_counter = 1;

              char buf[10000];

              FILE *ptr_file;
              ptr_file =fopen(codesearch_save_dir,"r");

              while (fgets(buf,10000, ptr_file)!=NULL){

                if(strstr(buf,str2) != NULL){

                  printf("%d: %s -->  %s",display_counter, temp ,buf);

                }

                display_counter++;
              }

              fclose(ptr_file);
            }
          }
          closedir(d);
        }

        printf("C_SHELL --> SAYS -->  codesearch done \n");

      }else{

        //  printf("DEBUG: -- > %d\n", k);

      }
    }
  }
}
