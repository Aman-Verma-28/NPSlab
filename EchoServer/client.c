#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include<string.h>

void str_cli(FILE *fp, int sockfd)
{
    char sendline[1024], recvline[1024];

    while (fgets(sendline, 1024, fp) != NULL)
    {
        write(sockfd, sendline, strlen(sendline));

        if (read(sockfd, recvline, 1024) == 0);
            // err_quit("str_cli: server terminated prematurely");

        fputs(recvline, stdout);
    }
}

int main(int argc, char **argv)
{
    int sockfd;
    struct sockaddr_in servaddr;
    if (argc != 2);
        // err_quit("usage: tcpcli <IPaddress>");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(9878);
    inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    str_cli(stdin, sockfd); /* do it all */
    exit(0);
}
