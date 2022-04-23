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
printf ("Chat Space for chatter 2: \n" ) ; 
printf ("--------------------------------\n") ; 

while (1) 
{
msg1 m ;

msgrcv( msqid , &m , sizeof(m) , 1 , 0 ) ; 





printf ( "chatter1 : %s\n" , m.text ) ;


reply r ;
printf ( "chatter2 : ") ; 
gets( r.text) ; 
r.type = m.from ; 

msgsnd ( msqid , &r , sizeof(r) , 0) ; 

//msgctl(msqid , IPC_RMID , NULL ) ; 
} // while 

return 0 ; 

}//main 


