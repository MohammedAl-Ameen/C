#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <string.h>
typedef struct {
char data[100];
int flag ;
}Data;

int main ()
{
int shm_id =shmget(123,sizeof(Data),IPC_CREAT|0777);

int id = fork(); 
if(id != 0 ) 
{
Data *shm = (Data *) shmat(shm_id,NULL,0);
shm->flag=1;

//parent process 
while(1)
{
while(shm->flag != 1);
printf("Enter the  string please : \n");
scanf("%s",shm->data);
shm->flag=2; 

}
shmdt(shm);
}
else 
{
Data *shm = (Data *) shmat(shm_id,NULL,0);

while(1)
{
while(shm->flag!=2);
printf("data = %s \n",shm->data);
shm->flag=1; 

}
shmdt(shm) ;

}
}


