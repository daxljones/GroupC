#include <stdio.h>
#include <stdlib.h>
struct Employee
{
	int ID;
	char name[20];
	char title[20];
	double basePay;
	double overtimePay;
	char benfit[20];
	char status[20];
	int satisfactionLevel;
	int numberProject;
	int averageMonthlyHours;
	int timeSpendCompanyInYears;
	int workAccident;
	int promationLast5Years;
};

int main ()
{
	char ch;
	do
	{
		system("clear");

		struct Employee Emp2;

		printf("Please enter the employee's name: ");
		scanf("%s", Emp2.name);

		printf("Please enter the Employee's job title: ");
		scanf("%s", Emp2.title);

		printf("Please Enter the Employee's status: ");
		scanf("%s", Emp2.status);

		printf("Do you wish to enter another employee? Y/N: ");
		scanf("%s", &ch);
	}
	while (ch == 'y' || ch == 'Y');
}