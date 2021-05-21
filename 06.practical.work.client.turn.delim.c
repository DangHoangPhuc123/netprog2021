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
    int sockfd, test;
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
    
    if (gethost == NULL) {
        printf("The host not found\n");
        exit(1);
    }
    IP = (struct in_addr **)gethost -> h_addr_list;

    for(unsigned int i=0; IP[i] != NULL; i++){
        printf("IP address found: %s\n", inet_ntoa(*IP[i]));
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf("Something wrong cannot creating socket\n");
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

    while (1) {
        bzero(buffer, sizeof(buffer));
        fgets(buffer, sizeof(buffer), stdin);
        test = write(sockfd, buffer, strlen(buffer));
        if (test >= 0)
            printf("can write to socket\n");
        else
            printf("can't write to socket\n");
        bzero(buffer, sizeof(buffer));
        test = read(sockfd, buffer ,sizeof(buffer));
        if (test >= 0)
            printf("can read from socket\n");
        else
            printf("cannot read from socket\n");
        printf("finish  %s\n", buffer);
    }
    return 0;
}

