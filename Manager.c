#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>


typedef struct employee{
    char* ID;
    char EmployeeName[50];
    char JobTitle[100];
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
} __attribute__((packed))employee;



int main ()
{	
	pid_t pida, parent;
	
	employee* emp = malloc(sizeof(*emp));
	int rv;
	int commpipe[2]; //This holds the fd for the input & output of the pipe 
	
	if(pipe(commpipe)){
		fprintf(stderr, "Pipe error");
		exit(1);
	}
	
	parent = getpid(); //get parent of me 
	
	
	pida = fork();
	
	if(pida == -1){
		fprintf(stderr, "Fork error 1. Exiting.");
		exit(1);
	}
	
	if(pida == 0){
		//if zero PID shows this is the child 
		//sleep(5);
		read(commpipe[0], emp, sizeof(*emp));
		printf("%s pipe output %s\n", emp -> JobTitle, emp -> EmployeeName);
		//exit(0);
	}
	else{
		//if positive PID is a parent
		char ch;
		
		do{
			//system("clear");


			printf("Please enter the employee's name: ");
			scanf("%s", emp -> EmployeeName);



			printf("Please enter the Employee's job title: ");
			scanf("%s", emp -> JobTitle);

			printf("Please Enter the Employee's status: ");
			scanf("%s", emp -> Status);
		
			printf("Do you wish to enter another employee? Y/N: ");
			scanf("%s", &ch);
			write(commpipe[1], emp, sizeof(*emp));
		}while (ch == 'y' || ch == 'Y');
	}
}