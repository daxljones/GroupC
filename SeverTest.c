#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

struct employee{
    char ID[15];
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
};



void findSatisfaction(struct employee *find)
{
    FILE *fp = fopen("SatisfactionLevel.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File2 not found!");
        exit(1);
    }

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

}



void findSalary(struct employee *find)
{
    FILE *fp = fopen("Salaries.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }


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
            return 0; 
        }

        memset(statusCheck, 0, 10);
        while(line[linePos + 2] != '\n')
        {
            linePos++;
        }

        if(line[linePos] != (find->Status)[0])
        {
            printf("This doesnt work");
            return 0;
        }
    }

    return 1;
}



int main()
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
                findSatisfaction(current);
                findSalary(current);
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
