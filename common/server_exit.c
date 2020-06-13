/*************************************************************************
	> File Name: server.exit.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月13日 星期六 14时44分43秒
 ************************************************************************/


#include "head.h"
#define MAX 50
extern struct User *rteam, *bteam;

void server_exit(int signum) {
    struct FootBallMsg msg;
    msg.type = FT_FIN;
    for(int i = 0; i < MAX; i++) {
        if(rteam[i].online) send(rteam[i].fd, (void *)&msg, sizeof(msg), 0);
        if(bteam[i].online) send(bteam[i].fd, (void *)&msg, sizeof(msg), 0);
    }
    endwin();
    DBG(RED"Server stopped!\n"NONE);
    exit(0);
}
