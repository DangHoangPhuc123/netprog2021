#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

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

    int sockfd;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Something wrong cannot creating socket\n");
        exit(1);
    }

    if ((gethost = gethostbyname("ict.usth.edu.vn")) == NULL) {
        printf("The host not found\n");
        exit(1);
    }

    struct sockaddr_in saddr;
    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    memcpy((char *) &saddr.sin_addr.s_addr, gethost->h_addr_list[0], gethost->h_length);
    saddr.sin_port = htons(8784);

    if (connect(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0) {
        printf("We cannot connect\n");
        exit(1);
    }
    printf("Error accepting connection\n");
    while (1) {
        char sever[1000];
        memset(sever, 0, 1000);
        printf("Client> ");
        fgets(sever, 200, stdin);
        write(sockfd, sever, strlen(s));
        read(sockfd, sever, 1000);
        s[strlen(sever)] = 0;
        printf("Server says: %s\n", sever);
    }
    return 0;
}

