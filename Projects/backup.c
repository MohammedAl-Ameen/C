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



struct choice{

long type;
char text1[100];
char text2[100];
bool flag;

};


void main(){


	
	
	

	struct choice send;
	struct choice receive;
	
	if(fork()){
	
	int msid;
	msid = msgget(1234 , IPC_CREAT | 0666);
	
	if(msid < 0)
	printf("error in the message creation \n");
	
	
	
	while(1){
	
	
	char c;
	printf("choice: ");
	scanf(" %c",&c);
	
	
	if(c == '1'){
	
	send.type = 1;
	
	printf("username: ");
	scanf(" %s" , send.text1);
	printf("password: ");
	scanf(" %s" , send.text2);
	
	if(msgsnd(msid , &send , sizeof(struct choice) - sizeof(long int) , 0) < 0)
	printf("error in the message send in parent \n");
	
	
	
	
	if(msgrcv(msid , &receive , sizeof(struct choice) - sizeof(float) , 0 , 0) < 0)
	printf("error in the message receive in the parent \n");
	
	
	
	printf("%s \n \n \n" , receive.text1);
	
	
				
	
	
	}else if(c == '2'){
	
	send.type = 2;
	
	printf("string: ");
        scanf(" %s" , send.text1);
	
	msgsnd(msid , &send , sizeof(struct choice) , 0);
	
	msgrcv(msid , &receive , sizeof(struct choice) , 0 , 0);
	
	printf("\n%s \n", receive.text1);
	
	
	
	
	}else if(c == '3'){
	
	send.type = 3;
	
	printf("number ");
	
	scanf("%s", send.text1);
	
	if(msgsnd(msid , &send , sizeof(struct choice) , 0) < 0)
	printf("error in msgsnd on the parent \n");
	
	
	
	
	
	msgrcv(msid , &receive , sizeof(struct choice) , 0 , 0);
	
	
	
	
	
	printf("\n%s \n", receive.text1);
	
	
	
	}
	}
	
	
	
	
	
	msgctl(msid, IPC_RMID , NULL);
	
	
	}else{
	int msid;
	msid = msgget(1234,0);
	
	while(1){
	
	if(msgrcv(msid , &receive , sizeof(struct choice) , 0 , 0 )<0){
	printf("error in the recive message in the child \n");}
	
	
	
	
	if(receive.type == 1){
	
	
	if(strcmp("tamer" , receive.text1) == 0 || strcmp("123456" , receive.text2) == 0){
	
	strcpy(send.text1 , "Login successfully");
		
	msgsnd(msid , &send , sizeof(struct choice) , 0);
		
	
	}else{
	
	
	
	strcpy(send.text1 , "Login failed");
		
	if(msgsnd(msid , &send , sizeof(struct choice) - sizeof(long int)  , 0) <0){
	printf("error in msgsnd in the child \n");
	break;
	
	}
	
	
				
	
	}
		
		
		
			
	
	
	
	
	
	
	}else if(receive.type == 2){
	
		for(int i = 0; receive.text1[i] ; i++){
		
		
		send.text1[i] = toupper(receive.text1[i]);
		}
		
		msgsnd(msid , &send , sizeof(struct choice) , 0);
		
				
	
	
	}else if(receive.type == 3){
	
	
	
				int sum = 0;
				
				
				
				for(int i = 0; i < strlen(receive.text1) ; i++)
				{
					
					sum += receive.text1[i] - '0';
					
					
				}
				
				
				
				send.type = 3;
				send.text1[0] = sum + '0';
				msgsnd(msid,&send,sizeof(struct choice),0);
				
	
	}
	

	
	}
	
	msgctl(msid, IPC_RMID , NULL);
	
	}



}
