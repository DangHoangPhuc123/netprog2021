#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main (int argc, char **argv) {
    int sockfd, clientfd, test;
    socklen_t clen;
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

    int fl = fcntl(sockfd, F_GETFL, 0);
    fl |= O_NONBLOCK;
    fcntl(sockfd, F_SETFL, fl);
    while (1) {
        char buffer[200];
        memset(buffer, 0, 200);
        if (read(sockfd, buffer, 200) > 0) {
            printf("Server says: %s\n", buffer);
        }
        const int POLLIN;
        struct pollfd input[1] = {{.fd = 0, .events = POLLIN}};
        if (poll(input, 1, 100) > 0) {
            fgets(buffer, 200, stdin);
            buffer[strlen(buffer)] = 0;
            write(sockfd, buffer, strlen(buffer));
        }
    }
    return 0;
}

