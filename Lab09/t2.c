/*[File t2.c] use mutex to access critical area.
compile using: gcc -o t1 t1.c -lpthread */
#include <stdio.h>
#include <pthread.h>
pthread_mutex_t mutex;
int v;
/* global variable: mutex */
/* global variable: v */
void increment(){
int i, a;
for( i = 0; i < 99; i++){
pthread_mutex_lock(&mutex);
/* critical section */
a = v + 10;
usleep(1);
v = a;
/* end of critical section */
pthread_mutex_unlock(&mutex);
}
}
void decrement(){
int i, a;
for(i = 0; i < 99; i++){
pthread_mutex_lock(&mutex);
/* critical section */
a = v - 10;
usleep(2);
v = a;
/* end of critical section */
pthread_mutex_unlock(&mutex);
}
}
int main (int argc, char *argv[])
{
/* thread id or type*/
pthread_t tid_increment;
pthread_t tid_decrement;
v = 0;
/*initialize v as 0 */
pthread_mutex_init(&mutex, NULL); /* mutex initialization */
/* thread creation */
pthread_create(&tid_increment, NULL, (void*)&increment, NULL);
pthread_create(&tid_decrement, NULL, (void*)&decrement, NULL);
/* The main threads waits for the two threads to finish using pthread_join */
pthread_join(tid_increment, NULL);
pthread_join(tid_decrement, NULL);
printf("v=%d\n",v);
return 0;
}
