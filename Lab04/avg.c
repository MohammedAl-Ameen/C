#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
void main(int argc , char * argv[])
{
if(argc <2 ) 
{
printf("error, need more arguments \n " ) ;
exit(0);  
}
else 
{
float sum = 0; 
int i= 1 ; 
for( ; i < argc ;i++)
{
sum = atoi(argv[i]) + sum ; 
}
printf("The average = %f \n ", sum/(argc-1));
}
}
