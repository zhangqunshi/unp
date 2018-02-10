#include <stdio.h>
#include <stdlib.h>
#include "../lib/unp.h"


int main(int argc, char **argv)
{
    printf("start\n");

    int sockfd, n;
    char recvline[MAXLINE + 1];
    struct sockaddr_in6 servaddr;

    if (argc != 2)
        err_quit("usage: a.out <IP address>");

    if ( (sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        err_sys("Socket Error");

    bzero(&servaddr, sizeof(servaddr)); // init zero
    printf("bzero OK\n");

    servaddr.sin6_family = AF_INET;
    servaddr.sin6_port = htons(13); // port 13

    if (inet_pton(AF_INET6, argv[1], &servaddr.sin6_addr) <= 0)
        err_quit("inet_pton error for %s", argv[1]);

    printf("inet_pton OK\n");

    if (connect(sockfd, (SA*) &servaddr, sizeof(servaddr)) < 0)
        err_sys("connect error");

    printf("connect to %s OK\n", argv[1]);

    while ( (n = read(sockfd, recvline, MAXLINE)) > 0 ) {
        recvline[n] = 0; /* null terminate */
        if (fputs(recvline, stdout) == EOF)
            err_sys("fputs error");
    }

    printf("read OK\n");

    if (n < 0)
        err_sys("read error");

    printf("Hello world!\n");
    return 0;
}
