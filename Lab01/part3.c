#include<stdio.h>

#include<stdlib.h>

#include<string.h>

void main(int argc , char *argv[]){

double length, width , radius , result;


if(strcmp(argv[1] , "s") == 0){

length = atof(argv[2]);

result = length * length;


}else if(strcmp(argv[1] , "r") == 0){

length = atof(argv[2]);

width = atof(argv[3]);

result = width * length;


}else if(strcmp(argv[1] , "c") == 0){

radius = atof(argv[2]);

result = 3.14*radius*radius;

}else{

printf("There is no parameter input\n");

}

printf("Result= %f\n" , result);



}
