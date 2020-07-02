/*************************************************************************
	> File Name: ball_status.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年07月02日 星期四 22时00分53秒
 ************************************************************************/

#include "head.h"
extern WINDOW *Message;
extern struct Bpoint ball;
extern struct BallStatus ball_status;

int can_kick(struct Point *loc, int strength) {
    int px = loc->x, py = loc->y; //将人和球的坐标对其
    if (abs(px - (int)ball.x) < 2 && abs(py - (int)ball.y <= 2)) {
        if (px == (int)ball.x && py == (int)ball.y) return 0;
        double dx = (ball.x - px) / pow(pow((ball.x - px), 2) + pow((ball.y - py), 2), 0.5);
        double dy = (ball.y - py) / pow(pow((ball.x - px), 2) + pow((ball.y - py), 2), 0.5);
        ball_status.a.x = -3 * dx; //a of air resistans
        ball_status.a.y = -3 * dy;
        ball_status.v.x = strength * 8 * dx;
        ball_status.v.y = strength * 8 * dy;
        return 1;
    }
    return 0;
}

