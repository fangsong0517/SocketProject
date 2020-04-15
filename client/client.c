/*************************************************************************
	> File Name: client.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年03月28日 星期六 14时51分50秒
 ************************************************************************/
/*
#include "head.h"
#include "tcp_client.h"
int main(int argc, char **argv) {
    char msg[512] = {0};
    int sockfd;
    if (argc != 3) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        return 1;
    }

    if ((sockfd = socket_connect(argv[1], atoi(argv[2]))) < 0) {
        perror("socket_connect");
        return 2;
    }
    make_nonblock(sockfd);
    recv(sockfd, msg, 512, 0);
    printf("recv : %s\n", msg);
    close(sockfd);
    return 0;
}
*/

#include "head.h"
#include "tcp_client.h"

int main(int argc, char **argv) {
    char msg[512] = {0};
    int sockfd;
    if (argc != 4) {
        fprintf(stderr, "Usage: %s ip port\n", argv[0]);
        return 1;
    }

    if ((sockfd = socket_connect_timeout(argv[1], atoi(argv[2]), atoi(argv[3]))) < 0) {
        perror("socket_connect");
        return 2;
    }

    printf("socket_connect!\n");
    close(sockfd);
    return 0;
}

