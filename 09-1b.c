#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

int main()
{
  int     *array;
  int     shmid;
  int     new = 1;
  int     semid;        
  struct  sembuf mybuf; 
  char    pathname[] = "09-1a.c";
  key_t   key;
  long    i;

  if ((key = ftok(pathname,0)) < 0) {
    printf("Can\'t generate key\n");
    exit(-1);
  }

  if ((shmid = shmget(key, 3*sizeof(int), 0666|IPC_CREAT|IPC_EXCL)) < 0) {
    if (errno != EEXIST) {
      printf("Can\'t create shared memory\n");
      exit(-2);
    } else {
      if ((shmid = shmget(key, 3*sizeof(int), 0)) < 0) {
        printf("Can\'t find shared memory\n");
        exit(-3);
      }
      new = 0;
    }
  }

  if ((semid = semget(key, 1, 0666 | IPC_CREAT | IPC_EXCL)) < 0) {
      if (errno != EEXIST) {
          printf("An unexpected error occured. The semaphore does not exist.\n");
          exit(-4);
      }
      else {
          if ((semid = semget(key, 1, 0)) < 0) {
              printf("Unable to get semaphore by key.\n");
              exit(-5);
          }
      }
  }
  else {
      mybuf.sem_num = 0;
      mybuf.sem_op = 1;
      mybuf.sem_flg = 0;

      if (semop(semid, &mybuf, 1) < 0) {
          printf("Can\'t set original value of this semaphore to 1.\n");
          exit(-6);
      }
  }

  if ((array = (int *)shmat(shmid, NULL, 0)) == (int *)(-1)) {
    printf("Can't attach shared memory in program B.\n");
    exit(-7);
  }

  mybuf.sem_num = 0;
  mybuf.sem_op = -1;
  mybuf.sem_flg = 0;

  if (semop(semid, &mybuf, 1) < 0) {
      printf("Can\'t enter the critical section properly in program B.\n");
      exit(-8);
  }

  if (new) {
    array[0] =  0;
    array[1] =  1;
    array[2] =  1;
  } else {
    array[1] += 1;
    for(i=0; i<2000000000L; i++);
    array[2] += 1;
  }

  printf
    ("Program A was spawned %d times, program B - %d times, total - %d times\n",
    array[0], array[1], array[2]);

  mybuf.sem_num = 0;
  mybuf.sem_op = 1;
  mybuf.sem_flg = 0;

  if (semop(semid, &mybuf, 1) < 0) {
      printf("Can\'t exit the critical section properly in program B.\n");
      exit(-8);
  }

  if (shmdt(array) < 0) {
    printf("Can't detach shared memory in program B.\n");
    exit(-9);
  }

  return 0;
}
