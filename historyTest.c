#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include "structs.h"

int main(){
    struct employee e;
	struct employee *emp = &e;
    struct employee s;
    struct employee *search = &s;

    strcpy(emp->EmployeeName, "JOSEPH DRISCOLL");
	strcpy(emp->JobTitle, "CAPTAIN, FIRE SUPPRESSION");
	strcpy(emp->Status, "PT");

    FILE *fptr, *temp;
	char fileName[] = "history";
	int rewrite = 0;
    int found = 0;

    //opens history file	
	fptr = fopen(fileName, "ab+");
	printf("Searching for %s with title %s and status %s\n",emp->EmployeeName,emp->JobTitle,emp->Status);

    fwrite(emp, sizeof(struct employee), 1, fptr);
    fclose(fptr); 

    fptr = fopen(fileName, "ab+");
    fread(search, sizeof(struct employee), 1, fptr);
    printf("Name for search: %s status: %s\n", s.EmployeeName, s.Status);
    fclose(fptr);

	// //checks if message is in the history file
	// while(fread(search, sizeof(struct employee), 1, fptr)){
	// 	printf("Name for search: %s status: %s\n", search->EmployeeName, search->Status);
	// 	printf("===================================");
	// 	if(!strcmp(emp->EmployeeName,search->EmployeeName) && !strcmp(emp->Status,search->Status) && !strcmp(emp->JobTitle,search->JobTitle)) {
	// 		emp = search;
	// 		printf("Employee found in history file\n");
	// 		found = 1;
	// 		break;
	// 	}
	// }
	// fclose(fptr);

    // //rewrite history file
	// fptr = fopen(fileName, "ab+");
	// temp = fopen("temp", "wb");
	// for(int i = 0; i < 10; i++){
	// 	if(rewrite % 10 == i){
	// 		fwrite(emp, sizeof(struct employee), 1, temp);
	// 	}
	// 	else{
	// 		fread(search, sizeof(struct employee), 1, fptr);
	// 		fwrite(search, sizeof(struct employee), 1, temp);
	// 	}
	// 	remove(fileName);
	// 	rename("temp",fileName);
	// 	fclose(temp);
	// }
    // fclose(fptr); 
}