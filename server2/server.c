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

#define POLLSIZE 100
#define BUFFSIZE 512
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
    int server_listen, fd;
    if((server_listen = socket_create(atoi(argv[1]))) < 0) {
        perror("socket_create");
        exit(1);
    }

    struct pollfd event_set[POLLSIZE];//client[];

    for(int i = 0; i < POLLSIZE; i++) {
        event_set[i].fd = -1;
    }

    event_set[0].fd = server_listen;
    event_set[0].events = POLLIN;

    while(1) {
        int retval;
        /*阻塞监听是佛有客户端链接请求*/
        if((retval = poll(event_set, POLLSIZE, -1)) < 0) {
            perror("poll");
            return 1;
        }
        /*listenfd有读时间就绪*/
        if(event_set[0].revents & POLLIN) {
            /*接受客户端请求accept不会阻塞*/
            if((fd = accept(server_listen, NULL, NULL)) < 0) {
                perror("accept");
                continue;
            }
            retval --;
            int i = 1;
            for(i = 1; i < POLLSIZE; i++) {
                if(event_set[i].fd < 0) {/*找到空闲位置，存放accept返回的connfd*/
                    event_set[i].fd = fd;
                    event_set[i].events = POLLIN;
                    break;
                }
            }
            if(i == POLLSIZE) {/*达到了最大客户端数*/
                printf("Too many clients!\n");
            }
        }
        for(int i = 1; i < POLLSIZE; i++) {/*检测client[]看是哪个fd满足*/
            if(event_set[i].fd < 0)continue;
            if(event_set[i].revents & (POLLIN | POLLHUP | POLLERR)) {
                retval--;
                char buff[BUFFSIZE] = {0};
                if(recv(event_set[i].fd, buff, BUFFSIZE, 0) > 0) {
                    printf("Recv : %s \n", buff);
                    for(int i = 0; i < strlen(buff); i++) {
                        buff[i] = ch_char(buff[i]);
                    }
                    send(event_set[i].fd, buff,strlen(buff), 0);
                } else {
                    close(event_set[i].fd);
                    event_set[i].fd = -1;/*poll中不监控该文件描述符，直接置位-1,不像select中那样移除*/
                }
            }
            if(retval <= 0)break;
        }
    }

    return 0;
}
