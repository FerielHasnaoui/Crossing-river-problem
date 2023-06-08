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
//structure de données partagées 
typedef struct data{int cpt, Hackers, Windows;}sdata;

//creation des sémaphores 
int semcreate(key_t key, int N){
int semid= semget(key, N, IPC_CREAT | IPC_EXCL|0666);
printf("semid= %d\n", semid);
if (semid == -1){ perror("semget :");
semid= semget(key, N, 0);
printf("un group de sémaphores existe déja pour cette clé et son id est %d\n", semid); }
else {printf("Un nouveau group de semaphores à été créee et son id est %d\n", semid); }
return semid;
}

//suppression des sémaphores 
int semdestroy(int semid){
int d=semctl(semid,0, IPC_RMID);
printf("le sémaphore a ete détruit");
return d;}

//Initialisation des sémaphores
int seminit(int idsem, char semname[6], int semnum, int initval){
int r=semctl(idsem, semnum, SETVAL, initval);
printf("le semaphore %s a été initialisé avec %d\n",semname, initval);
r=initval;
return r;}
int P(int semid, int sem){
struct sembuf op;
op.sem_num= sem;
op.sem_op= -1;
op.sem_flg=0;
int g =semop(semid, &op, 1);
if(g== -1) perror("semop");
return g;}

//Fonction Ptimed (qst8)
int semtimedop(int semid, struct sembuf *sops, unsigned nsops, struct timespec *timeout);
int Ptimed(int semid, int sem)
{
struct sembuf op;
op.sem_num= sem;
op.sem_op= -1;
op.sem_flg=0;
struct timespec time;
time.tv_sec = 60;
time.tv_nsec = 100;
int g =semtimedop(semid, &op, 1, &time);
if(g== -1) {printf("Voyage annule\n");exit(0);}
return g;}
/*********************/


int V(int semid, int sem){
struct sembuf op;
op.sem_num= sem;
op.sem_op= 1;
op.sem_flg = 0;
int g=semop(semid, &op, 1);
if (g == -1) perror("semop");
return g ;}

int Z(int semid, int sem){
struct sembuf op;
op.sem_num= sem;
op.sem_op= 0;
op.sem_flg = 0;
int g=semop(semid, &op,1);
if(g == -1) perror("semop");
return g;}

//Fonction RowBoat
void RowBoat(void){
printf("Le bateau a demarré !\n");}
/******************/

//Fonction Barriere
void Barriere(int N, int shmid, int semid){
int i;
sdata * sd=NULL;
sd=shmat(shmid,sd,0);
P(semid,4);
sd->cpt=(sd->cpt)+1;
if((sd->cpt)>= N){
V(semid,4);
for(i=0;i<(N-1);i++)
V(semid,3);
sd->cpt=0; }
else
{V(semid,4); P(semid,3);}}
