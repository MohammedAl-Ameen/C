#include <sys/ipc.h>
#include <sys/shm.h> 
#include <stdio.h>
#include <stdlib.h>


void main ()
{
int id ;
char name[100];
float mark;
int i;
FILE *f_read= fopen ("students.txt","r");
while( ! feof(f_read))
{
i= fscanf(f_read , "%i    %s    %f\n", &id , &name ,&mark);
printf("%i    %s    %f    \n ", id  , name ,mark );
}
}
