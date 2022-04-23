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



typedef struct {

long choice;
char data1[100];
char data2[100];


}send;

typedef struct{

long choice;
char data1[100];
char data2[100];


}receive;


void main(){

	
	
	


	
	if(fork()){
	
	bool flag = false;
	bool flagnumber = false;
	int msid;
	msid = msgget(6789,IPC_CREAT|0766);
	
	send message_send;
	receive message_receive;
	
	
	
	if(msid < 0)
	perror("Error: ");
	
	
	while(1){
	
	
	char c[200]; 
	
	
	printf("choice: ");
	
	scanf(" %s",c);
	
	if(strlen(c) == 1){
	
	
	if(c[0] == '1'){
	
	if(!flag){
	
	message_send.choice = 1;
	
	printf("username: ");
	scanf("%s" , message_send.data1);
	printf("password: ");
	scanf("%s" , message_send.data2);
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long)  , 0) < 0)
	perror("msgsnd in parent, Error: ");

	
	
	if(msgrcv(msid , &message_receive , 200 , 0 , 0) < 0)
	perror("msgrcv in parent, Error: ");
	
	if(strcmp( message_receive.data1 , "Login successfully...") == 0)
	flag = true;
	
	
	
	
	printf("%s \n \n \n" , message_receive.data1);
	
	}else{printf("You are already logged-in \n");}
				
	
	
	}else if(c[0] == '2'){
	
	if(flag){	
	
	message_send.choice = 2;
	
	printf("string: ");
      	scanf(" %s" , message_send.data1);
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)
	perror("Error: ");
	
	if(msgrcv(msid , &message_receive , sizeof(message_receive) - sizeof(long) , 0 , 0) < 0)
	perror("Error: ");
	
	printf("%s \n \n \n" , message_receive.data1);
	
	}else{
	
	printf("you need to login \n");
	
	}
	
	
	}else if(c[0] == '3'){
	
	if(flag){	
	message_send.choice = 3;
	
	printf("number ");
	
	scanf(" %s" , message_send.data1);
	
	for(int i = 0 ;i < strlen(message_send.data1) ; i++){
		if(!((message_send.data1[i] >= 48) && (message_send.data1[i] <= 57))){
			flagnumber = true;
	}
	
	}
	if(!flagnumber){
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)
	perror("Error: ");
	
	if(msgrcv(msid , &message_receive , sizeof(message_receive) - sizeof(long) , 0 , 0) < 0)
	perror("Error: ");
	
	printf("%s \n \n \n" , message_receive.data1);
	
	}else{printf("wrong input \n");}
	
	}else{
	
	printf("you need to login \n");
	
	}
	
		
	
	
	
	
	}else if(c[0] == '4'){
	
	if(flag){
	message_send.choice = 4;
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)
	perror("Error: ");
	
	if(msgrcv(msid , &message_receive , sizeof(message_receive) - sizeof(long) , 0 , 0) < 0)
	perror("Error: ");
	
	printf("%s \n \n \n" , message_receive.data1);
	
	flag = false;
	
	}else{printf("you need to login \n");}
	
	
	
	}else if(c[0] == 'x' || c[0] == 'X'){
	
	message_send.choice = 5;
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0){
	perror("Error: ");
	printf("The termination didn't work \n");
	
	}
	
	if(msgrcv(msid , &message_receive , sizeof(message_receive) - sizeof(long) , 0 , 0) < 0){
	perror("Error: ");
	printf("The termination didn't work \n");
	
	
	}
	
	
	if(strcmp("okey" , message_receive.data1) == 0){
	
	printf("The system has terminated \n");
	
	break;
	
	
	}else{
	
	
	printf("The termination didn't work \n");
	
	
	}
	
	}else {
	
	printf("You choice is bad try later good bye \n");
	
	}
	
	
	
	}else {
	
	printf("\nYour choice is like your face, everything wrong with it \n \n");
	break;
	
	}
	}
	
	
	
	
	
	
	
	
	}else{
	
	
	int msid;
	
	
	
	send message_send;
	receive message_receive;
	
	
	
	
	if((msid = msgget(6789,0))< 0)
	perror("Error: ");
	
	if(msid < 0)
	perror("Error: ");
	
	
	
	
	
	
	while(1){
	
	if(msgrcv(msid , &message_receive , sizeof(message_receive) - sizeof(long) , 0 , 0) < 0)
	perror("\nmsgrcv in child, Error: ");
	
	
	
	
	
	
	if(message_receive.choice == 1){
	
	message_send.choice = 1;
	
	if(strcmp("1" , message_receive.data1) == 0 || strcmp("1" , message_receive.data2) == 0){
	
	
	

	strcpy(message_send.data1 , "Login successfully...");
	
	
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long), 0) < 0)
	perror("msgsnd in child: ");
		
	
	}else{
	
	
	
	strcpy(message_send.data1 , "Login failed");
		
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)
	perror("msgsnd in child: ");
	
	
	}
	
	
				
	
	}else if(message_receive.choice == 2){
	
	message_send.choice = 2;
	
	int i;
		for(i = 0; message_receive.data1[i] ; i++){
		
		
		message_send.data1[i] = toupper(message_receive.data1[i]);
		}
		
		message_send.data1[i] = '\0';
		
		
		printf("%s \n \n \n" , message_send.data1);
		
		if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)
		perror("Error: ");
		
				
	
	
	}else if(message_receive.choice ==  3){
	
	
		message_send.choice = 3;
			
			
			
		int sum = 0;
		
		printf("length: %ld \n",strlen(message_receive.data1));
		
			
		
		for(int i = 0; i < strlen(message_receive.data1) ; i++)
		{
			
			sum += message_receive.data1[i] - '0';
			printf("sum: %d \n",sum);
					
		}
				
		printf("sum: %d \n",sum);
		
		sprintf(message_send.data1, "%d", sum);
				
		if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)	
		perror("Error: ");
				
	
	}else if(message_receive.choice == 4){
	
	message_send.choice = 4;
	
	strcpy(message_send.data1 , "Logout successfully");
	
	if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long) , 0) < 0)	
	perror("Error: ");
	
	
	}else if(message_receive.choice == 5){
	
	      message_send.choice = 5;
	      
	      strcpy(message_send.data1 , "okey");
	
	
	      if(msgsnd(msid , &message_send , sizeof(message_send) - sizeof(long), 0) < 0)
	      perror("msgsnd in child: ");
	      
	      msgctl(msid,IPC_RMID,NULL);
	      break;
	     
	      
	
	
	
	}
	

	
	}
	
	
	
	
	}



}
