#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/ipc.h>
#include<sys/msg.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<errno.h>
#include<fcntl.h>
#include<ctype.h>
#include<stdbool.h>


void main(){


int x = fork();

if(x){


int y = fork();

printf("x=:%d \t y=%d  \n" ,x , y);


}else{

printf("%d \n" , x);

}




}




