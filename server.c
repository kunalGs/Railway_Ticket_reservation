#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include "serverutils.h"
#define portno 8999



int main()
{
	struct sockaddr_in serv, cli;
	int sd,sz,nsd;
	char buf[80];

	sd=socket(AF_INET,SOCK_STREAM,0);
	
	serv.sin_family=AF_INET;
	serv.sin_addr.s_addr=INADDR_ANY;
	serv.sin_port=htons(portno);
	
	
	
	if(bind(sd, (void *)(&serv),sizeof(serv))<0){
		printf("Error at bind function call \n");
	}
	
	listen(sd,5);
	sz=sizeof(cli);
	while(1)
	{
		nsd=accept(sd,(struct sockaddr*)(&cli),&sz);
		if(fork()==0)
		{
			close(sd);  // no use of the raw socket dsescriptor 
			
			mainMenu(nsd);
			exit(0);
		}
		else
		{   
		 printf(" error code : 503 (means the server is unavailable......) "); 
		 close(nsd);
			
	        }
	}
	
	close(nsd); // actual socket descriptor returned by accept function call.
	close(sd);  // closing : raw socket descriptor 
	
	
	return 0;
}
