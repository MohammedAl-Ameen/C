#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<string.h>

typedef struct {
char name[50] ; 
double gpa ; 
long int id  ;
}student;


void sort(student arr[10], int numberOfSutdents)
{

  student temp;  
    for (int i = 0; i < numberOfSutdents - 1; i++)
    {
        for (int j = 0; j < (numberOfSutdents - 1 -i); j++)
        {
            if (arr[j].gpa < arr[j + 1].gpa)
            {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            } 
        }
    }
}

void main()
{
student students[10] ;
int i= 0 ; 
for(int i = 0;i<10;i++)
{
printf("Insert the name of the student: ") ;
scanf("%s" , students[i].name);
printf("Insert the gpa of the student: ") ;
scanf("%lf" , &students[i].gpa);
printf("Insert the id of the student: ") ;
scanf("%ld" , &students[i].id);
}
int ch = fork();
if(ch == 0 )
{

sort(students,10) ;

printf("I'm in the child \n" ) ;
for(int i = 0 ;i<10;i++)
{
printf("Name : %s\t",students[i].name) ;
printf("GPA : %lf\t" ,students[i].gpa) ;
printf("ID : %ld\n" ,students[i].id) ;
}
}
else
{
wait(0);


printf("I'm in parent \n" ) ;
for(int i = 0 ; i < 10 ; i++)
{
printf("Name : %s\t",students[i].name) ;
printf("GPA : %lf\t" ,students[i].gpa) ;
printf("ID : %ld\n" ,students[i].id) ;
}
}
}
