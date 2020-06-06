/*************************************************************************
	> File Name: epoll.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年04月11日 星期六 20时25分31秒
 ************************************************************************/

#include <sys/epoll.h>
#define MAX_EVENTS 10
#include "../common/head.h"
#include "../common/tcp_server.h"
#include "../common/common.h"
#define BUFFSIZE 512

int main(int argc, char **argv) {
    struct epoll_event ev, events[MAX_EVENTS];/*ev:epoll_ctl参数 events[]:epoll_wait参数*/
    int listen_sock, conn_sock, nfds, epollfd;
    char buff[BUFFSIZE] = {0};
    if (argc != 2) exit(1);
    listen_sock = socket_create(atoi(argv[1]));
/* Code to set up listening socket, 'listen_sock',
   (socket(), bind(), listen()) omitted */
    epollfd = epoll_create1(0);/*创建epoll模型,epollfd指向红黑树根节点*/
    if (epollfd == -1) {
        perror("epoll_create1");
        exit(EXIT_FAILURE);
    }

    ev.events = EPOLLIN;/*指定lfd的监听事件为"读"*/
    ev.data.fd = listen_sock;

    if (epoll_ctl(epollfd, EPOLL_CTL_ADD, listen_sock, &ev) == -1) {/*将lfd及对应的结构体设置到树上,epollfd可找到该树*/
        perror("epoll_ctl: listen_sock");
        exit(EXIT_FAILURE);
    }

    for (;;) {
        /*epoll为server阻塞监听事件,events为struct epoll_event类型数组,MAX_EVENTS维数组容量,-1代表永久阻塞*/
        nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1);

        if (nfds == -1) {
            perror("epoll_wait");
            exit(EXIT_FAILURE);
        }

        for (int n = 0; n < nfds; ++n) {
            if (events[n].data.fd == listen_sock) { //判断事件fd是不是lfd;
                conn_sock = accept(listen_sock, NULL, NULL); //接受链接
                if (conn_sock == -1) {
                    perror("accept");
                    exit(EXIT_FAILURE);
                }
                make_nonblock(conn_sock);
                ev.events = EPOLLIN | EPOLLET;
                ev.data.fd = conn_sock;

                if (epoll_ctl(epollfd, EPOLL_CTL_ADD, conn_sock, &ev) == -1) {
                    perror("epoll_ctl: conn_sock");
                    exit(EXIT_FAILURE);
                }
            } else {//不是lfd
                //do_use_fd(events[n].data.fd);
                if (events[n].events & (EPOLLIN | EPOLLHUP | EPOLLERR)) {
                    memset(buff, 0, sizeof(buff));
                    if (recv(events[n].data.fd, buff, BUFFSIZE, 0) > 0) {
                        printf("recv: %s", buff);
                        for (int i = 0; i < strlen(buff); i++) {
                            if (buff[i] >= 'a' && buff[i] <= 'z') buff[i] -= 32;
                        }
                        send(events[n].data.fd, buff, strlen(buff), 0);
                    } else {
                        if (epoll_ctl(epollfd, EPOLL_CTL_DEL, events[n].data.fd, NULL) < 0) {//将该文件描述符从红黑树摘除
                            perror("epoll_ctrl");
                        }
                        close(events[n].data.fd);
                        printf("Logout!\n");
                    }
                }
            }
        }
    }
return 0;
}
