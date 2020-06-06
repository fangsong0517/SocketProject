/*************************************************************************
	> File Name: server.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年05月28日 星期四 19时13分15秒
 ************************************************************************/

#include "../common/common.h"
#include "../common/head.h"
#include "../common/udp_server.h"
int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s port\n", argv[0]);
        exit(1);
    }
    int port, sockfd;
    struct sockaddr_in client;
    port = atoi(argv[1]);
    socklen_t addr_len = sizeof(client);
    if((sockfd = socket_create_udp(port)) < 0) {
        perror("udp_create");
        exit(1);
    }
    memset(&client, 0, sizeof(struct sockaddr_in));

    while(1) {
        char buff[512] = {0};
        if((recvfrom(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, &addr_len)) > 0) {
            printf("[%s]: %s", inet_ntoa(client.sin_addr), buff);
        }
        sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&client, addr_len);
    }
    return 0;
}
