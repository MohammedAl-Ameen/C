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
#include <stdbool.h>


typedef struct{ 
long type ;
char name [200];
char password [200];
char choice [200];
char message [200];
char num [200];
char sum [200];
}text_message1;
typedef struct  { long type ; char state [200];} text_message2;


void main ()
{


if(fork()){


 int msid ;
 int s;
 
msid =msgget(75 ,IPC_CREAT |0766);

if(msid==-1){
printf("error1\n");exit(1);}
else
{
while(1){
text_message1 mess1;
mess1.type=1;
printf("\n******************************\n1- login\n2-convert to uper\n3-find digits sum\n4-log out\n4-x for termination\n******************************\n "); 
printf("choice : "); 
gets(mess1.choice);

switch(mess1.choice [0]){
case'1':
{

printf("enter your name: "); 
gets(mess1.name);
printf("enter your password: "); 
gets(mess1.password);


s=msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
if (s < 0 ){
printf("error2\n");exit(0);
}
 text_message2 mess2;
 msgrcv(msid,&mess2,sizeof(mess2),2,0);
printf("%s \n", mess2.state);
break;
}
case '2':{
printf("enter any string: "); 
gets(mess1.message);

s=msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
if (s < 0 ){
printf("error2\n");exit(0);}

text_message1 mess2;
 msgrcv(msid,&mess2,sizeof(mess2),2,0);
printf("%s \n", mess2.message);
break;
}
case '3':{
printf("enter any number: "); 
gets(mess1.num);

s=msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
if (s < 0 ){
printf("error2\n");exit(0);}
text_message1 mess13;
printf("%s \n", mess13.sum);
break;}

case '4':
{
s=msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
if (s < 0 ){
printf("error2\n");exit(0);
}
 text_message2 mess2;
 msgrcv(msid,&mess2,sizeof(mess2),2,0);
printf("%s \n", mess2.state);

break;}
case 'x':
{
s=msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
exit(0);
break;}


}
}}


}else{

int msid =msgget(75 ,IPC_CREAT|0766);

 while(1){

text_message1 mess1; 
msgrcv(msid,&mess1,sizeof(mess1),1,0);
 
if(strcmp(mess1.choice,"x")==0){exit(0);}

else{ 
	switch(mess1.choice [0])
{ case '1':{
	text_message2 mess2;
	mess2.type =2;
	
	if((strcmp(mess1.name,"anas")==0) && (strcmp(mess1.password,"1999")==0))
	{
	strcpy(mess2.state,"login");
	}
	else{
	strcpy(mess2.state,"invalid");}
 	
	msgsnd(msid , &mess2 ,sizeof(mess2) ,0);
       if(strcmp(mess1.choice,"x")==0){exit(0);}
	break;
}

case '2':
{
char upper[200];
for(int i=0 ;i<strlen(mess1.message);i++)
{
   
   upper[i]=toupper(mess1.message[i]); 
}
text_message1 mess2;
strcpy(mess2.message,upper);

msgsnd(msid , &mess2 ,sizeof(mess2) ,0);     
break;}

case '3':{
int sum=0;
for(int i=0 ;i<sizeof(mess1.num);i++)
{
   sum= sum + atoi(mess1.num[i]); 
}
sprintf(mess1.sum,"%d",sum);
msgsnd(msid , &mess1 ,sizeof(mess1) ,0);
break;}

case '4':{
	text_message2 mess2;
	mess2.type =2;
	
	strcpy(mess2.state,"loged out");

	msgsnd(msid , &mess2 ,sizeof(mess2) ,0);

       
	break;

}
}
}
}

}


}
