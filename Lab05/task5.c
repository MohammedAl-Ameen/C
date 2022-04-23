#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
struct bankinfomation
{
char username[20];
char password[20];
char balance[20];

}bankinfomation;



int main () 
{
struct bankinfomation info , temp;


   printf("please insert the name of the client\n");
   scanf("%s",(info.username));
   printf("please insert the password of the client\n");
   scanf("%s",(info.password));
int client[2],bank[2], ch ;
pipe(client);
pipe(bank);
ch = fork();

if(ch != 0 )
{
close(client[0]);

write(client[1],&info,sizeof(info));

wait(0);
close(bank[1]);
dup2(bank[0],0);

read(bank[0],&(info.balance),sizeof(info.balance));


if(strcmp(info.balance ,"error")==0)
{
printf("Invaild username or password\n" ); 

}
else
printf("Your balance is: %s$ \n" ,info.balance);
}
else
{
struct bankinfomation info2 , temp ;
close(client[1]);

char var[20];
int i;
FILE *f_read = fopen ("BankRecords.txt","r");
dup2(client[0],0);
int l=0;

read(client[0],&info2,sizeof(info2));
while(!feof(f_read))
{
i= fscanf(f_read , "%s    %s    %s\n",temp.username , temp.password ,temp.balance);

if(strcmp(info2.password,temp.password) == 0 && strcmp(info2.username , temp.username) == 0 ) 
{

close(bank[0]);

write(bank[1],&temp.balance ,sizeof(temp.balance));

}
else
{


close(bank[0]);

write(bank[1],"error",20);

}
}

}


}

