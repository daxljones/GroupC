//Author: Dax Jones
//Use: Searches through multiple text files to determine if the predermined
//      employee is in the file, then gathers all related imformation pertaing to the employee


#include "structs.h"
#include "functions.h"
#include <pthread.h>


//findSatisfaction()
//Desc: This is a thread to gather all information related to a client given employee from
//the satisfaction file and store it into the employee package
//Parameters:
//void *f: f will be casted into an employee struct which hold client given info to find specific employee
//Return:
//void *: needed for thread but not used

void * findSatisfaction(void *f)
{
    FILE *fp = fopen("SatisfactionLevel.txt", "r"); //open satisfaction file 

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File2 not found!");
        exit(1);
    }

    struct employee *find = (struct employee *)f; //cast void pointer to employee struct pointer

    int i = 0, pos = 0, linePos = 0; // create position pointers and all needed arrays to store info from file
    char id[15];
    char line[200];
    char satisfactionLevel[10];
    char numOfProjects[10];
    char avgMonthlyHours[10];
    char timeWithCompany[10];
    char workAccidents[10];
    char promLastYear[10];

    while(fgets(line, 200, fp) != NULL) //read file until EOF
    {
        pos = 0; //set pointers to 0 to start new
        linePos = 0;

        memset(id, 0, 15); // clear array to prevent bugs
        while(line[linePos] != '\t') //gather ID
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(find->ID != atoi(id)){ continue; } //check to see if ID is equal to given ID, if not continue



        while(line[linePos] != '\t') //gather satisfaction level
        {
            satisfactionLevel[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->satisfaction_level = atof(satisfactionLevel); //set employee package satisfaction level to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') // gather number of projects
        {
            numOfProjects[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->number_project = atoi(numOfProjects); //set employee package num of projects to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') //gather avg monthly hours
        {
            avgMonthlyHours[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->average_monthly_hours = atoi(avgMonthlyHours); //set employee package avg monthly hours to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') //gather time with company
        {
            timeWithCompany[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->time_spend_company_in_years = atoi(timeWithCompany); //set employee package time spent with company to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') //gather work accidents
        {
            workAccidents[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->Work_accident = atoi(workAccidents); //set employee package work accidents to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\n') //gather promotions
        {
            promLastYear[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->promotion_last_5years = atoi(promLastYear); //set employee package promotions to gathered array
        linePos++;
        pos = 0;
        
        break; //since found, break
    }

    fclose(fp); //close file and return
    return NULL;
}

//findSalary()
//Desc: This is a thread to gather all information related to a client given employee from
//the salary file and store it into the employee package
//Parameters:
//void *f: f will be casted into an employee struct which hold client given info to find specific employee
//Return:
//void *: needed for thread but not used


void * findSalary(void *f)
{
    FILE *fp = fopen("Salaries.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }

    struct employee *find = (struct employee *)f; //cast void pointer to employee struct pointer

    int pos = 0, linePos = 0, i = 0; // create position pointers and all needed arrays to store info from file
    char id[15];
    char line[200];
    char basePay[20];
    char overtimePay[20];
    char benefits[20];

    while(fgets(line, 200, fp) != NULL) //read file until EOF
    {
        pos = 0; //set pointers to 0 to start new
        linePos = 0;

        memset(id, 0, 15); // clear array to prevent bugs
        while(line[linePos] != '\t') //gather ID
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(find->ID != atoi(id)) //check if the ID is the same as the given ID
        {
            continue; //continue to check next record
        }

        while(line[linePos] != '\t') //skips name
        {
            linePos++;
        }
        linePos++;

        while(line[linePos] != '\t') //gather base pay
        {
            basePay[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->BasePay = atof(basePay); //set employee package base pay to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') //gather overtime pay
        {
            overtimePay[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->OvertimePay = atof(overtimePay); //set employee package overtime pay to gathered array
        linePos++;
        pos = 0;

        while(line[linePos] != '\t') //gather benefits
        {
            benefits[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->Benefit = atof(benefits); //set employee package benefits to gathered array
        linePos++;

        break; //break
    }

    fclose(fp); //close file and return

    return NULL;
}



//Check details
//Desc: Used to check if all information given matches a found name. This is used incase there is an employee with
//the same name but the other information not matching.
//Parameters:
//struct employee *find: the struct that will contain client given information
//Return:
//int: returns 0 if the information does not match, 1 if it all matches


int checkDetails(struct employee *find)
{
    FILE *fp = fopen("Salaries.txt", "r"); //open file containg info to check

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }


    int pos = 0, linePos = 0; //create ints for position pointers
    char id[15]; //create all chars needed to read in info from file
    char line[200];
    char jobCheck[100];
    char statusCheck[10];

    while(fgets(line, 200, fp) != NULL) //take in lines until EOF
    {
        pos = 0; //start with pointers at 0
        linePos = 0;

        memset(id, 0, 15); //clear id to prevent bugs
        while(line[linePos] != '\t') //read until first tab break
        {
            id[pos] = line[linePos]; //copy over chars
            pos++;
            linePos++;
        }
        linePos++; //move past tab
        pos = 0;

        if(find->ID != atoi(id)) //if the ID is not the same, skip to next line
        {
            continue;
        }


        memset(jobCheck, 0, 100); //clear array to prevent bugs
        while(line[linePos] != '\t') //read until next break
        {
            jobCheck[pos] = line[linePos]; //copy over chars
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(strcmp(find->JobTitle, jobCheck) != 0) //check to see if the gathered temp array is the same as given info
        {
            fclose(fp); //close file and return false
            return 0; 
        }

        memset(statusCheck, 0, 10); //clear array to prevent bugs
        while(line[linePos + 2] != '\n') //move to end of line but keep 'linepos' 2 spots before(the start of status)
        {
            linePos++;
        }

        if(line[linePos] != (find->Status)[0]) //since status is either PT or FT, just compare first char
        {
            fclose(fp); //if not equal, close file and return false
            return 0;
        }
        else{
            break; //if the status and title are the same
        }

    }

    fclose(fp); //close file and return true

    return 1;
}




//The main part of the server.
//Use: This will be the main thread that will make socket connections with the client, take in all request, and the use
//threads to gather all related information and send it back to the client if it was found. If not found, it will
//convey that to the client

void server()
{
    int sockfd, ret; //int for server connections
    struct sockaddr_in serverAddr; //struct for socket information

    int newSocket; // socket for accepting
    struct sockaddr_in newAddr; // struct for new connection

    socklen_t addr_size; 


    char line[1000]; //chars to store file line and paticular parts of lines
    char id[15];
    char name[50];

    int pos = 0, linePos = 0, foundMatch = 0; // ints for keeping up with line pointers, pos in temporary arrays, and a psuedo bool


    struct employee curr;               //struct and pointer for recieving and packaging employee info
    struct employee *current = &curr;

    pthread_t salaryThread; // information for the 2 threads
    pthread_t satisfactionThread;

    sockfd =  socket(AF_INET, SOCK_STREAM, 0); //create socket(closed then opened again to ensure the socket is new)
    close(sockfd);
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0) //check for problem
    {
        printf("ERROR IN CONNECTION");
        exit(1);
    }
    printf("Server Socket is Created.\n");

    char ip[20]; //string for IP
    int i = 0;
    printf("Please enter the desired IP to create socket for: \n");
    fgets(ip, sizeof(ip), stdin); //Get IP

    while(ip[i] != '\n') //find location of '\n' that's tacked on to fgets input
    {
        i++;
    }
    ip[i] = ip[i + 1]; // replace '\n' with null terminator

    memset(&serverAddr, '\0', sizeof(serverAddr)); //Fill socket info struct with required info
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr(ip);

    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)); //bind socket for connections
    if(ret < 0)
    {
        printf("ERROR IN BINDING");
        exit(1);
    }
    printf("Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0) //listen for client connection
    {
        printf("Listening..\n");
    }
    else
        printf(("Error in binding2\n"));


    newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size); // accept clients request for connection
    if(newSocket < 0)
        exit(1);
    
    printf("Connection Accepted from %s:%d\n\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port)); //print out client's connection info

    while(1)
    {
        pos = 0; //set pointer ints and bool to 0
        linePos = 0;
        foundMatch = 0;

        recv(newSocket, current, sizeof(struct employee), 0); //recieve info from client

        printf("Got Name: %s, Title: %s, Status: %s\n", current->EmployeeName, current->JobTitle, current->Status); //Display information recieved

        if(strcmp(current -> EmployeeName, "exit") == 0) //check to see if clients want to exit
        {
            close(sockfd); //close sockets and leave
            close(newSocket);
            break;
        }

        FILE *fp = fopen("ID_Name.txt", "r"); //open file to determine id based on name

        if(fp == NULL) //Check to see if file successfully opened
        {
            printf("Error: File not found!");
            exit(1);
        }


        while(fgets(line, 100, fp) != NULL) //read in line from file until EOF
        {
            while(line[linePos] != '\t') //read until first seperation
            {
                id[pos] = line[linePos]; //copy chars over one by one
                pos++;
                linePos++;
            }
            current->ID = atoi(id); //convert to int and store in struct
            pos = 0;
            linePos++; //move pointer past tab

            while(line[linePos] != '\n') //read name until line end
            {
                name[pos] = line[linePos]; //copy over chars
                pos++;
                linePos++;
            }

            if(strcmp(current->EmployeeName, name) == 0) // check to see if the name matches to the client provided name
            {
                
                if(checkDetails(current) != 0) //check to see if status and job title are the same as client given info in case name is the same as anothers
                {
                    pthread_create(&salaryThread, NULL, findSalary, current); //call thread to gather salary info
                    pthread_create(&satisfactionThread, NULL, findSatisfaction, current); //call thread to gather satisfaction info
                    pthread_join(salaryThread, NULL); //wait until threads return
                    pthread_join(satisfactionThread, NULL);
                    foundMatch = 1; // match = true
                    memset(name, 0, 50); //reset name array for clean start
                    pos = 0; //reset pointers and break
                    linePos = 0;
                    break;
                }
            }

            memset(name, 0, 50); //reset name to prevent bugs
            pos = 0;
            linePos = 0;
        }

        if(foundMatch) //check if the match was found
        {
            send(newSocket, current, sizeof(struct employee), 0); //send all info back to client
        }
        else
        {
            strcpy(current->EmployeeName, "No Match"); //no match so send back to client with the name "no match"
            send(newSocket, current, sizeof(struct employee), 0);
        }

        fclose(fp); //close file
    }

    printf("Server closing.. GoodBye!"); //server closing message and exit program
    exit(0);
}
