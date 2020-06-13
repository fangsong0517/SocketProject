/*************************************************************************
	> File Name: client_recver.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月13日 星期六 14时13分16秒
 ************************************************************************/

#include "head.h"
#include "common.h"

extern int sockfd;

void *client_recv(void *arg) {
    while(1) {
        struct FootBallMsg msg;
        bzero(&msg, sizeof(msg));
        recv(sockfd, (void *)&msg, sizeof(msg), 0);
        if(msg.type & FT_TEST) {
            DBG(RED "HeartBeat from Server ❤" NONE "\n");
            msg.type = FT_ACK;
            send(sockfd, (void *)&msg, sizeof(msg), 0);
        }  else if (msg.type & (FT_MSG | FT_WALL)) {
            DBG(GREEN "Server Msg : " NONE "%s\n", msg.msg);
        } else if(msg.type & FT_FIN) {
            DBG(GREEN"Server is going to stop.\n"NONE);
            endwin();
            exit(0);
        } else {
            DBG(GREEN"Msg Unsupport\n"NONE);
        }
    }
}
