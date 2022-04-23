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
struct sockaddr_in address;
address.sin_family = AF_INET; //ipv4
address.sin_port = htons(5000);
address.sin_addr.s_addr = INADDR_ANY;
// initiate the connection with server
socklen_t len = sizeof(address);
if(bind(sid, (struct sockaddr*)&address,len)<0)
{
perror("Cannot bind address block withsocket !!!\n");
exit(1);
}
while(1)
{
if(listen(sid, 3)<0)
{
perror("Can find a stableconnection !!!\n");
exit(1);
}
int client_s;
if((client_s = accept(sid,(struct
sockaddr*)&address,&len))<0)
{
perror("Failed to connect withtarget client!!\n");
exit(1);
}

char str [100];
char str2[100];
char tt;

read(client_s, str,sizeof(char)*100);
for(int i=0;i<100;i++)
{
tt=str[i];
str2[i]=toupper(tt); 
}
printf("the string in upper case is : %s \n",str2);
}
}

