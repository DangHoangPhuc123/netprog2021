#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main (int argc, char **argv) {
    int sockfd, clen, clientfd;
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
        n = write(sockfd,buffer,strlen(buffer));
        if (n < 0)
            printf("cannot write to socket");
        bzero(buffer,256);
        n = read(sockfd,buffer,255);
        if (n < 0)
            printf("cannot read from socket");
        printf("%s\n",buffer);
        
        if (strcmp(buffer, "/quit") == 0) {
            printf("disconnected server\n");
            shutdown(sockfd, SHUT_RDWR);
            close(sockfd);
            return 0;
        }
    }
    return 0;
}

