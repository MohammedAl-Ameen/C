#include<stdio.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<stdlib.h>
#include <arpa/inet.h>
#include<string.h>
int main()
{
// create socket in client side
int sid = socket(AF_INET, SOCK_STREAM,0);
if(sid <0)
{
perror("Cannot define a TCP socket !!!\n");
exit(1);
}
// define the socket addresses
struct sockaddr_in address;
address.sin_family = AF_INET; //ipv4
address.sin_port = htons(5000);
address.sin_addr.s_addr = INADDR_ANY;
// initiate the connection with server
socklen_t len = sizeof(address);
if(bind(sid, (struct sockaddr*)&address,len)<0)
{
perror("Cannot bind address block with socket !!!\n");
exit(1);
}
while(1)
{
if(listen(sid, 3)<0)
{
perror("Can find a stable connection !!!\n");
exit(1);
}
int client_s;
if((client_s = accept(sid,(struct
sockaddr*)&address,&len))<0)
{
perror("Failed to connect with target client!!\n");
exit(1);
}
int down[10];
read(client_s, down,sizeof(int)*10);
float avg =0;int i=0;
for(;i<10;i=i+1)
avg = avg+down[i];
avg = avg/10;
printf("The average of numbers received from client:%.2f\n",avg);
}
}
