#include <stdio.h> 
#include <stdlib.h>
#include <string.h>

void findSatisfaction(char *findID)
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
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }

        if(atoi(id) == atoi(findID))
        {
            printf("%s\n", line);
            break;
        }

        pos = 0;
        linePos = 0;
    }

}

void findSalary(char *findID)
{
    printf("CALLED2: %s", findID);

    FILE *fp = fopen("Salaries.txt", "r"); //open file state.txt

    if(fp == NULL) //Check to see if file successfully opened
    {
        printf("Error: File1 not found!");
        exit(1);
    }

    int pos = 0, linePos = 0;
    char id[15];
    char line[200];

    while(fgets(line, 200, fp) != NULL)
    {
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }

        if(atoi(id) == atoi(findID))
        {
            printf("%s\n", line);
            break;
        }

        pos = 0;
        linePos = 0;
    }
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
    char choice[] = "ALBERT PARDINI";
    char name[50];


    



    int i = 0, pos = 0, linePos = 0;

    while(fgets(line, 100, fp) != NULL)
    {
        while(line[linePos] != '\t')
        {
            id[pos] = line[linePos];
            pos++;
            linePos++;
        }
        pos = 0;
        linePos++;

        while(line[linePos] != '\n')
        {
            name[pos] = line[linePos];
            pos++;
            linePos++;
        }


        if(strcmp(name, choice) == 0)
        {
            printf("Found! ID: %s Name: %s\n", id, name);
            findSatisfaction(id);
            findSalary(id);
        }

        pos = 0;
        linePos = 0;
    }


    

    



}
