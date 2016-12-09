void printStory();

union semun{
  int val; //val for set val
  struct semid_ds *buf; //Buffer for IPC_STAT IPC_SET
  unsigned short *array; //Array for GETALL , SETALL
  struct seminfo *__buf; //Buffer for IPC_INFO
};
