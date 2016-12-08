#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>

union semun{
  int val; //val for set val
  struct semid_ds *buf; //Buffer for IPC_STAT IPC_SET
  unsigned short *array; //Array for GETALL , SETALL
  struct seminfo *__buf; //Buffer for IPC_INFO
};

int main(int argc , char ** argv){
  int semid;
  int key = ftok("control.c", 512);
  int semC;
  int size;
  
  if(argc == 0){
    printf("add one to commandline: -c, -r, -v\n");
    return -1;
  }
  
  if(strncmp(argv[1], "-c", strlen(argv[1])) == 0){
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
    printf("semaphore created: %d\n", semid);
    union semun su;
    su.val = 1;
    semC = semctl(semid, 0, SETVAL, su);
    return 0;
  }
  

}
