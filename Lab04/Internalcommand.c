#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>
void main () 
{

execlp("part1","part1", "20 30 40" , NULL);
}
