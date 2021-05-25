#include <arpa/inet.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char const *argv[]){
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

