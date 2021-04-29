#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h> 
#include <errno.h>
#include <arpa/inet.h>

int main(int argc, char const *argv[])
{
	char hostname[256];
	if(argc == 1){
		printf("Enter a hostname: ");
		scanf("%s", hostname);		

	}
	else if(argc == 2)
	{
		const char *hostname = argv[1];
	}
	else if(argc > 2)
	{
		printf("There are too many results! \n");
		exit(-1);
	}
	else if(argc < 2)
	{
		printf("I checked it, but found nothing.\n");
		exit(1);
	}

	struct hostent *gethost = gethostbyname(hostname);
	struct in_addr **IP;
	IP = (struct in_addr **)gethost -> h_addr_list;

	for(unsigned int i=0; IP[i] != NULL; i++){
		printf("IP address found: %s\n", inet_ntoa(*IP[i]));
	}

	return 0;
}
