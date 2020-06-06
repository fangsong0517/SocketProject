/*************************************************************************
	> File Name: server.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年04月07日 星期二 18时20分30秒
 ************************************************************************/
#include"../common/head.h" 
#include"../common/color.h"

#include"../common/common.h"
#include"../common/tcp_server.h"

#define MAX_N 512
#define BUFFSIZE 1024
char ch_char(char c) {
    if(c >= 'a' && c <= 'z') {
        return c - 32;
    }
    return c;
}


int main(int argc, char **argv) {
    if(argc != 2) {
        fprintf(stderr, "Usage: %s port!\n", argv[0]);
        exit(1);
    }
    int server_listen, fd, client[MAX_N] = {0};
    if((server_listen = socket_create(atoi(argv[1]))) < 0) {
        perror("socket_create");
        exit(1);
    }
    make_nonblock(server_listen);
    int maxfd = server_listen;//开始server_listen最大
    fd_set rfds, wfds, efds;
    for(int i = 0; i < MAX_N; i++) {
        client[i] = -1;
    }
    while(1) {
        FD_ZERO(&rfds);
        FD_ZERO(&wfds);
        FD_ZERO(&efds);
        FD_SET(server_listen, &rfds);
        for(int i = 0; i < MAX_N; i++) {
            if(client[i] == server_listen)continue;
            if(client[i] > 0) {
                if(maxfd < client[i]) maxfd = client[i];
                FD_SET(client[i], &rfds);
            }
        }
        if(select(maxfd + 1, &rfds, NULL, NULL, NULL) < 0) {
            perror("select");
            return 1;
        }

        if(FD_ISSET(server_listen, &rfds)) {
            printf("Connect ready on serverlisten!\n");
            if((fd = accept(server_listen, NULL, NULL)) < 0) {
                perror("accept");
                return 1;
            }
            if(fd > MAX_N) {
                printf("Too many clients!\n");
                close(fd);
            } else {
                make_nonblock(fd);
                if(client[fd] == -1) {
                    client[fd] = fd;
                }
            }
        }
        for(int i = 0; i < MAX_N; i++) {
            if(i == server_listen) continue;
            if(FD_ISSET(i, &rfds)) {
                char buff[BUFFSIZE] = {0};
                int retval = recv(i, buff, BUFFSIZE, 0);
                if(retval <= 0) {
                    printf("Logout!\n");
                    client[i] = -1;
                    close(i);
                    continue;
                }
                printf("Recv: %s \n", buff);
                for(int j = 0; j < strlen(buff); j++) {
                    buff[j] = ch_char(buff[j]);
                }
                send(i, buff, strlen(buff), 0);
            }
        }
    }

    return 0;
}
