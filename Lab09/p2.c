//yasmeen dalgamouni
//tuqa abu mattar
//noor jaradat 
#include <pthread.h>
#include<semaphore.h>
#include<fcntl.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include <stdlib.h>
#define BUFFER_SIZE 2

//initializaton
int in = 0; //index of producer
int out = 0; //index of consumer
int counter = 0;//index in buffer
int buffer[BUFFER_SIZE];//buffer where we save the data
pthread_mutex_t mutex;//mutex to protect the critical section
//both semaphore for signalling and synchronization
sem_t* semp;//semaphore for poducer signal
sem_t* semc;//semaphore for consumer signal 
int data =0;//data represent the number of data the produced and consumed

void producer()
{
//producer
int nextProduced ;

while (1) {

sleep(2);
//wait the empty signal from the consumer
sem_wait(semc);

//lock themutex that protect the critical section 
pthread_mutex_lock(&mutex);

nextProduced = data;
data++;

//check if the buffer is full 
while(counter == BUFFER_SIZE)
{
printf("Buffer is full\n");
sleep(2);
//unlock the mutex that protect the critical section
pthread_mutex_unlock(&mutex);
}

buffer [in] = nextProduced;//insert the data on the buffer
printf("Producer :\t Sharedbuffer[%i] = %i \n",in, nextProduced);
///find the index for next produced data 
in = (in + 1) % BUFFER_SIZE;
counter++;

sleep(2);
//unlock the mutex that protect the critical section
pthread_mutex_unlock(&mutex);

//send signal to let the cosumer read the full item
sem_post(semp);

}
//pthread_mutex_unlock(&mutex);
}
void consumer()
{
//consumer
int nextConsumed;

while (1) {

sleep(2);
//wait the signal form the producer
sem_wait(semp);

//lock themutex that protect the critical section 
pthread_mutex_lock(&mutex);

//check if the buffer is empty 
while( counter == 0)
{
printf("Buffer is empty\n");
sleep(2);
//unlock the mutex that protect the critical section
pthread_mutex_unlock(&mutex);
}

nextConsumed = buffer[out];//read the data from the buffer
printf("Consumer:\t Sharedbuffer[%i] = %i \n",out, nextConsumed);

//find the index for next consumed data 
out = (out + 1) % BUFFER_SIZE;
counter--;

sleep(2);
//unlock the mutex that protect the critical section
pthread_mutex_unlock(&mutex);

//send signal to let the producer write data to the buffer
sem_post(semc);

}
//pthread_mutex_unlock(&mutex);
}
int main (int argc, char *argv[])
{
sem_unlink("p"); /* Remove the semaphore p if it already exists */
sem_unlink("c"); /* Remove the semaphore c if it already exists */

/* Open a semaphor c and create it if it does not exist. c is initialized to buffer size (represent the number of empty slots ). */
semc = sem_open("c", O_CREAT, 0644, BUFFER_SIZE);

/* Open a semaphore p and create it if it does not exist. p is initialized to 0. (represent the number of full slots )*/
semp = sem_open("p", O_CREAT, 0644, 0);

//check if there is any error on creation the semaphore p
if (semp == SEM_FAILED ) {
printf("Failed to open Semaphore\n");
return -1;
}
//check if there is any error on creation the semaphore c
if (semc == SEM_FAILED)
{
printf("Failed to open Semaphore\n");
return -1;
}

/* thread id or type*/
pthread_t tid_producer;
pthread_t tid_consumer;

int mutin ;
mutin=pthread_mutex_init(&mutex, NULL); /* mutex initialization */
if(mutin != 0)
{
printf("error initialization mutex ! \n ");
return -1;
}
/* thread creation */
int pp,pc;
pp = pthread_create(&tid_producer, NULL, (void*)&producer, NULL);//producer thread//

//check error creating 
if(pp != 0)
{
printf("error creating producer thread ! \n");
return -1;
}

pc = pthread_create(&tid_consumer, NULL, (void*)&consumer, NULL);//consumer thread//

//check error creating 
if(pc != 0)
{
printf("error creating consumer thread ! \n");
return -1;
}

/* The main threads waits for the two threads to finish using pthread_join */
int pj,cj;

pj=pthread_join(tid_producer, NULL);
//check error joining
if(pj != 0)
{
printf("error joining producer thread ! \n");
return -1;
}

cj=pthread_join(tid_consumer, NULL);
//check error joining 
if(cj != 0) 
{
printf("error joining consumer thread ! \n");
return -1;
}

return 0;
}
