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
        char sever[1000];
        memset(sever, 0, 1000);
        printf("Client> ");
        fgets(sever, 200, stdin);
        write(sockfd, sever, strlen(sever));
        read(sockfd, sever, 1000);
        sever[strlen(sever)] = 0;
        printf("Server says: %s\n", sever);
    }
    return 0;
}
