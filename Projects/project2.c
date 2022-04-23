#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>


/*type 1 ==> choice 1, type 2 ==> choice 2,
  type 3 ==> choice 3, type 4 ==> choice 4, 
  type 5 ==> termination (X is entered)*/
struct choice {
	long type;
	char text1[100];
	char text2[100];
};


void main()
{
	//Message Queue Creation
	int msid;
	msid = msgget(1234,IPC_CREAT | 0666);
	
	if(msid < 0)  //Error Checking in MQueue Creation 
	{
		printf("Error in MQueue Creation!\n");
		exit(0);
	}
	struct choice send;
	struct choice receive;
	//Create a child process
	int value = fork();
	
	if(value < 0) // Error Checking in forking
	{
		printf("Error in forking!\n");
		exit(1);
	}
	/*               Parent (Client Process)               */
	if(value > 0)  
	{
		char ch;
		while(1)
		{
			//Main Menu
			printf("Choose one of the following choices : \n");
			printf("1-login\n");
			printf("2-convert to upper\n");
			printf("3-find digits sum\n");
			printf("4-logout\n");
			printf("X for termination\n");
			scanf(" %c",&ch);
			
			if(ch == '1')    //login, message type = 1
			{
				//Determine the type of message
				send.type = 1;
				//Get the credentials (username + password)
				printf("Enter Username : ");
				scanf(" %s",send.text1);
				printf("Enter Password : ");
				scanf(" %s",send.text2);
				
				//Send the credentials to the server 
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
				 	
				//Receive the result, "Invalid Credentials" or "Login Successfully"
				msgrcv(msid,&receive,200,0,0);
				
				//Print the result
				printf("%s\n\n",receive.text1);
			}
			else if(ch == '2') //convert to upper, message type = 2
			{
				//Determine the type of message
				send.type = 2;
				//Get the string that will be converted to uppercase
				printf("Enter String to be converted : ");
				scanf("%s",send.text1);
				
				//Send the string to the server 
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
				 //Receive the result
				 msgrcv(msid,&receive,200,0,0);
				 //Print the result
				 printf("your string : %s\nConverted string : %s\n\n",send.text1,receive.text1);	
				 
			}
			else if(ch == '3') //find digits sum, message type = 3
			{
				int flag =0;
				int i =0;
				//Determine the type of message
				send.type = 3;
				//Get the number of n digits 
				printf("Enter a number of n digits : ");
				scanf("%s",send.text1);
				
				//Check whether the input is number or not
				while(send.text1[i])
				{
					if(!(send.text1[i] <='9' && send.text1[i] >= '0'))
					{
						flag = 1;
						break;
					}
					i++;
				}
				
				
				if(flag == 0) // in case of entering a correct number
				{
					//Send the number to the server
					if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 		printf("Sending message error\n");
				 	 //Receive the result
				 	 msgrcv(msid,&receive,200,0,0);
				 	 //Print the result
					printf("Your number : %s\nSum of its digits  	      %s\n\n",send.text1,receive.text1);				
				}
				else  //in case of entering an incorrect number
				{
					//Print error message tells the user that he entered an incorrect number
					printf("Incorrect Number, Try again!\n");
				}
			}
			else if(ch == '4') //logout, message type = 4
			{	
				//Determine the type of message
				send.type = 4;
				//Send the message to the server
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
				 	
				//Receive the result
				msgrcv(msid,&receive,200,0,0);
				//Print the result
				printf("%s\n",receive.text1);
			}
			else if(ch == 'x' || ch == 'X') //termination, message type = 5
			{	
				 //Determine the type of message
				 send.type = 5;
				 //Send the the 'x' termination choice to the server 
				 if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
				 //Sleep 1 sec waiting the server to terminate and destroy the message queue then 					 terminate itself
				 sleep(1);
				 break;
			}
			else  // print error message in case of choosing an incorrect choice
			{
				printf("Incorrect Choice, Try again!\n");
			}
			
			sleep(1);
		}
		
		
 	}
 	/*               Child (Server Process)               */
	else		
	{
		//Get MQueue id 
		msid = msgget(1234,0);
		while(1)
		{	
			//Receive the message from client process (blocking till get a message)
			msgrcv(msid,&receive,200,0,0);
			
			if(receive.type == 1)  //login, message type = 1
			{	
				
				int ch = 0;
				
				
					
					if(strcmp("m",receive.text1) == 0)
					{
						if(strcmp("m",receive.text2) == 0)
						{
							ch = 1;
							
						}
					}
				
				//Close the file of credentials 
				
				
				if (ch == 1)  //Correct credentials
				{
					//Determine the type of message
					send.type = 1;
					//Send the result to the client process
					strcpy(send.text1,"Login successfully");
					if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
					
				}
				else		//Inorrect credentials
				{
					//Determine the type of message
					send.type = 1;
					//Send the result to the client process
					strcpy(send.text1,"Invalid Credentials");
					if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				 	printf("Sending message error\n");
				}
				
			}
			else if(receive.type == 2) //convert to upper, message type = 2
			{
				char str[100] = "";
				int i=0;
				//Convert the string to uppercase 
				while(receive.text1[i])
				{
					str[i] = toupper(receive.text1[i]);
					i++;
				}
				
				//Determine the type of message
				send.type = 2;
				//Send the result to the client process
				strcpy(send.text1,str);
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				     printf("Sending message error\n");
				
				
			}
			else if(receive.type == 3) //find digits sum, message type = 3
			{	
				int sum = 0;
				int ch ;
				int i = 0;
				//Calculate the sum of digits 
				while(i < strlen(receive.text1))
				{
					ch = receive.text1[i];
					sum += (ch - 48);
					i++;
				}
				
				
				//Determine the type of message
				send.type = 3;
				//Send the result to the client process
				sprintf(send.text1, "%d", sum);
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				     printf("Sending message error\n");
				
				
			}
			else if(receive.type == 4) //logout, message type = 4
			{
				send.type = 4;
				strcpy(send.text1,"Logged out Successfully\n"); 
				if((msgsnd(msid,&send,sizeof(struct choice)-sizeof(long),0)) < 0)
				     printf("Sending message error\n");
				//printf("Logged out Succesfully\n");
			}
			else if(receive.type == 5) //termination, message type = 5
			{	
				printf("Terminated Successfully\n");
				//Destroy the MQueue
				msgctl(msid,IPC_RMID,NULL);
				break;
			}
		}
	}
	
}
