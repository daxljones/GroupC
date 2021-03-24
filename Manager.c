#include "functions.h"
#include "structs.h"


void assistant();


void Manager ()
{	
	pid_t pida;
	
	struct employee* emp = malloc(sizeof(*emp));
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
		
		assistant();
		
	}
	// else{ //manager
	// 	char ch;
		
	// 	do{
	// 		//system("clear");
	// 		printf("Please enter the employee's name: ");
	// 		scanf("%s", emp -> EmployeeName);
	// 		fflush(stdin);

	// 		printf("Please enter the Employee's job title: ");
	// 		scanf("%s", emp -> JobTitle);

	// 		printf("Please Enter the Employee's status: ");
	// 		scanf("%s", emp -> Status);
	// 		fflush(stdin);
		
	// 		printf("Do you wish to enter another employee? Y/N: ");
	// 		scanf("%s", &ch);
	// 		fflush(stdin);
			
	// 		write(commpipe[1], emp, sizeof(*emp));
	// 	}while (ch == 'y' || ch == 'Y');

		//kill(pida, SIGKILL);
	//}

	wait(NULL);
}


void assistant(){
	
	struct employee* emp = malloc(sizeof(*emp));
	int rv;
	int commpipe[2]; //This holds the fd for the input & output of the pipe 
	struct employee *search,*result;
	//while(1){
		//receives message from manager and creates struct from message
		// read(commpipe[0], emp, sizeof(*emp));
		// struct employee *search, *result;
		// int found = 0;
		// int found2 = 0;
		// int rewrite = 0;
		
		
		int clientSocket, ret;
		struct sockaddr_in serverAddr;
		struct employee employee;
		struct employee *e = &employee;

		strcpy(e->EmployeeName, "JOSEPH DRISCOLL");
		strcpy(e->JobTitle, "CAPTAIN, FIRE SUPPRESSION");
		strcpy(e->Status, "PT");
		

		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		close(clientSocket);
		clientSocket = socket(AF_INET, SOCK_STREAM, 0);
		if(clientSocket < 0)
		{
			printf("ERROR IN CONNECTION");
			exit(1);
		}
		printf("Socket Created!\n");

		memset(&serverAddr, '\0', sizeof(serverAddr));
		serverAddr.sin_family = AF_INET;
		serverAddr.sin_port = htons(PORT);
		serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

		ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
		//opens history file
		// FILE *fptr, *temp;
		// char fileName[] = "history";
		// fptr = fopen(fileName, "ab+");

		//printf("Searching for %s with title %s and status %s\n",e->EmployeeName,e->JobTitle,e->Status);

		//checks if message is in the history file
		// while(fread(search, sizeof(struct employee), 1, fptr)){
		// 	if(!strcmp(e->EmployeeName,search->EmployeeName) && !strcmp(e->Status,search->Status) && !strcmp(e->JobTitle,search->JobTitle)) {
		// 		result = search;
		// 		//found = 1;
		// 		break;
		// 	}
		// }

		//if(!found){
			//make request to server and receive result
			
			if(ret < 0)
			{
				printf("ERROR IN CONNECTION2");
				exit(1);
			}
			printf("CONNECTED TO SERVER\n\n");


				printf("Sending EmployeeName:\t%s\n", e->EmployeeName);
				send(clientSocket, e, sizeof(struct employee), 0);

				if(recv(clientSocket, e, sizeof(struct employee), 0) < 0)
				{
					printf("ERROR recieving");
				}
				else
				{
					printf("Found! Now sending...\n");
					printf("ID: %d\n", e->ID);
					printf("Name: %s\n", e->EmployeeName);
					printf("SL: %f\n", e->satisfaction_level);
					printf("NP: %d\n", e->number_project);
					printf("AVGH: %d\n", e->average_monthly_hours);
					printf("TSCY: %d\n", e->time_spend_company_in_years);
					printf("WA: %d\n", e->Work_accident);
					printf("PLY: %d\n", e->promotion_last_5years);
					printf("Job: %s\n", e->JobTitle);
					printf("Base: %f\n", e->BasePay);
					printf("OT: %f\n", e->OvertimePay);
					printf("Bene: %f\n", e->Benefit);
					printf("Status: %s\n", e->Status);
				}

			
			//printf("%s was not found in history file\n",emp->EmployeeName);
			// printf("We would make a request to the server at this point but that functionality is not completed\n");
			// if(!found2){
			// 	printf("%s was not found\n",e->EmployeeName);
			// }else{
			// 	//rewrite history file
			// 	temp = fopen("temp", "ab+");
			// 	for(int i = 0; i < 10; i++){
			// 		if(rewrite % 10 == i){
			// 			fwrite(result, sizeof(struct employee), 1, temp);
			// 		}
			// 		else{
			// 			fread(search, sizeof(struct employee), 1, fptr);
			// 			fwrite(search, sizeof(struct employee), 1, temp);
			// 		}
			// 		remove(fileName);
			// 		rename("temp",fileName);
			// 		fclose(temp);
			// 	}
			// }			
		//}
		//fclose(fptr); 
		
	//}

	fflush(stdout);
	close(clientSocket);
	exit(0);
}

