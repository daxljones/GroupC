//Kellen Riley 
//this was the way we used pipes in the manager and assistant

#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <sys/wait.h>


typedef struct employee{
    char* ID;
    char* EmployeeName;
    char JobTitle[50];
    char BasePay[10];
    char OvertimePay[10];
    char Benefit[10];
    char Status[10];
    char satisfaction_level[10];
    char number_project[10];
    char average_monthly_hours[10];
    char time_spend_company_in_years[10];
    char Work_accident[10];
    char promotion_last_5years[10];
}_attribute__ ((packed)) employee;

int main(){
	pid_t pida, parent;
	
	employee* emp = malloc(sizeof(*emp));
	int rv;
	int commpipe[2]; //This holds the fd for the input & output of the pipe 
	
	if(pipe(commpipe)){
		fprintf(stderr, "Pipe error");
		exit(1);
	}
	
	parent = getpid(); //get parent of me 
	printf("main parent = ", getpid());
	
	pida = fork();
	
	if(pida == -1){
		fprintf(stderr, "Fork error 1. Exiting.");
		exit(1);
	}
	
	if(pida == 0){
		//if zero PID shows this is the child 
		sleep(5);
		read(commpipe[0], emp, sizeof(*emp));
		printf("%s pipe output %s\n", emp -> ID, emp -> EmployeeName);
		exit(0);
	}else{
		//if positive PID is a parent
		//testing inputs 
		employee* empOne = malloc(sizeof(*empOne));
		empOne->ID = "0001";
		empOne->EmployeeName = "Kellen";
		
		write(commpipe[1], empOne, sizeof(*empOne));
		sleep(2);
		printf("main parent");
		wait(&rv);
		fprintf(stderr, "child exited with a value\n", rv);
		}
	return 0;
}