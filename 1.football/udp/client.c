/*************************************************************************
	> File Name: client.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月04日 星期四 18时21分37秒
 ************************************************************************/

#include "../common/color.h"

#include "../common/common.h"

#include "../common/head.h"

#include "../common/udp_client.h"

int main(int argc, char **argv) {
    if(argc != 3) {
        fprintf(stderr, "Usage : %s ip port!\n", argv[0]);
        exit(1);
    }
    char ip[20] = {0};
    int port = atoi(argv[2]);
    strncpy(ip, argv[1], 20);
    char msg[512] = {0};
    int sockfd;
    struct sockaddr_in server;
    socklen_t len = sizeof(server);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(ip);
    if((sockfd = socket_udp()) < 0) {
        perror("socket_udp");
        exit(1);
    }

    if(connect(sockfd, (struct sockaddr *)&server, len) < 0) {
        perror("connect");
        exit(1);
    }
    sendto(sockfd, "hi", sizeof("hi"), 0, (struct sockaddr *)&server, len);

    sleep(1);
    recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)&server, &len);

    printf("D : recv from server: %s \n", msg);


    return 0;
}

