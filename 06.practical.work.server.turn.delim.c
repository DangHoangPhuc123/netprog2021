#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char **argv) {
    int sockfd, clen, clientfd, test;
    struct sockaddr_in saddr, caddr;
    unsigned short port = 8784;

    if ((sockfd=socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        printf ("Error creating socket\n");
        return -1;
    }

    memset(&saddr, 0, sizeof(saddr));
    saddr.sin_family = AF_INET;
    saddr.sin_addr.s_addr = htonl(INADDR_ANY);
    saddr.sin_port = htons(port);

    if ((bind(sockfd, (struct sockaddr *) &saddr, sizeof(saddr)) < 0)) {
        printf("Error binding\n");
        return -1;
    }

    if (listen(sockfd, 5) < 0) {
        printf("Error listening\n");
        return -1;
    }

    clen =sizeof(caddr);

    if ((clientfd=accept(sockfd, (struct sockaddr *) &caddr, &clen)) < 0) {
        printf("Error accepting connection\n");
        return -1;
    }

    printf("There's a client want to connect!\n");
    while (1) {
        printf("Please enter the message: ");
        bzero(buffer,256);
        fgets(buffer,255,stdin);
        test = write(sockfd,buffer,strlen(buffer));
        if (test >= 0)
            printf("can write to socket\n");
        else
            printf("can't write to socket\n");
        bzero(buffer,256);
        test = read(sockfd,buffer,255);
        if (test >= 0)
            printf("can read from socket\n");
        else
            printf("cannot read from socket\n");
        printf("%s\n",buffer);
    }
    return 0;
}
