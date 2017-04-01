#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>
#include "C_shell_muzik_functions.h"

void muzikCommand(char *args[]){
  if(strncmp(args[1],"-l",2)==0){
    showPlayList("C_shell_play_list.txt");
  }else if(strncmp(args[1],"-r",2)==0){
    removeSong(args[2],"C_shell_play_list.txt","C_shell_crontab.txt");
  }else{
    addPlayList(args,"C_shell_play_list.txt","C_shell_crontab.txt");
  }
}
