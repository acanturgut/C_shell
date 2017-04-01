#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>

int PROCESS_PID =-1;

void c_shell_prcessInfoFunc(char *args[]){

  printf("C_SHELL --> SAYS --> ProcessInfo Starts...\n");
  if(args[1]==NULL){
    printf("C_Shell Error ----> Invalid PID\n");
  }else{

    int k = atoi(args[1]);
    printf("DEBUG K == >%d\n",k);

    if(PROCESS_PID==k){
      printf("C_SHELL Warning ---> This module is already exist\n");
    }else{

      if(PROCESS_PID != -1){
        char runModule[1024];
        strcpy(runModule,"sudo insmod processInfo.ko processPID=");
        strcat(runModule,args[1]);
        strcat(runModule," processPrio=");
        strcat(runModule,args[2]);

        printf("%s",runModule);

        system("sudo rmmod processInfo.ko");
        system(runModule);
        system("sudo dmesg -c");

      }else{

        PROCESS_PID = k;
        char runModule[1024];
        strcpy(runModule,"sudo insmod processInfo.ko processPID=");
        strcat(runModule,args[1]);
        strcat(runModule," processPrio=");
        strcat(runModule,args[2]);
        system("make");
        system(runModule);
        system("sudo dmesg -c");
      }
    }
  }
}
