#include <sys/types.h>
#include <sys/shm.h> 
#include <sys/ipc.h>
#include <stdlib.h> 
#include <stdio.h> 
#include <string.h> 


typedef struct 
{
char text[100] ; 
int flag ; 

}block ; 

void main () 
{

int shmid  = shmget (5555 , sizeof(block) , IPC_CREAT|0777) ; 

int pid = fork() ; 
if( pid ) 
{
block* b= (block*) shmat( shmid , NULL  , 0 ) ; 
b->flag = -1 ; //old info ; 

while (1) 
{
while(b->flag != -1) ; 

scanf("%s" , b->text ) ;
b->flag = 1 ; //new info
 
} 

shmdt(b) ;

}
else 
{
block* b= (block*) shmat( shmid , NULL  , 0 ) ; 


while (1) 
{
while ( b->flag != 1);
//sleep(2) ;  
printf("%s\n" , b->text ) ;
b->flag = -1 ; 

} 

shmdt(b) ;

}



//to delete shared memory 
// shmctl(shmid , IPC_RMID , NULL ) ;  
}
