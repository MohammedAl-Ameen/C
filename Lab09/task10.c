//producer_consumer problem
#include <stdio.h>
#include <pthread.h>
#define BUFFER_SIZE 5
int in = 0; //index of producer
int out = 0; //index of consumer
int counter = 0;//index in buffer
char buffer[BUFFER_SIZE];
pthread_mutex_t mutex;

void producer()
{
//producer
//pthread_mutex_lock(&mutex);
char ch = 'a';
char nextProduced ;
char nextProd ;
while (1) {
pthread_mutex_lock(&mutex);
nextProd = ch;
if(nextProd <= 'z')
{
nextProduced = nextProd ;
} 
else
{
ch='a';
nextProduced = ch;
}
ch=ch+1;
if(counter == BUFFER_SIZE)
{
printf("Buffer is full\n");
sleep(3);
pthread_mutex_unlock(&mutex);
}

buffer [in] = nextProduced;
in = (in + 1) % BUFFER_SIZE;
counter++;
printf("Produced %i %c\n",in, nextProduced);
sleep(2);
pthread_mutex_unlock(&mutex);


}
//pthread_mutex_unlock(&mutex);
}
void consumer()
{
//consumer
//pthread_mutex_lock(&mutex);
int timer = 0;
char nextConsumed;
while (1) {
pthread_mutex_lock(&mutex);
if(counter == 0)
{
printf("Buffer is empty\n");
sleep(2);
pthread_mutex_unlock(&mutex);
}
nextConsumed = buffer[out];
out = (out + 1) % BUFFER_SIZE;
counter--;
printf("Consumed %i %c\n",out, nextConsumed);
sleep(3);
pthread_mutex_unlock(&mutex);


}
//pthread_mutex_unlock(&mutex);
}
int main (int argc, char *argv[])
{
/* thread id or type*/
pthread_t tid_producer;
pthread_t tid_consumer;
/*initialize v as 0 */
pthread_mutex_init(&mutex, NULL); /* mutex initialization */
/* thread creation */
pthread_create(&tid_producer, NULL, (void*)&producer, NULL);
pthread_create(&tid_consumer, NULL, (void*)&consumer, NULL);
/* The main threads waits for the two threads to finish using pthread_join */
pthread_join(tid_producer, NULL);
pthread_join(tid_consumer, NULL);
return 0;
}
