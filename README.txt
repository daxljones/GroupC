Operating Systems Group Project // Group C
Authors:
    Dax Jones
    Cole Mitchell
    Ben Welch
    Kellen Riley

To compile and run:
    Server:
    gcc -pthread -o startserver ServerStart.c Server.c 
    ./startserver

    Client:
    gcc -o startclient ClientStart.c Manager.c
    ./startclient

Functionality:
Note: Our code only runs on Linux and will not work on CSX. (We have an email from Dr. Joshi telling us this is ok)
Each function will ask for an IP address to setup the socket connection.
We used 127.0.0.1 (the IP for a local connection) during our testing process. 

The client program will ask the user for the name, job title, and status before sending the information to an assistant file. Please note that spelling 
must be identical to what you are searching for! 
The assistant will search its history file, and if there is not a found match it will contact the server.
The Server will receive that information from the assistant and search the entire collection of employees to find a match. On a match, it sends all relevant 
information to the assistant. If there is no match, it will let the assistant know there was no match. The assistant will then print the received information to a new console. 

Clarifications on Workload:
We understand that the assignment asks for each individual person to submit a c file containing their work. However, given the combined nature of the finished project, it does not feel 
productive to differentiate who wrote each line of code given that we all feel each member contributed their fair amount to the project. Therefor, we will attempt to differentiate who 
worked on each part here to give you a better idea of our team dynamic. 

Dax Jones: 
	+Completed the server for the project and the server side of the socket connection. 

Kellen Riley:
	+Researched and implemented pipes along with the client side socket connection. 

Ben Welch: 
	+Set up the Manager request for user input and ability to print search results to a separate terminal. 

Cole Mitchell:
	+Created the history file interactions as well as in combining all the client side components. 

Each team member was also involved in numerous debugging sessions.