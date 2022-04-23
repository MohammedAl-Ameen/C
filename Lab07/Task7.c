#include <stdio.h> 
#include <signal.h>
#include <stdlib.h>
int i = 0 ; 

void int_handler (int signum ) 
{
printf ( "%d\n" , i) ;
i++ ; 
}


void char_handler (int signum ) 
{
printf ( "%c\n" , i+65) ;
i++ ; 
}


int main () 
{ 
int pid;
pid = fork();
  
if (pid == 0) 
{
     signal ( SIGINT , char_handler ) ; 
     sleep(1) ; 
                    
     for (  int k = 0 ; k<10 ; k++ ) 
     {     
     kill ( getppid() , SIGINT) ;
     sleep(1) ; 
     } 

            
}
else 
{      
   
        signal ( SIGINT , int_handler ) ;
        sleep(1) ; 
          
        for( int j = 0 ; j<10 ; j++ ) 
        {
         kill ( pid , SIGINT) ;  
         sleep(1) ; 
        }
       
} // parent
}
