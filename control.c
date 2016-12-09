#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <string.h>
#include <fcntl.h>
#include "control.h"

int main(int argc , char ** argv){
  int semid, shmid;
  int key = ftok("control.c", 512);
  int semC;
  int address;
  int size;
  int fd;
  
  if(argc == 0){
    printf("add one to commandline: -c, -r, -v\n");
    return -1;
  }
  
  if(strncmp(argv[1], "-c", strlen(argv[1])) == 0){

    //semaphore
    semid = semget(key, 1, IPC_CREAT | IPC_EXCL | 0644);
    union semun su;
    su.val = 1;
    semC = semctl(semid, 0, SETVAL, su);

    //shared memory
    shmid = shmget(key, 1024, IPC_CREAT | IPC_EXCL | 0644);
    address = shmat(shmid, 0, 0);

    printf("semaphore created: %d\n", semid);
    printf("shared memory created: %d\n", shmid);

    //file
    umask(0);
    fd = open("story", O_CREAT | O_TRUNC | O_EXCL, 0644);
    
  }else if (strncmp(argv[1], "-r", strlen(argv[1])) == 0){

    //semaphore
    semid = semget(key, 1, 0);
    semC = semctl(semid, 0, IPC_RMID);

    //shared memory
    shmid = shmget(key, 1024, 0);
    shmctl(shmid, IPC_RMID, 0);

    //output story
    printStory();
    
  }else if (strncmp(argv[1], "-v", strlen(argv[1])) == 0){

    //output story
    printStory();
    
  }
  
  return 0;
}

void printStory(){
  int fd = open("story", O_RDONLY);
  
  int fsize = lseek(fd, 0, SEEK_END);
  lseek(fd, 0, SEEK_SET);
  //printf("size of file: %d\n", fsize);


  char storyS[fsize];
  int rd = read(fd, storyS, fsize); 
  //printf("rd: %d\n", rd);
  
  printf("%s", storyS); //PRINTS OUT THE END OF FILE????

  close(fd);
}
