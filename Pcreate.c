#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/ipc.h>
#include<sys/sem.h>
#include<sys/shm.h>
#include<time.h>
#include<signal.h>
#include<string.h>
#include "semaphores20.h"

int main(void){

//CREATION OF A GROUP OF 5 SEMAPHORES
key_t key=ftok("/home/TP1",'c');
int sem=semcreate(key, 5);

//INITIALIZATION
seminit(sem, "HackersQueue",0,0);
seminit(sem, "WindowsQueue",1,0);
seminit(sem, "Mutex1",2,1);
seminit(sem, "SemBarriere",3,0);
seminit(sem, "Mutex2",4,1);
printf("The semaphore group ID value is %d\n\n ", sem);
fflush(stdout);

//CREATION OF THE SHARED MEMORY (WE HAVE 3 SHARED VARIABLES)
key_t key2=ftok("/home", '3');
int shmid=shmget(key2,sizeof(sdata), IPC_CREAT | IPC_EXCL|0666);
printf("Memory segment ID is %d \n", shmid);
if(shmid== -1) {perror("shemget");
shmid=shmget(key2, sizeof(sdata), 0);
printf("shmid=%d\n", shmid);}
sdata* sd=NULL;
sd = shmat (shmid, sd, 0);
sd -> Hackers=0;
sd -> Windows=0;
sd -> cpt=0;
printf("Shared variables have been initialized\n Hackers=%d, Windows=%d, cpt=%d ", sd->Hackers, sd->Windows, sd->cpt);}


