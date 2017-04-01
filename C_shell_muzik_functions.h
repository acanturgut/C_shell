#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/types.h>
#include <string.h>

#define MAX_LINE 80

void removeCrontab(char *file);

void addPlayList(char *task[],char muzikFile[],char crontabFile[]){

  char *temp[MAX_LINE];
  int counter=0;
  char is[1024];
  strcpy(is,task[1]);
  //printf("%s\n", is);
  while(task[counter]!=NULL){
    //printf("sasa %s\n", task[counter]);
    temp[counter]=task[counter];
    //printf("%s\n", temp[counter]);
    counter++;
  }
  addCrontab(temp);

  FILE *ptr_file;
  ptr_file =fopen(muzikFile,"a");
  fprintf(ptr_file,"%s\t%s\n",task[1],task[2]);
  fclose(ptr_file);
  //printf("DEBUGER ----- 1\n");

  FILE *ptr_file2;
  ptr_file2 =fopen(crontabFile,"a");

  //printf("DEBUGER ----- 2\n");
  char *array[10];
  int i=0;

  array[i] = strtok(is,".");

  while(array[i]!=NULL)
  {
    array[++i] = strtok(NULL,".");
  }

  //printf("ARRAY 1 --> %s\n",array[0]);
  //printf("ARRAY 1 --> %s\n",array[1]);
  char muzikCommand[MAX_LINE];
  char *ptr_time;
  char hour[1024];

//  printf("DEBUGER ----- 3\n");

  strcpy(hour,array[0]);

//  printf("%s\n",hour );
//  printf("DEBUGER ----- 4\n");

  char minute[1024];
  strcpy(minute,array[1]);

  //printf("DEBUGER ----- 5\n");

  printf("%s\n",minute );
  strcpy(muzikCommand,minute);
  strcat(muzikCommand," ");
  strcat(muzikCommand,hour);
  strcat(muzikCommand," * * * ");
  strcat(muzikCommand,"/usr/bin/mpg123 ");
  strcat(muzikCommand,task[2]);
  //printf("%s\n",muzikCommand );
  fprintf(ptr_file2,"%s\n",muzikCommand);
  fclose(ptr_file2);
}

void showPlayList(char muzikFile[]){
  FILE *ptr_file;
  char buf[1000];
  ptr_file =fopen(muzikFile,"r");
  while (fgets(buf,1000, ptr_file)!=NULL){
    printf("%s",buf);
  }
  fclose(ptr_file);
}
//removeda sıkıntı var!!!!
void removeSong(char time[], char muzikFile[], char crontabFile[]){

  char *timeArray[10];
  int i=0;
  timeArray[i] = strtok(time,".");
  while(timeArray[i]!=NULL)
  {
    timeArray[++i] = strtok(NULL,".");
  }
  //printf("TIME ARRAY 1 --> %s\n",timeArray[0]);
  //printf("TIME ARRAY 1 --> %s\n",timeArray[1]);

  FILE *ptr_file;
  FILE *temp_file;
  char buf[1000];
  ptr_file =fopen(muzikFile,"r");
  temp_file=fopen("tempMuzikfile.txt","w");
  char tempBuf[1000];
  char *timex;
  while(fgets(buf,1000,ptr_file)!=NULL){
    strcpy(tempBuf,buf);
    timex=strtok(tempBuf,"\t");
    if(strcmp(timex,time)!=0){
      fprintf(temp_file, "%s", buf);
    }
  }
  fclose(ptr_file);
  fclose(temp_file);
  temp_file=fopen("tempMuzikfile.txt","r");
  ptr_file=fopen(muzikFile,"w");
  while(fgets(buf,1000,temp_file)!=NULL){
    fprintf(ptr_file, "%s", buf);
  }
  fclose(temp_file);
  fclose(ptr_file);
  remove("tempMuzikfile.txt");

  //remove from crontab file
  ptr_file =fopen(crontabFile,"r");
  temp_file=fopen("tempCrontabfile.txt","w");
  while(fgets(buf,1000,ptr_file)!=NULL){
    strcpy(tempBuf,buf);
    char *array[10];
    int i=0;
    array[i] = strtok(tempBuf," ");
    while(array[i]!=NULL)
    {
      array[++i] = strtok(NULL," ");
    }
    printf("ARRAY 1 --> %s\n",array[0]);
    printf("ARRAY 1 --> %s\n",array[1]);
    if(strcmp(array[1],timeArray[0])!=0 && strcmp(array[0],timeArray[1])!=0){
      fprintf(temp_file, "%s", buf);
    }
  }
  fclose(ptr_file);
  fclose(temp_file);
  temp_file=fopen("tempCrontabfile.txt","r");
  ptr_file=fopen(crontabFile,"w");
  while(fgets(buf,1000,temp_file)!=NULL){
    fprintf(ptr_file, "%s", buf);
  }
  fclose(temp_file);
  fclose(ptr_file);
  remove("tempCrontabfile.txt");
  removeCrontab(crontabFile);
}

void addCrontab(char *task[]){
  char muzikCommand[MAX_LINE];
  char *ptr_time;
  char hour[1024];
  ptr_time=strtok(task[1],".");
  strcpy(hour,ptr_time);
  char minute[1024];
  ptr_time=strtok(NULL,".");
  strcpy(minute,ptr_time);
  strcpy(muzikCommand,"(crontab -l &&  echo \"");
  strcat(muzikCommand,strdup(minute));
  strcat(muzikCommand," ");
  strcat(muzikCommand,strdup(hour));
  strcat(muzikCommand," * * * ");
  strcat(muzikCommand,"/usr/bin/mpg123 ");
  strcat(muzikCommand,task[2]);
  strcat(muzikCommand,"\" )  |  crontab -");
  printf("MUZIK COMMAND: %s\n",muzikCommand);
  system(muzikCommand);
  memset(hour,0,sizeof(hour));
  memset(minute,0,sizeof(minute));
  memset(muzikCommand,0,sizeof(muzikCommand));
}

void removeCrontab(char file[]){
  system("crontab -r");
  char crntb[1024];
  strcpy(crntb,"cat ");
  strcat(crntb,file);
  strcat(crntb," | crontab -");
  system(crntb);

}
