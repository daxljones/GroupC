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
    printf("Server Demo running...\n\nLooking for 'JOSEPH DRISCOLL', 'CAPTAIN, FIRE SUPPRESSION', 'PT'...\n\n");
    
    FILE *fp = fopen("ID_Name.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File not found!");
        exit(1);
    }

    char line[1000];
    char id[15];
    char choice[] = "JOSEPH DRISCOLL";
    char name[50];


    struct employee curr;
    struct employee *current = &curr;

    strcpy(current->JobTitle, "CAPTAIN, FIRE SUPPRESSION");
    strcpy(current->Status, "PT");

    pthread_t salaryThread;
    pthread_t satisfactionThread;

    int i = 0, pos = 0, linePos = 0, foundMatch = 0;

    while(fgets(line, 100, fp) != NULL)
    {
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        current->ID = atoi(id);
        pos = 0;
        linePos++;

        while(line[linePos] != '\n')
        {
            (current -> EmployeeName)[pos] = line[linePos];
            pos++;
            linePos++;
        }


        if(strcmp(current->EmployeeName, choice) == 0)
        {
            //printf("Found! ID: %s Name: %s\n", current->ID, current->EmployeeName);
            
            if(checkDetails(current) != 0)
            {
                pthread_create(&salaryThread, NULL, findSalary, current);
                pthread_create(&satisfactionThread, NULL, findSatisfaction, current);
                pthread_join(salaryThread, NULL);
                pthread_join(satisfactionThread, NULL);
                foundMatch = 1;
                break;
            }
        }

        memset(current->EmployeeName, 0, 50);
        pos = 0;
        linePos = 0;
    }

    if(foundMatch)
    {
        printf("Found!\n");
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
    }
    else
        printf("No Match!\n");

}
