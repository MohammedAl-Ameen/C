#include <sys/types.h>
#include <sys/shm.h> 
#include <sys/ipc.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 
#include <signal.h>

typedef struct 
{
char text[100] ; 
}block ; 

block * b ;

void parent_handler (int signum ) 
{
printf ( "\nEnter text to write on shared memory : \n") ; 
scanf("%s" , b->text ) ;

}

void child_handler ( int signum ) 
{
printf ( "\nchild read from shared memory :\n") ; 
printf("%s\n" , b->text ) ;
}

void main () 
{

int shmid  = shmget (5555 , sizeof(block) , IPC_CREAT|0777) ; 
b= (block*) shmat( shmid , NULL  , 0 ) ; 
int pid = fork() ; 

if( pid ) 
{


signal ( SIGINT , parent_handler ) ;
sleep(5) ; 



while (1) 
{
printf ("\n sending signal to child ... \n" ) ; 
kill(pid , SIGINT);   
sleep(1) ;
}

shmdt(b) ;
}
else 
{

signal ( SIGINT , child_handler ) ;
sleep(1) ; 

//b= (block*) shmat( shmid , NULL  , 0 ) ; 

while (1) 
{ 
kill(getppid() , SIGINT ) ;
sleep(5) ;  
} 

shmdt(b) ;

}

//to delete shared memory 
// shmctl(shmid , IPC_RMID , NULL ) ;  
}
