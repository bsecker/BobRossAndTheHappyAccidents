#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "E101.h"
#include "constants.h"



int open_gate(){
	//attempt to connect to server
	char server[15] = "130.195.6.196";
	connect_to_server(server, 1024) ;
	//Sending message(please) to server	
	printf("password %s \n", SERVER_PASSWORD);
	send_to_server(SERVER_PASSWORD);
	//receiving password from server first declares a char[] to store
	char message[24];
	receive_from_server(message);
	//print the message recieved
	printf("Servers Message: %s\n", message);
	//send message back to server and open gate
	send_to_server(message);
	printf("Gate should be open\n");
return 0;}


