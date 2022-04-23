//: Synchronization using semaphores
/* #include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
int i=0;
sem_unlink("S"); // Remove the semaphore S if it already exists 
// Open a mutex S and create it if it does not exist. S is initialized to 0. 
sem_t* mutex = sem_open("S", O_CREAT, 0644, 0);
if (mutex == SEM_FAILED) {
printf("Failed to open Semaphore\n");
return -1;
}
if (fork() == 0) ///Child process 
{
for(i=0;i<10;i++){ printf("%c\n",i+65); }
sem_post(mutex); // Signal the Semaphore 
}
else //Parent process 
{
sem_wait(mutex); // Wait for a Semaphore 
for(i=0;i<10;i++){ printf("%d\n",i); }
}
}*/

//change print one char one number
//: Synchronization using semaphores
#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>

int main()
{
int i=0;
sem_unlink("S");
sem_unlink("M");

sem_t* mutex = sem_open("S", O_CREAT, 0660, 0);
sem_t* Mutex = sem_open("M", O_CREAT, 0660, 1);
if (mutex == SEM_FAILED) {
printf("Failed to open Semaphore\n");
return -1;
}
if (fork() == 0) /* Child process */
{
for(i=0;i<10;i++){ sem_wait(Mutex); printf("%c\n",i+65);sem_post(mutex);}
 /* Signal the Semaphore */
}
else /* Parent process */
{
 /* Wait for a Semaphore */
for(i=0;i<10;i++){  sem_wait(mutex); printf("%d\n",i); sem_post(Mutex); }
}
}

