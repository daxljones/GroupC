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



int Manager ()
{	
	pid_t pida;
	
	employee* emp = malloc(sizeof(*emp));
	int rv;
	int commpipe[2]; //This holds the fd for the input & output of the pipe 
	
	if(pipe(commpipe)){
		fprintf(stderr, "Pipe error");
		exit(1);
	}	
	
	pida = fork();
	
	if(pida == -1){
		fprintf(stderr, "Fork error 1. Exiting.");
		exit(1);
	}
	
	if(pida == 0){ //assistant
		struct employee *search,*result;
		while(1){
			//receives message from manager and creates struct from message
			read(commpipe[0], emp, sizeof(*emp));
			struct employee *search, *result;
			int found = 0;
			int found2 = 0;
			int rewrite = 0;

			//opens history file
			FILE *fptr, *temp;
			char fileName[] = "history";
			fptr = fopen(fileName, "ab+");

			printf("Searching for %s with title %s and status %s\n",emp->EmployeeName,emp->JobTitle,emp->Status);

			//checks if message is in the history file
			while(fread(search, sizeof(struct employee), 1, fptr)){
				if(!strcmp(emp->EmployeeName,search->EmployeeName) && !strcmp(emp->Status,search->Status) && !strcmp(emp->JobTitle,search->JobTitle) {
					result = search;
					found = 1;
					break;
				}
				printf("%s was not found in history file\n",emp->EmployeeName);
			}

			if(!found){
				//make request to server and receive result
				printf("We would make a request to the server at this point but that functionality is not completed\n");
				if(!found2){
					printf("%s was not found\n",emp->EmployeeName);
				}else{
					//rewrite history file
					temp = fopen("temp", "ab+");
					for(int i = 0; i < 10; i++){
						if(rewrite % 10 == i){
							fwrite(result, sizeof(struct employee), 1, temp);
						}
						else{
							fread(search, sizeof(struct employee), 1, fptr);
							fwrite(search, sizeof(struct employee), 1, temp);
						}
						remove(fileName);
						rename("temp",fileName);
						fclose(temp);
					}
				}			
			}
			fclose(fptr); 
		}
	}
	else{ //manager
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

		kill(pida, SIGKILL);
	}
}