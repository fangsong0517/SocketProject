/*************************************************************************
	> File Name: client.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年03月22日 星期日 20时22分39秒
 ************************************************************************/
#include "head.h"
#include "common.h"
int socket_connect(char *host, int port) {
    int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);

    if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    /*
     connect()用于建立与指定socket的连接。
     头文件: #include <sys/socket.h>
     函数原型: int connect(SOCKET s, const struct sockaddr * name, int namelen);
    参数:
    s：标识一个未连接socket
    name：指向要连接套接字的sockaddr结构体的指针
    namelen：sockaddr结构体的字节长度
     */
    printf("Socket create.\n");
    if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("connect");
        return -1;
    }
    /*
     send（）是一个计算机函数，功能是向一个已经连接的socket发送数据
     int send( SOCKET s, const char FAR *buf, int len, int flags );
     不论是客户还是服务器应用程序都用send函数来向TCP连接的另一端发送数据。
    客户程序一般用send函数向服务器发送请求，而服务器则通常用send函数来向客户程序发送应答。
（1）第一个参数指定发送端套接字描述符；
（2）第二个参数指明一个存放应用程序要发送数据的缓冲区；
（3）第三个参数指明实际要发送的数据的字节数；
（4）第四个参数一般置0。
    */
    return 0;
}

int socket_connect_timeout(char *host, int port, long timeout) {
    int sockfd;
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    server.sin_addr.s_addr = inet_addr(host);

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        return -1;
    }
    make_nonblock(sockfd);
    struct timeval tv;
    fd_set wfds;
    FD_ZERO(&wfds);
    FD_SET(sockfd, &wfds);
    tv.tv_sec = 0;
    tv.tv_usec = timeout;
    if (connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0) {
        int retval, error = -1;
        int len = sizeof(int);
        retval = select(sockfd + 1, NULL, &wfds, NULL, &tv);

        if(retval < 0) {
            close(sockfd);
            return -1;
        } else if(retval) {
            //ok;
            if(getsockopt(sockfd, SOL_SOCKET, SO_ERROR, &error,(socklen_t *)&len ) < 0) {
                close(sockfd);
                return -1;
            }
            if(error) {
                close(sockfd);
                return -1;
            }
        } else {
            //timeout;
            printf("Connect Time Out!\n");
            close(sockfd);
            return -1;
        }
    }
    make_block(sockfd);
    return sockfd;
}

