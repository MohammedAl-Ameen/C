//Race conditions
#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
int main(){
sem_unlink("S");
sem_t* mutex = sem_open("S", O_CREAT, 0660, 0);
int shmid = shmget(25318,sizeof(int),IPC_CREAT|0666);
int i;
int *x = shmat(shmid, NULL,0);
*x = 0;
printf("Initial value X = %d\n", *x);
if (fork() == 0) /* Child process */
{

for(i=0;i<1000000;i++) *x = *x + 1;
sem_post(mutex); 
}
else if(fork()==0) /* Parent process */
{
sem_wait(mutex); 
for(i=0;i<1000000;i++) *x = *x - 1;
}
else
{
wait(NULL);
wait(NULL);
printf("Final value X = %d\n", *x);
}
}
