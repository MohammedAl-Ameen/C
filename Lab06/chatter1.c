#include <stdio.h> 
#include <stdlib.h>
#include <string.h> 
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>


typedef struct 
{
long type ; 
long from ; 
char text[100] ; 

}msg1 ; 

typedef struct 
{
long type ; 
long from ; 
char text[100] ; 

}reply ; 


int main ()
{
int msqid = msgget ( 6789 , IPC_CREAT|0766) ;
printf (" Chat Space for chatter 1 : \n" ) ; 
printf ("--------------------------------\n") ; 

while (1) 
{
msg1 m ; 
m.type = 1 ;
m.from = getpid(); 


printf("chatter1 : ") ;
gets( m.text ) ; 

msgsnd ( msqid , &m , sizeof(m) , 0) ; 

reply r ; 
msgrcv( msqid ,&r , sizeof (r) , getpid() , 0 ) ; 
 
printf("chatter2: %s \n" , r.text ) ; 
}//while
return 0 ; 
}
