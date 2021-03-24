/*Group C
Cole Mitchell
cole.mitchell@okstate.edu
3-28-21
Description: testing the history file
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 4444
#include<stdio.h>
#include<string.h>
#include"structs.h"

int main(){
    while(1){
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
			int clientSocket, ret;
			struct sockaddr_in serverAddr;
			struct employee *emp;
			struct employee *e = &e;

			strcpy(e->name, "Dax");
			e->stars = 5;

			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			close(clientSocket);
			clientSocket = socket(AF_INET, SOCK_STREAM, 0);
			if(clientSocket < 0)
			{
				printf("ERROR IN CONNECTION");
				exit(1);
			}
			printf("Socket Created!\n");

			memset(&serverAddr, '\0', sizeof(serverAddr));
			serverAddr.sin_family = AF_INET;
			serverAddr.sin_port = htons(PORT);
			serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

			ret = connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
			if(ret < 0)
			{
				printf("ERROR IN CONNECTION2");
				exit(1);
			}
			printf("CONNECTED TO SERVER\n\n");


				printf("Sending name:\t%s\tstar:\t%d\n", e->name, e->stars);
				send(clientSocket, e, sizeof(struct employee), 0);

				if(recv(clientSocket, e, sizeof(struct employee), 0) < 0)
				{
					printf("ERROR recieving");
				}
				else
				{
					printf("Server: \t%s\t%d\n", e->name, e->stars);
				}

			close(clientSocket);
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
    }
    return 0;
}