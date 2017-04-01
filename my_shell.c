/**
* myshell interface program Ahmet Can Turgut - Damla Övek
* Comp 304 - Operating Systems
*/

#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

#include <readline/readline.h>
#include <readline/history.h>

#include "C_shell_cd.h"
#include "C_shell_linux_commands.h"
#include "C_shell_muzik_commands.h"
#include "C_shell_codesearch_commands.h"
#include "C_shell_history_comments.h"
#include "C_shell_bookmark_commands.h"
#include "C_shell_processInfo.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#define MAX_LINE 80

int parseCommand(char inputBuffer[], char *args[],int *background);
char fullpath[MAX_LINE];
char directory[MAX_LINE]="C_Shell >> ";
char history_save_dir[1024];
char fp[MAX_LINE];
char cwd[1024];

int disko_temp;

void disko(char diskoTime[]){

  printf("Dis-ko Starts... Check Your Desktop \n DIS-KO BEGINS WHOOOW...\n");

  int diskoInt = atoi(diskoTime);
  int counter_disko = 0;
  printf("CWD %s\n",cwd);

  char commandGR[1024] = "gsettings set org.gnome.desktop.background picture-uri file:///";
  char commandRD[1024] = "gsettings set org.gnome.desktop.background picture-uri file:///";
  char commandBL[1024] = "gsettings set org.gnome.desktop.background picture-uri file:///";

  strcat(commandGR,cwd);
  strcat(commandRD,cwd);
  strcat(commandBL,cwd);

  char blue[1024] = "/disko_images/blue.png";
  char red[1024] = "/disko_images/red.png";
  char green[1024] = "/disko_images/green.png";

  strcat(commandBL,blue);
  strcat(commandRD,red);
  strcat(commandGR,green);

  //printf("%s\n", commandBL);
  //printf("%s\n", commandRD);
  //printf("%s\n", commandGR);

  for (;;) {
    double interval = 0.01;
    time_t start = time(NULL);
    int duration = 1;

    printf("GO GO GO - GO GO GO %s", ctime(&start));

    if(disko_temp == 0){

      system(commandBL);
      disko_temp++;

    }else if(disko_temp == 1){

      system(commandRD);
      disko_temp++;

    }else{

      system(commandGR);
      disko_temp = 0;
    }

    sleep(duration);
    counter_disko ++;

    time_t end = time(NULL);

    double elapsed = difftime(end, start);
    int seconds_to_sleep = (int)(interval - elapsed);
    if (seconds_to_sleep > 0) {
      sleep(seconds_to_sleep);
    }

    if(counter_disko == diskoInt){
      return;
    }
  }
}

void help(){

  printf("*****************************\n");
  printf("This is help command...\n");
  printf("You can execute linux commands such as ls, top, cd\n");
  printf("-keyboard allows to keyboard navigation\n");
  printf("*****************************\n");
  printf("history     <-- display last 10 entry \n");
  printf("history -c  <-- clear history \n");
  printf("history -!! <-- execute last entry \n");
  printf("history -!x <-- execute x'th entry \n");
  printf("*****************************\n");
  printf("bookmark \"xxxx\" <-- add bookmarks\n");
  printf("bookmark -l       <-- list bookmarks\n");
  printf("bookmark -i x     <-- execute x'th bookmark\n");
  printf("bookmark -d x     <-- remove x'th bookmark\n");
  printf("*****************************\n");
  printf("muzik minute hour * * path/path/selectedmuzik.mp3  <-- add to play music given time\n");
  printf("muizk xxx -r <-- xxx remove music\n");
  printf("muizk  -l    <-- show music list\n");
  printf("*****************************\n");
  printf("codesearch \"xxx\"    <-- search desired code (Warning code should not include any \" ) \n");
  printf("codesearch -r \"xxx\" <-- search in sub directoris \n");
  printf("*****************************\n");
  printf("disco x <-- Starts disco on desktop with x second\n");
  printf("*****************************\n");

}

int main(void){

  int disko_temp = 0;

  printf(ANSI_COLOR_GREEN "*********************************************************\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "*********************************************************\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   This is C_SHELL                                     *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   Type help to see capabilities                       *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   Created by Ahmet Can Turgut & Damla Övek            *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   COMP 304 - OS project 1 - MY_SHELL                  *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   Koc University - 2017 Spring                        *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "*   CopyRight.. University Code of Honesty              *\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "*********************************************************\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "*********************************************************\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "C_SHELL --> HELP ---->  HELP -help for     ==>> help     \n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "C_SHELL --> INFO ----> Keyboard Activation ==>> -keyboard\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "C_SHELL --> DISKO ---> FOR DESKTOP DISKO  ==>> disko x(s)\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_BLUE "C_SHELL --> SAYS ----> You can start typing NOW..........\n" ANSI_COLOR_RESET);
  printf(ANSI_COLOR_GREEN "*********************************************************\n\n" ANSI_COLOR_RESET);

  getcwd(cwd, sizeof(cwd));
  getcwd(history_save_dir, sizeof(history_save_dir));
  strcat(history_save_dir, "/my_shell_data.txt");
  strcpy(fp,cwd);
  strcat(fp,"/C_shell_bookmark_data.txt");

  char temp_cwd[1024];
  strcpy(temp_cwd, cwd);

  char temp_directory[MAX_LINE] = "C_Shell >> ";

  char inputBuffer[MAX_LINE]; 	      /* buffer to hold the command entered */
  int background;             	      /* equals 1 if a command is followed by '&' */
  char *args[MAX_LINE/2 + 1];	        /* command line (of 80) has max of 40 arguments */
  pid_t child;            		        /* process id of the child process */
  int status;           		          /* result from execv system call*/
  int shouldrun = 1;

  while (shouldrun){            		/* Program terminates normally inside setup */

    background = 0;
    shouldrun = parseCommand(inputBuffer,args,&background);       /* get next command */

    if (strncmp(inputBuffer, "exit", 4) == 0)
    shouldrun = 0;     /* Exiting from myshell*/

    if (shouldrun) {

      /*
      After reading user input, the steps are
      (1) Fork a child process using fork()
      (2) the child process will invoke execv()
      (3) if command included &, parent will invoke wait()
      */

      child=fork();
      if(child==0){

        store_history(history_save_dir,args);

        if(strncmp(args[0],"cd",2) == 0 ){

          execv_cd(args, temp_cwd, temp_directory, cwd, directory);

        }else if(strncmp(args[0],"history",7) == 0){

          history_Comments(args, history_save_dir, temp_cwd, temp_directory, cwd, directory);

        }else if(strncmp(args[0],"bookmark",7) == 0){

          bookmark_comments(args,history_save_dir,temp_directory,temp_cwd,cwd,directory,fp);

        }else if(strncmp(args[0],"processInfo",11) == 0){
	        //printf("DEBUGER: ENTER <-- PID");
          c_shell_prcessInfoFunc(args);

        }else if(strncmp(args[0],"muzik",5) == 0){

          muzikCommand(args);

        }else if(strncmp(args[0],"help",4) == 0){

          help();

        }else if(strncmp(args[0],"codesearch",10) == 0){

          codesearch_comments(args,cwd);

        }else if(strncmp(args[0],"disko",5) == 0){

          disko(args[1]);

        }else if(strncmp(args[0],"-keyboard",13) == 0){
          printf(ANSI_COLOR_GREEN "-------------------------------------------------------\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-------------------------------------------------------\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-C_SHELL --> SAYS---> WARNING <------------------------\n" ANSI_COLOR_RESET);
          printf("\n");
          printf(ANSI_COLOR_GREEN "-YOU ARE IN GNU readLINE\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-Type 'ext' for return PURE C_SHELL\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-KEYBOARD ARROW KEYS ALLOWS TO YOU NAVIGATE HISTORY\n\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-------------------------------------------------------\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-------------------------------------------------------\n\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_RED "-SOME FETURES MAY NOT WORK ! --------------------------\n" ANSI_COLOR_RESET);
          printf(ANSI_COLOR_GREEN "-START TYPING...\n\n" ANSI_COLOR_RESET);
          char *inpt;

          inpt = readline("C_SHELL_keyboard >> ");

          if(inpt != NULL){
            add_history(inpt);
          }

          int argc = 0;
          char *argk[MAX_LINE];
          char *pointer;

          pointer = strtok(inpt, " ");

          while (pointer && argc < MAX_LINE-1){

            argk[argc++] = pointer;
            pointer = strtok(NULL, " ");

          }

          argk[argc] = NULL;

          //printf("DEBUGER args0 --> %s\n", argk[0]);
          //printf("DEBUGER args1 --> %s\n", argk[1]);
          //printf("DEBUGER args2 --> %s\n", args[2]);

          if(strncmp(argk[0],"cd",2) == 0 ){

            execv_cd(argk, temp_cwd, temp_directory, cwd, directory);

          }else if(strncmp(argk[0],"history",7) == 0){

            history_Comments(argk, history_save_dir, temp_cwd, temp_directory, cwd, directory);

          }else if(strncmp(argk[0],"bookmark",7) == 0){

            bookmark_comments(argk,history_save_dir,temp_directory,temp_cwd,cwd,directory,fp);

          }else if(strncmp(argk[0],"processInfo",11) == 0){

            c_shell_prcessInfoFunc(args);

          }else if(strncmp(argk[0],"muzik",5) == 0){

            muzikCommand(argk);

          }else if(strncmp(argk[0],"help",4) == 0){

            help();

          }else if(strncmp(argk[0],"codesearch",10) == 0){

            codesearch_comments(argk,cwd);

          }else if(strncmp(argk[0],"disko",5) == 0){

            disko(argk[1]);

          }else{

            linux_Comments(argk);

          }

          while(strcmp(inpt,"ext") !=0){

              inpt = readline("C_SHELL_keyboard >> ");

              if(inpt != NULL){
                add_history(inpt);
              }

              int argc = 0;
              char *argk[MAX_LINE];
              char *pointer;

              pointer = strtok(inpt, " ");

              while (pointer && argc < MAX_LINE-1){

                //printf("DEBUGER -executeOP \n");
                argk[argc++] = pointer;
                pointer = strtok(NULL, " ");

              }

              argk[argc] = NULL;

              //printf("DEBUGER args0 --> %s\n", argk[0]);
              //printf("DEBUGER args1 --> %s\n", argk[1]);
              //printf("DEBUGER args2 --> %s\n", args[2]);

              if(strncmp(argk[0],"cd",2) == 0 ){

                execv_cd(argk, temp_cwd, temp_directory, cwd, directory);

              }else if(strncmp(argk[0],"history",7) == 0){

                history_Comments(argk, history_save_dir, temp_cwd, temp_directory, cwd, directory);

              }else if(strncmp(argk[0],"bookmark",7) == 0){

                bookmark_comments(argk,history_save_dir,temp_directory,temp_cwd,cwd,directory,fp);

              }else if(strncmp(argk[0],"processInfo",11) == 0){

                c_shell_prcessInfoFunc(args);

              }else if(strncmp(argk[0],"muzik",5) == 0){

                muzikCommand(argk);

              }else if(strncmp(argk[0],"help",4) == 0){

                help();

              }else if(strncmp(argk[0],"codesearch",10) == 0){

                codesearch_comments(argk,cwd);

              }else if(strncmp(argk[0],"disko",5) == 0){

                disko(argk[1]);

              }else{

                linux_Comments(argk);

              }
          }

        }else{

          linux_Comments(args);
        }

      }if(child>0){

        if(background==1){
          wait(NULL);
        }
        else{
          waitpid(child, &status, 0);
        }
      }
      if(child<0){
        fprintf(stderr, "Fork failed.\n");
        exit(1);
      }
    }
  }
  return 0;
}

/**
* The parseCommand function below will not return any value, but it will just: read
* in the next command line; separate it into distinct arguments (using blanks as
* delimiters), and set the args array entries to point to the beginning of what
* will become null-terminated, C-style strings.
*/

int parseCommand(char inputBuffer[], char *args[],int *background){

  int length,		/* # of characters in the command line */
  i,		/* loop index for accessing inputBuffer array */
  start,		/* index where beginning of next command parameter is */
  ct,	        /* index of where to place the next parameter into args[] */
  command_number;	/* index of requested command number */

  ct = 0;

  /* read what the user enters on the command line */
  do {
    printf(ANSI_COLOR_CYAN "%s" ANSI_COLOR_RESET,directory);
    fflush(stdout);
    length = read(STDIN_FILENO,inputBuffer,MAX_LINE); // READ LINE GELICEK...
  }
  while (inputBuffer[0] == '\n'); /* swallow newline characters */

  /**
  *  0 is the system predefined file descriptor for stdin (standard input),
  *  which is the user's screen in this case. inputBuffer by itself is the
  *  same as &inputBuffer[0], i.e. the starting address of where to store
  *  the command that is read, and length holds the number of characters
  *  read in. inputBuffer is not a null terminated C-string.
  */
  start = -1;
  if (length == 0)
  exit(0);            /* ^d was entered, end of user command stream */

  /**
  * the <control><d> signal interrupted the read system call
  * if the process is in the read() system call, read returns -1
  * However, if this occurs, errno is set to EINTR. We can check this  value
  * and disregard the -1 value
  */

  if ( (length < 0) && (errno != EINTR) ) {
    perror("error reading the command");
    exit(-1);           /* terminate with error code of -1 */
  }

  /**
  * Parse the contents of inputBuffer
  */

  for (i=0;i<length;i++) {
    /* examine every character in the inputBuffer */

    switch (inputBuffer[i]){
      case ' ':
      case '\t' :                          /* argument separators */
      if(start != -1){
        args[ct] = &inputBuffer[start];    /* set up pointer */
        ct++;
      }
      inputBuffer[i] = '\0';              /* add a null char; make a C string */
      start = -1;
      break;

      case '\n':                         /* should be the final char examined */
      if (start != -1){
        args[ct] = &inputBuffer[start];
        ct++;
      }
      inputBuffer[i] = '\0';
      args[ct] = NULL;                   /* no more arguments to this command */
      break;

      default :             /* some other character */
      if (start == -1)
      start = i;
      if (inputBuffer[i] == '&') {
        *background  = 1;
        inputBuffer[i-1] = '\0';
      }
    } /* end of switch */
  }    /* end of for */

  /**
  * If we get &, don't enter it in the args array
  */

  if (*background)
  args[--ct] = NULL;

  args[ct] = NULL; /* just in case the input line was > 80 */

  return 1;

} /* end of parseCommand routine */
