
/*
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
*/

#ifndef structs
#define structs
struct employee{
    int ID;
    char EmployeeName[50];
    char JobTitle[100];
    float BasePay;
    float OvertimePay;
    float Benefit;
    char Status[10];
    float satisfaction_level;
    int number_project;
    int average_monthly_hours;
    int time_spend_company_in_years;
    int Work_accident;
    int promotion_last_5years;
}__attribute__((packed))employee;
#endif
