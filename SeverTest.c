#include "structs.h"
#include "functions.h"



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

        if(strcmp(id, find->ID)){ continue; }



        while(line[linePos] != '\t')
        {
            (find->satisfaction_level)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->number_project)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->average_monthly_hours)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->time_spend_company_in_years)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->Work_accident)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\n')
        {
            (find->promotion_last_5years)[pos] = line[linePos];
            pos++;
            linePos++;
        }
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

        if(strcmp(id, find->ID))
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
            (find->BasePay)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->OvertimePay)[pos] = line[linePos];
            pos++;
            linePos++;
        }
        linePos++;
        pos = 0;

        while(line[linePos] != '\t')
        {
            (find->Benefit)[pos] = line[linePos];
            pos++;
            linePos++;
        }
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

        if(strcmp(id, find->ID))
        {
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
            (current -> ID)[pos] = line[linePos];
            pos++;
            linePos++;
        }
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
        printf("ID: %s\n", current->ID);
        printf("Name: %s\n", current->EmployeeName);
        printf("SL: %s\n", current->satisfaction_level);
        printf("NP: %d\n", atoi(current->number_project));
        printf("AVGH: %d\n", atoi(current->average_monthly_hours));
        printf("TSCY: %s\n", current->time_spend_company_in_years);
        printf("WA: %s\n", current->Work_accident);
        printf("PLY: %s\n", current->promotion_last_5years);
        printf("Job: %s\n", current->JobTitle);
        printf("Base: %s\n", current->BasePay);
        printf("OT: %s\n", current->OvertimePay);
        printf("Bene: %s\n", current->Benefit);
        printf("Status: %s\n", current->Status);
    }
    else
        printf("No Match!\n");

}
