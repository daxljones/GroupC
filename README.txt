Operating Systems Group Project // Group C
Authors:
    Dax Jones
    Cole Mitchell
    Ben Welch
    Kellen Riley

To compile and run:
    gcc -pthread -o startDemo groupCStart.c 
    ./startDemo

This program is currently in an unfinished state. Running it will demonstrate how the program
can run and the work done so far. There is currently no connection between the server and the
assistant.

Functionality:

The program will ask the user for input and send the input to an assistant file. The assistant
will search its history file, and if there is not a found match it will contact the server.
The Server will (does not yet) receive that information from the assistant and search the entire
collection of employees to find a match. On a match, it sends all relevant information to the assistant.
If there is no match, it will let the assistant know there was no match. The assistant will then print the received information to a new console (does not yet). 