/*************************************************************************
	> File Name: send_ctl.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月14日 星期日 20时07分47秒
 ************************************************************************/

#include "head.h"

extern int sockfd;
extern struct FootBallMsg ctl_msg;

void send_ctl() {
    if (ctl_msg.ctl.dirx || ctl_msg.ctl.diry) {
        send(sockfd, (void *)&ctl_msg, sizeof(ctl_msg), 0 );
    }
    ctl_msg.ctl.dirx = ctl_msg.ctl.diry = 0;
}

