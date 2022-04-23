#include <stdio.h>
#include "stdlib.h"
#include "stdio.h"
#include "string.h"
#include "sys/wait.h"
#include "unistd.h"
#include "fcntl.h"
#include "sys/types.h"
#include "sys/stat.h"
#include<signal.h>
void main( )
{
int childPID;
childPID = fork();
if(childPID==0)
{
printf("Child is alive\n");
}
else
{
printf("Parent is going to sleep\n");
sleep(10);
printf("Parent is awake, killing child\n");
kill(childPID, SIGKILL);
wait(NULL);
}
}

