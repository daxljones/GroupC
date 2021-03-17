#include <stdio.h>
#include <stdlib.h>


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

int main ()
{
	char ch;
	do
	{
		system("clear");

		struct employee Emp2;

		printf("Please enter the employee's name: ");
		scanf("%s", Emp2.EmployeeName);

		printf("Please enter the Employee's job title: ");
		scanf("%s", Emp2.JobTitle);

		printf("Please Enter the Employee's status: ");
		scanf("%s", Emp2.Status);

		printf("Do you wish to enter another employee? Y/N: ");
		scanf("%s", &ch);
	}
	while (ch == 'y' || ch == 'Y');
}