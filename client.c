#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include "clientutils.h"
#define portno 8999

int main()
{
	struct sockaddr_in serv;
	int sd;
	char buf[80];
	
	sd=socket(AF_INET,SOCK_STREAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=INADDR_ANY;
	serv.sin_port=htons(portno);
	
	//ek .h file mein karo
	//yahan se menu mein sd pass kar
	
	connect(sd, (void *)(&serv),sizeof(serv));
	
	mainMenu(sd);  // inside clientutils.h
	
	
	close(sd);

	return(0);



}
