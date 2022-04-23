#include<stdio.h>

#include<stdlib.h>

#include<string.h>

void main(int argc, char *argv[]){
int num,result = 0, argnum , num3;
argnum= argc;

if(strcmp(argv[1], "+") == 0){

for(int i = 2; i != argnum; i++){
num = atoi(argv[i]);

result += num;
}


}else if(strcmp(argv[1], "-") == 0){

for(int i = 2; i != argnum ; i++){

if(i == 2){

result = atoi(argv[i]);

}else{

num = atoi(argv[i]);

result -= num; 

}


}}

else if(strcmp(argv[1], "x") == 0){

for(int i = 2; i != argnum ; i++){
if(i == 2){

result = atoi(argv[i]);

}else{

num = atoi(argv[i]);

result *= num; 

}

}
}else if(strcmp(argv[1], "/") == 0){


for(int i = 2; i != argnum ; i++){
if(i == 2){

result = atoi(argv[i]);

}else{

num = atoi(argv[i]);

result /= num; 

}



}



}



printf("result=%d\n",result);




}
