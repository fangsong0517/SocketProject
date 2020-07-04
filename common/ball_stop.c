/*************************************************************************
	> File Name: ball_stop.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年07月04日 星期六 17时29分10秒
 ************************************************************************/

#include "head.h"

extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int ball_stop(struct Point *loc) {
	int px = loc->x;
	int py = loc->y;
	if (abs(px - (int)ball.x) <= 2 && abs(py - (int)ball.y) <= 2) {
		ball_status.a.x = 0;
		ball_status.a.y = 0;
		ball_status.v.x = 0;
		ball_status.v.y = 0;
        return 1;
    }
    return 0;
}


