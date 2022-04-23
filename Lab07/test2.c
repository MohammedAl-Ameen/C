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
void my_handler(int);

void main( )
{
//signal(SIGINT, my_handler);
signal(SIGINT, SIG_IGN);
printf("[%d] Entering infinite loop\n", getpid());
while(1) { sleep(10); }
}

void my_handler(int signo)
{
printf("Running my new signal handler for signal %d\n", signo);
}
