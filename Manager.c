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

	
	
	char ch;
		
	// do{
	// 	//system("clear");
	// 	printf("Please enter the employee's name: ");
	// 	scanf("%s", emp -> EmployeeName);
	// 	fflush(stdin);

	// 	printf("Please enter the Employee's job title: ");
	// 	scanf("%s", emp -> JobTitle);

	// 	printf("Please Enter the Employee's status: ");
	// 	scanf("%s", emp -> Status);
	// 	fflush(stdin);
	
	// 	printf("Do you wish to enter another employee? Y/N: ");
	// 	scanf("%s", &ch);
	// 	fflush(stdin);
		
	// 	write(commpipe[1], emp, sizeof(*emp));
	// }while (ch == 'y' || ch == 'Y');

	//kill(pida, SIGKILL);


	strcpy(emp->EmployeeName, "JOSEPH DRISCOLL");
	strcpy(emp->JobTitle, "CAPTAIN, FIRE SUPPRESSION");
	strcpy(emp->Status, "PT");

	printf("SENDING NAME: %s\n", emp->EmployeeName);

	write(commpipe[1], emp, sizeof(struct employee));
	write(commpipe[1], emp, sizeof(struct employee));

	strcpy(emp->EmployeeName, "exit");

	write(commpipe[1], emp, sizeof(struct employee));

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
	//fp = fopen("Output.txt", "w+");
	//fprintf(fp, "Socket Created!\n");
	//system("gnome-terminal -- tail -f Output.txt");
	//fclose(fp);
	printf("Socket Created!\n");

	memset(&serverAddr, '\0', sizeof(serverAddr));
	serverAddr.sin_family = AF_INET;
	serverAddr.sin_port = htons(PORT);
	serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

	ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));


	while(1){
		//open output file type w+
		
		fp = fopen("Output.txt", "w+");

		//receives message from manager and creates struct from message
		read(commpipe[0], emp, sizeof(struct employee));

		if(strcmp(emp->EmployeeName, "exit") == 0)
		{
			send(clientSocket, emp, sizeof(struct employee), 0);
			close(clientSocket);
			fprintf(fp, "Assistant now leaving...");
			exit(0);
		}

		int found = 0;
		int found2 = 0;

		//opens history file	
		fptr = fopen(fileName, "ab+");
		fprintf(fp, "Searching for %s with title %s and status %s\n",emp->EmployeeName,emp->JobTitle,emp->Status);

		//checks if message is in the history file
		while(fread(search, sizeof(struct employee), 1, fptr)){
			fprintf(fp, "Name for search: %s status: %s\n", search->EmployeeName, search->Status);
			fprintf(fp, "===================================");
			if(!strcmp(emp->EmployeeName,s.EmployeeName) && !strcmp(emp->Status,s.Status) && !strcmp(emp->JobTitle,s.JobTitle)) {
				employee = s;
				fprintf(fp, "Employee found in history file\n");
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
    			fclose(temp);
    			fclose(fptr);
    			remove("./history");
				rename("./temp",fileName);
			}			
		}
		fclose(fptr); 	
		//call command to print output file 
		system("gnome-terminal -- tail -f output.txt");
		//fclose(output);
		fclose(fp);
	}

	//fflush(stdout);
	close(clientSocket);
	exit(0);
}

