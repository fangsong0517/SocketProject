/*************************************************************************
	> File Name: udp_client.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月04日 星期四 18时56分20秒
 ************************************************************************/

#include  "head.h"
int socket_udp() {
    int sockfd;
    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    printf("socket creat.\n");
    return sockfd;
}
