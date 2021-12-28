#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <netinet/in.h>
#include <arpa/inet.h>

void str_echo(int sockfd)
{
    ssize_t n;
    char buf[1026];

again:

    while ((n = read(sockfd, buf, 1024)) > 0)
    {
        // fputs(buf, stdout);
        write(sockfd, buf, n);
    }

    if (n < 0)
        goto again;
    else if (n < 0)
        ;
    // err_sys("str_echo: read error");
}
int main(int argc, char **argv)
{
    int listenfd, connfd;
    pid_t childpid;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    // bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(9878);
    bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    listen(listenfd, 3);
    for (;;)
    {
        clilen = sizeof(cliaddr);
        connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
        if ((childpid = fork()) == 0)
        {                     /* child process */
            close(listenfd);  /* close listening socket */
            str_echo(connfd); /* process the request */
            exit(0);
        }
        close(connfd); /* parent closes connected socket */
    }
}
