/*Group C
Cole Mitchell
cole.mitchell@okstate.edu
3-28-21
Description: testing the history file
*/

#include<stdio.h>
#include<string.h>
#include"assignment02_groupC_structDefinitions.h"

int main(){
    //receives message from manager and creates struct from message
    struct employee *search,*result;
    char name[] = "Anthony";
    int found = 0;
    int rewrite = 0;

    //opens history file
    FILE *fptr, *temp;
    char fileName[] = "history";
    fptr = fopen(fileName, "ab+");

    //checks if message is in the history file
    while(fread(search, sizeof(struct employee), 1, fptr)){
        if(!strcmp(name,search->EmployeeName)){
            result = search;
            found = 1;
            break;
        }
    }

    if(!found){
        //make request to server and receive result 

        //rewrite history file
        temp = fopen("temp", "ab+");
        for(int i = 0; i < 10; i++){
        if(rewrite % 10 == i){
            fwrite(result, sizeof(struct employee), 1, temp);
        }
        else{
            fread(search, sizeof(struct employee), 1, fptr);
            fwrite(search, sizeof(struct employee), 1, temp);
        }
        remove(fileName);
        rename("temp",fileName);
        fclose(temp);
    }
    }


    fclose(fptr); 
    return 0;
}