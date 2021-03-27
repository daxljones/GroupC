#include "functions.h"
#include "structs.h"


void assistant(int *);


void Manager ()
{	
	pid_t pida;
	
	struct employee e;
	struct employee *emp = &e;
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
		
		assistant(commpipe);
		
	}


	int i = 0;
		
	while(1)
	{
		system("clear");
		printf("Please enter the employee's name (enter 'exit' to leave): \n");
		fgets(emp->EmployeeName, sizeof(emp->EmployeeName), stdin);

		while(emp->EmployeeName[i] != '\n')
		{
			i++;
		}

		emp->EmployeeName[i] = emp->EmployeeName[i + 1];
		i = 0;


		if(strcmp(emp->EmployeeName, "exit") == 0)
		{
			write(commpipe[1], emp, sizeof(*emp));
			break;
		}


		printf("Please enter the Employee's job title: \n");
		fgets(emp->JobTitle, sizeof(emp->JobTitle), stdin);

		while(emp->JobTitle[i] != '\n')
		{
			i++;
		}
		emp->JobTitle[i] = emp->JobTitle[i + 1];
		i = 0;

		printf("Please Enter the Employee's status: \n");
		fgets(emp->Status, sizeof(emp->Status), stdin);

		while(emp->Status[i] != '\n')
		{
			i++;
		}
		emp->Status[i] = emp->Status[i + 1];
		i = 0;

		
		write(commpipe[1], emp, sizeof(*emp));
	}


	wait(NULL);
}


void assistant(int *commpipe){
	
	//sets up pipe to read
	struct employee* emp = malloc(sizeof(*emp));
	int rv;
	//int commpipe[2]; //This holds the fd for the input & output of the pipe 
	struct employee s;
    struct employee *search = &s;

	//sets up socket connection
	int clientSocket, ret;
	struct sockaddr_in serverAddr;
	struct employee employee;
	struct employee *e = &employee;

	FILE *fptr, *temp, *fp;
	char fileName[] = "history";
	int rewrite = 0;
		

	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	close(clientSocket);
	clientSocket = socket(AF_INET, SOCK_STREAM, 0);
	if(clientSocket < 0)
	{
		printf("ERROR IN CONNECTION");
		exit(1);
	}
	// fp = fopen("Output.txt", "w+");
	// fprintf(fp, "Socket Created!\n");
	// system("gnome-terminal -- tail -f Output.txt");
	// fclose(fp);
	printf("Socket Created!\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));


	while(1){
		//receives message from manager and creates struct from message
		read(commpipe[0], emp, sizeof(struct employee));

		if(strcmp(emp->EmployeeName, "exit") == 0)
		{
			send(clientSocket, emp, sizeof(struct employee), 0);
			close(clientSocket);
			//fprintf(fp, "Assistant now leaving...");
			exit(0);
		}
		
		//open output file type w+
		//char outputName[30];
    	//snprintf(outputName,(int)sizeof(outputName),"output%d",rewrite);
		fp = fopen("Output.txt", "w+");

		int found = 0;
		int found2 = 0;

		//opens history file	
		fptr = fopen(fileName, "ab+");
		fprintf(fp, "Searching for %s with title %s and status %s\n",emp->EmployeeName,emp->JobTitle,emp->Status);

		//checks if message is in the history file
		while(fread(search, sizeof(struct employee), 1, fptr)){
			//fprintf(fp, "Name for search: %s status: %s\n", search->EmployeeName, search->Status);
			if(!strcmp(emp->EmployeeName,s.EmployeeName) && !strcmp(emp->Status,s.Status) && !strcmp(emp->JobTitle,s.JobTitle)) {
				//employee = s;
				fprintf(fp, "Employee found in history file\n");
				fprintf(fp, "ID: %d\n", s.ID);
				fprintf(fp, "Name: %s\n", s.EmployeeName);
				fprintf(fp, "SL: %f\n", s.satisfaction_level);
				fprintf(fp, "NP: %d\n", s.number_project);
				fprintf(fp, "AVGH: %d\n", s.average_monthly_hours);
				fprintf(fp, "TSCY: %d\n", s.time_spend_company_in_years);
				fprintf(fp, "WA: %d\n", s.Work_accident);
				fprintf(fp, "PLY: %d\n", s.promotion_last_5years);
				fprintf(fp, "Job: %s\n", s.JobTitle);
				fprintf(fp, "Base: %f\n", s.BasePay);
				fprintf(fp, "OT: %f\n", s.OvertimePay);
				fprintf(fp, "Bene: %f\n", s.Benefit);
				fprintf(fp, "Status: %s\n", s.Status);
				found = 1;
				break;
			}
		}
		fclose(fptr);
		
		//if not found in history file, asks server for information
		if(!found){
			//make request to server and receive result		
			if(ret < 0)
			{
				fprintf(fp, "ERROR IN CONNECTION2");
				exit(1);
			}
			fprintf(fp, "CONNECTED TO SERVER\n\n");


			fprintf(fp, "Sending EmployeeName:\t%s\n", e->EmployeeName);
			send(clientSocket, emp, sizeof(struct employee), 0);

			if(recv(clientSocket, emp, sizeof(struct employee), 0) < 0)
			{
				fprintf(fp, "ERROR recieving");
			}
			else
			{
				fprintf(fp, "Found! Now sending...\n");
				fprintf(fp, "ID: %d\n", emp->ID);
				fprintf(fp, "Name: %s\n", emp->EmployeeName);
				fprintf(fp, "SL: %f\n", emp->satisfaction_level);
				fprintf(fp, "NP: %d\n", emp->number_project);
				fprintf(fp, "AVGH: %d\n", emp->average_monthly_hours);
				fprintf(fp, "TSCY: %d\n", emp->time_spend_company_in_years);
				fprintf(fp, "WA: %d\n", emp->Work_accident);
				fprintf(fp, "PLY: %d\n", emp->promotion_last_5years);
				fprintf(fp, "Job: %s\n", emp->JobTitle);
				fprintf(fp, "Base: %f\n", emp->BasePay);
				fprintf(fp, "OT: %f\n", emp->OvertimePay);
				fprintf(fp, "Bene: %f\n", emp->Benefit);
				fprintf(fp, "Status: %s\n", emp->Status);
				found2 = 1;
			}

			if(!found2){
				fprintf(fp, "%s was not found\n",emp->EmployeeName);
			}else{
				//rewrite history file
				fptr = fopen(fileName, "ab+");
				temp = fopen("temp", "wb");
				for(int i = 0; i < 10; i++){
					if(rewrite % 10 == i){
						fwrite(emp, sizeof(struct employee), 1, temp);
					}
					else{
						fread(search, sizeof(struct employee), 1, fptr);
						fwrite(search, sizeof(struct employee), 1, temp);
					}
    			}
				rewrite++;
    			fclose(temp);
    			fclose(fptr);
    			remove("./history");
				rename("./temp",fileName);
			}			
		}	
		//call command to print output file 
		fclose(fp);
		system("gnome-terminal -- tail -f Output.txt -n 20");		
		remove("./Output.txt");

		// fp = fopen("output", "r");
		// char line[100];
		// while(fread(line, sizeof(line), 1, fp)){
		// 	printf("%s\n",line);
		// }
		// fclose(fp);
	}

	//fflush(stdout);
	close(clientSocket);
	exit(0);
}
