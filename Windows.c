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
bool IsCaptain=false;
key_t key=ftok("/home", 'c');
key_t key2=ftok("/home", '3');
int semid=semget(key,2,0);
if(semid== -1) {perror("semget\n"); }
P(semid, 2);
int shmid=shmget(key2, sizeof(sdata), 0);
if(shmid== -1){perror("shmget\n"); }
sdata*sd=NULL;
sd= shmat(shmid, sd, 0);
sd -> Windows =(sd->Windows)+1;
pid_t pid;
pid=fork();
if(pid==0){
if ((sd-> Windows)==4){
for(int i=0;i<3;i++) {V(semid,1);}
sd-> Windows =0;
IsCaptain=true;
printf("I am a Windows and captain of this boat. My ID is %d.\n", getpid());}
else if(((sd-> Windows) == 2) && ((sd-> Hackers) >=2))
{V(semid,1); V(semid, 0); V(semid, 0);
sd-> Hackers =(sd-> Hackers)-2;
sd-> Windows =0;
IsCaptain=true;
printf("I am a Windows and captain of this boat. My ID is %d.\n",getpid());}
else {
printf("I am Windows number %d from pid %d. I await the arrival of the others...\n", sd-> Windows, getpid());
V(semid, 2); Ptimed(semid,1); }
/* P(semid,0);}*/
/*2nd Solution (qst8)
void time_out()
{ printf(“the trip is cancelled!\n”);
sd->Windows=(sd-> Windows)-1 ;
exit(0) ;}
signal(SIGALRM,time_out);
alarm(60);
P(semid,1);}
*************************/
printf("I am a Windows with pid %d. I board the boat.\n",getpid());
/*Handler*/
void handler()
{if(IsCaptain==true)
{RowBoat();V(semid,2);IsCaptain=false;}
else{sd->cpt=(sd->cpt)+1;}}
signal(SIGINT,handler);
sleep(15); //qst5
Barriere(4,shmid, semid);
sleep(15); //qst4
if(IsCaptain==true)
{V(semid,2);
RowBoat();}
}}
