/*Group C
Cole Mitchell
cole.mitchell@okstate.edu
3-28-21
Description: holds all the definitions for the 
structures used in the program
*/
#ifndef assignment02_Mitchell_Cole_structDefinitions
#define assignment02_Mitchell_Cole_structDefinitions
//stores all the information for an employee
//to start these will all be strings but we can change that as necesary
struct employee{
    char ID[10];
    char EmployeeName[50];
    char JobTitle[50];
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


#endif