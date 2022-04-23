
//part3
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
//size of file 
long int findSize(char file_name[]) 
{
    FILE* f = fopen(file_name, "r"); 
    if (f == NULL) { 
        printf("No file with this name \n"); 
        return -1; 
    } 
    else
    {

    fseek(f, 0, SEEK_END); 
 
    long int size = ftell(f); 
    fclose(f); 
    return size; 
    }
  
    return -1;
} 
int main (int argc , char * argv[])
{
 int i = 0 ; 

    char *filename = argv[1]; 
    long int size= findSize(filename); 
    if (size != -1) 
        printf("Size of the file is %ld bytes \n", size); 
        }
    return 0; 
}
