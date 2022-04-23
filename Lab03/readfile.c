
//part2
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

long int findszie(char file_name[])
{

FILE* f = fopen(file_name , "r");

if(f == NULL){

printf("No file with this name \n");
return -1;

}else{

fseek(f , 0 ,SEEK_END );

long int size = ftell(f);

fclose(f);

return size;

}



}


int main ()
{
long int size;

  
size = findszie("students.txt");
 
     FILE * fPtr;
   fPtr = fopen("students.txt", "r");
    if(fPtr == NULL)
    {
       
        printf("Error on open the file !!!\n");
      return -1 ; 
        
    }
    else
    {
     char * str =(char *)malloc((size+1)*sizeof(char));
  int read = fread(str,sizeof(char),size+1,fPtr);
printf("%s \n" , str ) ; 
    }

  fclose(fPtr);
}

