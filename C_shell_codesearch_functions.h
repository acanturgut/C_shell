#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <dirent.h>

#define MAX_LINE 80


int code_search_valid_rec(char *args2[]){

  printf("ANAN2\n");

  int counter2 = 0;

  while(args2[counter2] != NULL){

    counter2++;

  }

  int lastIndex2 = counter2-1;
  int firstIndex2 = 2;

  printf("DEBUGER: -r CS-> COUNTER:  %d\n", counter2  );
  printf("DEBUGER: -r CS-> LASTARGS: %s\n", args2[firstIndex2]);
  printf("DEBUGER: -r CS-> LASTARGS: %s\n", args2[lastIndex2]);

  char firstString2[MAX_LINE] = "-";
  char secondString2[MAX_LINE] = "-";

  strcpy(firstString2, args2[firstIndex2]);
  strcpy(secondString2, args2[lastIndex2]);


  if(lastIndex2 == 1){

    //printf("DEBUGER: CS-> DONE OK. LASTINDEX: %d\n", lastIndex);

    char firstchar;

    firstchar = firstString2[0];

    if(firstchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> First \" Missing ! <-- command\n");
      return -1;

    }

    int charIndex = 0;

    for(charIndex = 0; firstString2[charIndex] != '\0'; ++charIndex);

    char endchar;

    endchar = firstString2[charIndex-1];

    if(endchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> Last \" Missing ! <-- command\n");
      return -1;

    }

    //  printf("DEBUGER OK. \n");
    //  printf("DEBUGER: --> CHAR INDEX %d\n", charIndex-1 );

  }else{

    char firstchar;

    firstchar = firstString2[0];

    if(firstchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> First \" Missing ! <-- command\n");
      return -1;

    }

    int charIndex = 0;

    for(charIndex = 0; secondString2[charIndex] != '\0'; ++charIndex);

    char endchar;

    endchar = secondString2[charIndex-1];

    if(endchar != '\"'){

      printf("C_SHELL Warning ----> SYNTAX ERROR --> Last \" Missing ! <-- command\n");
      return -1;

    }

    //  printf("DEBUGER OK. \n");
    //  printf("DEBUGER: --> CHAR INDEX %d\n", charIndex-1 );

  }

  return 1;

}

int code_search_valid(char *args[]){

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


void listdir(const char *name, int level, const char strr[]){

  //printf("DIRECTORY: %s\n", name);

  DIR *dir;
  struct dirent *entry;

  if (!(dir = opendir(name)))
  return;
  if (!(entry = readdir(dir)))
  return;

  while ((entry = readdir(dir))){

    if (entry->d_type == DT_DIR) {

      char path[1024];
      int len = snprintf(path, sizeof(path)-1, "%s/%s", name, entry->d_name);
      path[len] = 0;

      if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
        continue;
      }

      //printf("%*s[%s]\n", level*2, "", entry->d_name);
      listdir(path, level + 1, strr);


    }else{

      char dir[1024];

      strcpy(dir, name);
      strcat(dir, "/");
      strcat(dir, entry->d_name);

      //printf("DIR NAME--> TARGER:::: DONE %s\n",dir);
      //printf("%*s - %s\n", level*2, "", entry->d_name);

      int display_counter = 1;

      char buf[10000];

      FILE *ptr_file;
      ptr_file =fopen(dir,"r");

      while (fgets(buf,10000, ptr_file)!=NULL){

        if(strstr(buf,strr) != NULL){

          printf("%d: %s -->  %s",display_counter, dir ,buf);

        }

        display_counter++;
      }

      fclose(ptr_file);

    }
  }

  closedir(dir);
}
