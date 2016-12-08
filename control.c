#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

union semun{
  int val; //val for set val
  struct semid_ds; //Buffer for IPC_STAT IPC_SET
  unsigned short *array; //Array for GETALL , SETALL
  struct seminfo *__buf; //Buffer for IPC_INFO
};

int main(int argc , char ** argv){
  
  int size;
  
  if(argc == 0){
    printf("add one to commandline: -c, -r, -v\n");
    return -1;
  }
  if(strcmp(argv[1], "-c") == 0){
    int key = ftok("control.c" , 512);
    int semid = semget(key, 1 , IPC_EXCL | IPC_CREAT | 0644);
    int sm = shmget(key, 1024 , IPC_CREAT | IPC_EXCL | 0644);
    
    open("writefile" O_TRUNC | O_CREAT | 0644);
    return 0;
  }
  

}
