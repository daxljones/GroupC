//Author: Dax Jones
//Use: Searches through multiple text files to determine if the predermined
//      employee is in the file, then gathers all related imformation pertaing to the employee


#include "structs.h"
#include "functions.h"
#include <pthread.h>


void * findSatisfaction(void *f)
{
    FILE *fp = fopen("SatisfactionLevel.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File2 not found!");
        exit(1);
    }

    struct employee *find = (struct employee *)f;

    int i = 0, pos = 0, linePos = 0;
    char id[15];
    char line[200];
    char satisfactionLevel[10];
    char numOfProjects[10];
    char avgMonthlyHours[10];
    char timeWithCompany[10];
    char workAccidents[10];
    char promLastYear[10];

    while(fgets(line, 200, fp) != NULL)
    {
        pos = 0;
        linePos = 0;

        memset(id, 0, 15);
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(find->ID != atoi(id)){ continue; }



        while(line[linePos] != '\t')
        {
            satisfactionLevel[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->satisfaction_level = atof(satisfactionLevel);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            numOfProjects[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->number_project = atoi(numOfProjects);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            avgMonthlyHours[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->average_monthly_hours = atoi(avgMonthlyHours);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            timeWithCompany[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->time_spend_company_in_years = atoi(timeWithCompany);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            workAccidents[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->Work_accident = atoi(workAccidents);
        linePos++;
        pos = 0;

        while(line[linePos] != '\n')
        {
            promLastYear[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->promotion_last_5years = atoi(promLastYear);
        linePos++;
        pos = 0;
        
        break;
    }

    fclose(fp);
    return NULL;
}



void * findSalary(void *f)
{
    FILE *fp = fopen("Salaries.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }

    struct employee *find = (struct employee *)f;

    int pos = 0, linePos = 0, i = 0;
    char id[15];
    char line[200];
    char basePay[20];
    char overtimePay[20];
    char benefits[20];

    while(fgets(line, 200, fp) != NULL)
    {
        pos = 0;
        linePos = 0;

        memset(id, 0, 15);
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(find->ID != atoi(id))
        {
            continue;
        }

        while(line[linePos] != '\t')
        {
            linePos++;
        }
        linePos++;

        while(line[linePos] != '\t')
        {
            basePay[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->BasePay = atof(basePay);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            overtimePay[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->OvertimePay = atof(overtimePay);
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            benefits[pos] = line[linePos];
            pos++;
            linePos++;
        }
        find->Benefit = atof(benefits);
        linePos++;

        break;
    }

    fclose(fp);

    return NULL;
}






int checkDetails(struct employee *find)
{
    FILE *fp = fopen("Salaries.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }


    int pos = 0, linePos = 0;
    char id[15];
    char line[200];
    char jobCheck[100];
    char statusCheck[10];

    while(fgets(line, 200, fp) != NULL)
    {
        pos = 0;
        linePos = 0;

        memset(id, 0, 15);
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(find->ID != atoi(id))
        {
            //printf("have: %d need: %d", atoi(id), find->ID);
            continue;
        }


        memset(jobCheck, 0, 100);
        while(line[linePos] != '\t')
        {
            jobCheck[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        if(strcmp(find->JobTitle, jobCheck) != 0)
        {
            memset(jobCheck, 0, 100);
            fclose(fp);
            return 0; 
        }

        memset(statusCheck, 0, 10);
        while(line[linePos + 2] != '\n')
        {
            linePos++;
        }

        if(line[linePos] != (find->Status)[0])
        {
            fclose(fp);
            return 0;
        }
    }

    fclose(fp);

    return 1;
}







void server()
{
    //printf("Server Demo running...\n\nLooking for 'JOSEPH DRISCOLL', 'CAPTAIN, FIRE SUPPRESSION', 'PT'...\n\n");
    
    FILE *fp = fopen("ID_Name.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File not found!");
        exit(1);
    }

    int sockfd, ret;
    struct sockaddr_in serverAddr;

    int newSocket;
    struct sockaddr_in newAddr;

    socklen_t addr_size;


    char line[1000];
    char id[15];
    char name[50];

    int i = 0, pos = 0, linePos = 0, foundMatch = 0;


    struct employee curr;
    struct employee *current = &curr;

    pthread_t salaryThread;
    pthread_t satisfactionThread;

    sockfd =  socket(AF_INET, SOCK_STREAM, 0);
    close(sockfd);
    sockfd =  socket(AF_INET, SOCK_STREAM, 0);

    if(sockfd < 0)
    {
        printf("ERROR IN CONNECTION");
        exit(1);
    }
    printf("Server Socket is Created.\n");

    memset(&serverAddr, '\0', sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    ret = bind(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
    if(ret < 0)
    {
        printf("ERROR IN BINDING");
        exit(1);
    }
    printf("Bind to port %d\n", 4444);

    if(listen(sockfd, 10) == 0)
    {
        printf("Listening..\n");
    }
    else
        printf(("Error in binding2\n"));


    newSocket = accept(sockfd, (struct sockaddr *)&newAddr, &addr_size);
    if(newSocket < 0)
        exit(1);
    
    printf("Connection Accepted from %s:%d\n\n", inet_ntoa(newAddr.sin_addr), ntohs(newAddr.sin_port));

    while(1)
    {
        i = 0;
        pos = 0;
        linePos = 0;
        foundMatch = 0;

        recv(newSocket, current, sizeof(struct employee), 0);

        printf("Got Name: %s, Title: %s, Status: %s\n", current->EmployeeName, current->JobTitle, current->Status);

        if(strcmp(current -> EmployeeName, "exit") == 0)
        {
            close(sockfd);
            close(newSocket);
            break;
        }

        FILE *fp = fopen("ID_Name.txt", "r"); //open file state.txt

        if(fp == NULL) //Check to see if file successfully opened
        {
            printf("Error: File not found!");
            exit(1);
        }


        while(fgets(line, 100, fp) != NULL)
        {
            while(line[linePos] != '\t')
            {
                id[pos] = line[linePos];
                pos++;
                linePos++;
            }
            current->ID = atoi(id);
            //printf("looking at id: %d", current->ID);
            pos = 0;
            linePos++;

            while(line[linePos] != '\n')
            {
                name[pos] = line[linePos];
                pos++;
                linePos++;
            }

            if(strcmp(current->EmployeeName, name) == 0)
            {
                
                if(checkDetails(current) != 0)
                {
                    pthread_create(&salaryThread, NULL, findSalary, current);
                    pthread_create(&satisfactionThread, NULL, findSatisfaction, current);
                    pthread_join(salaryThread, NULL);
                    pthread_join(satisfactionThread, NULL);
                    foundMatch = 1;
                    memset(name, 0, 50);
                    pos = 0;
                    linePos = 0;
                    break;
                }
            }

            memset(name, 0, 50);
            pos = 0;
            linePos = 0;
        }

        if(foundMatch)
        {
            printf("Found! Now sending...\n");
            printf("ID: %d\n", current->ID);
            printf("Name: %s\n", current->EmployeeName);
            printf("SL: %f\n", current->satisfaction_level);
            printf("NP: %d\n", current->number_project);
            printf("AVGH: %d\n", current->average_monthly_hours);
            printf("TSCY: %d\n", current->time_spend_company_in_years);
            printf("WA: %d\n", current->Work_accident);
            printf("PLY: %d\n", current->promotion_last_5years);
            printf("Job: %s\n", current->JobTitle);
            printf("Base: %f\n", current->BasePay);
            printf("OT: %f\n", current->OvertimePay);
            printf("Bene: %f\n", current->Benefit);
            printf("Status: %s\n", current->Status);

            send(newSocket, current, sizeof(struct employee), 0);
        }
        else
        {
            strcpy(current->EmployeeName, "No Match");
            send(newSocket, current, sizeof(struct employee), 0);
        }

        fclose(fp);
    }

    printf("Server closing.. GoodBye!");
    exit(0);
}
