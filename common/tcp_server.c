/*************************************************************************
	> File Name: server.c
	> Author: suyelu
	> Mail: suyelu@haizeix.com
	> Created Time: Sun 22 Mar 2020 08:24:46 PM CST
 ************************************************************************/

#include "head.h"
int socket_create(int port) {
    int server_listen;
    if ((server_listen = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = INADDR_ANY;

    struct linger m_linger;
    m_linger.l_onoff = 1;
    m_linger.l_linger = 5;
    if (setsockopt(server_listen, SOL_SOCKET, SO_LINGER, &m_linger, (socklen_t)sizeof(m_linger)) < 0) {
        return -1;
    }
    int flag = 1;
    if (setsockopt(server_listen, SOL_SOCKET, SO_REUSEADDR, &flag, sizeof(int)) < 0) {
        return -1;
    }


    if (bind(server_listen, (struct sockaddr *)&server, sizeof(server)) < 0) {
        return -1;
    }

    if (listen(server_listen, 20) < 0){
        return -1;
    }
   /* int maxfd = server_listen;
    struct timeval tv;
    int retval;
    fd_set rfds;
    FD_ZERO(&rfds);
    FD_SET(maxfd, &rfds);    
    int sub, fd;
    tv.tv_sec = 5;
    tv.tv_usec = 0;
    retval = select(maxfd + 1, &rfds, NULL, NULL, &tv);
    if(retval == -1) {
        perror("select()");
    } else if(retval) {
        printf("Data is available now.\n");
    } else {
        printf("No data within five seconds.\n");
    }

    if ((fd = accept(maxfd, NULL, NULL)) < 0) {
        perror("accept");
    }
    if(fd > maxfd) {
       maxfd = fd;
    }*/
    return server_listen;
}

