//part1
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main()
{
 
    
      FILE * file = fopen("Myfile.txt", "w");

    if(file == NULL)
    {
       
        printf("Error on create the file !!!\n");
        exit(0);
    }
    
    char * data = "the quick brown fox jumps over the lazy dog";


    fputs(data, file);


 
    fclose(file);


    printf("File created and saved successfully. \n");


    return 0;
}


