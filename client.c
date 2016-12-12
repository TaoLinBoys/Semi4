#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include "control.h"

int main(){
  int semid, shmid, fd;
  int key = ftok("control.c", 512);
  
  semid = semget(key, 1, 0644);
  shmid = shmget(key, 1024, 0644);
  fd = open("story", O_APPEND | O_RDWR);

  //downing
  struct sembuf semB;
  semB.sem_num = 0;
  semB.sem_flg = SEM_UNDO;
  semB.sem_op = -1;
  semop(semid, &semB, 1);

  
  //printing last entry
  printf("previous entry:");
  
  int * size;
  size = (int *)shmat(shmid, 0, 0);
  char prev[*size +1];
  lseek(fd, -(*size), SEEK_END);
  read(fd, prev, *size);
  prev[*size] = 0;
  
  printf(" %s\n", prev);

  
  //enter next entry
  char new[256];
  printf("whaddya want: ");
  
  fgets(new, sizeof(new), stdin);
  *size = strlen(new);
  write(fd, new, *size);


  //upping
  semB.sem_op = 1;
  semop(semid, &semB, 1);
  

  close(fd);
  return 0;
}
