#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include<sys/wait.h>
#include <string.h>

typedef struct {
char data[100];
}Data;

Data *shm;

void reader_handler (int signum ) 
{
printf("Data = %s\n" , shm->data ) ;
signal ( SIGINT , reader_handler ) ; 
}


void writer_handler (int signum ) 
{
printf ( "enter the message \n" ) ;
scanf("%s", shm->data);
signal ( SIGINT , writer_handler ) ;
}



int main ()
{
int shm_id =shmget(123,sizeof(Data),IPC_CREAT|0777);
shm = (Data *) shmat(shm_id,NULL,0);
int id = fork(); 
if(id != 0 ) 
{
signal ( SIGINT , writer_handler ) ;
sleep(5) ; 

while (1) 
{
kill(id , SIGINT);   
sleep(1) ;
}
shmdt(shm) ;
}
else 
{
signal ( SIGINT , reader_handler ) ;
sleep(1) ; 
while (1) 
{ 
kill(getppid() , SIGINT ) ;
sleep(5) ;  
} 

shmdt(shm) ;

}
}


