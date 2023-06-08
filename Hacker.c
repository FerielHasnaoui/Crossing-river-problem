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
key_t key=ftok("/home/TP1", 'c');
key_t key2=ftok("/home/TP1", '3');
int semid=semget(key,2,0);
if(semid== -1) {perror("semget\n"); }
P(semid, 2);
int shmid=shmget(key2, sizeof(sdata), 0);
if(shmid== -1){perror("shmget\n"); }
sdata*sd=NULL;
sd= shmat(shmid, sd, 0);
sd -> Hackers =(sd->Hackers)+1;
pid_t pid;
pid=fork();
if(pid==0){
if ((sd->Hackers)==4){
for(int i=0;i<3;i++) {V(semid,0); }
sd->Hackers=0;
IsCaptain=true;
printf("Je suis un Hacker et capitaine de ce bateau. Mon ID est %d.\n", getpid());}
else if(((sd->Hackers) == 2) && ((sd->Windows) >=2))
{V(semid,0); V(semid, 1); V(semid, 1);
sd->Windows=(sd->Windows)-2;
sd->Hackers=0;
IsCaptain=true;
printf("Je suis un Hacker et capitaine de ce bateau. Mon ID est %d.\n",getpid());}
else {
printf("je suis le Hacker numero %d de pid %d. J'attend l'arrivé des autres…\n",sd->Hackers, getpid());
V(semid,2); Ptimed(semid,0);}
/* P(semid,0);}*/
/*Solution2 qst8
void time_out()
{ printf(“le voyage est annulé!\n”);
sd->Hackers=(sd->Hackers)-1 ;
exit(0) ;}
signal(SIGALRM,time_out);
alarm(60);
P(semid,0);}
*************************/
printf("je suis un Hacker de pid %d. J'embarque sur le bateau.\n",getpid());
/*Handler*/
void handler()
{if(IsCaptain==true)
{RowBoat();V(semid,2);IsCaptain=false;}
else{sd->cpt=(sd->cpt)+1;}}
signal(SIGINT,handler);
sleep(15); //qst5
Barriere(4,shmid, semid);
sleep(15); //qst4
if (IsCaptain==true)
{V(semid, 2);
RowBoat();}
}}
