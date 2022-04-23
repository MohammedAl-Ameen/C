#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
void main(int argc,char **argv,char** envp)
{
  while(1)
  {
    char command1[50];
    char command2[50];
    printf("mohammed>>");
    gets(command1);
    strcpy(command2, command1);

    int size = 0;
    char *token = strtok(command1, " ");
    while (token!=NULL)
    {
        token = strtok(NULL, " ");
        size += 1;
    }
    char **str = (char **)malloc(size * sizeof(char *));
    token = strtok(command2, " ");
    int sizet;
    for (int i = 0; token != NULL;i++)
    {
        sizet = strlen(token) + 1;
        str[i] = (char *)malloc(sizet * sizeof(char));
        strcpy(str[i], token);
        str[i][sizet - 1] = NULL;

        token = strtok(NULL, " ");
    }

   /* for (int i = 0; i < strlen(*str);i++)
    {
        printf("str[%i]....%s\n", i, str[i]);
    }*/

    if(strcmp(str[0],"exit")==0)
    {
        exit(0);
    }
    else if (strcmp(str[0],"clear")==0)
    {
        system(str[0]);
    }
    else if (strcmp(str[0],"pwd")==0)
    {
        system(str[0]);
    }
    else if (strcmp(str[0],"listen")==0)
    {
        char **en = envp;
        while(en!=NULL)
        {
            printf("%s\n", *en++);
        }
    }
    else 
    {
        printf("Command Not Found \n");
    }
  }
}
