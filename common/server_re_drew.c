/*************************************************************************
	> File Name: server_re_drew.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月14日 星期日 20时29分34秒
 ************************************************************************/

#include "head.h"
#include "game.h"
#define MAX 50
extern struct User *rteam, *bteam;
extern WINDOW *Football;

extern struct Bpoint ball;
extern struct BallStatus ball_status;
extern struct Score score;

void re_drew_player(int team, char *name, struct Point *loc) {
    char p = 'K';
    if(team) {
        wattron(Football, COLOR_PAIR(6));
    } else {
        wattron(Football, COLOR_PAIR(2));        
    }
    w_gotoxy_putc(Football, loc->x, loc->y, p);
    w_gotoxy_puts(Football, loc->x + 1, loc->y - 1, name);
}

void re_drew_team(struct User *team) {
    for(int i = 0; i < MAX; i++) {
        if(!team[i].online)continue;
        re_drew_player(team[i].team, team[i].name, &team[i].loc);
    }
}

void re_draw_ball() {
    int px, py;
    if(ball_status.carry == 0) {
    double t = 0.1;
    if((int)ball_status.v.x != 0 ||(int)ball_status.v.y != 0 ) {
        ball.x += ball_status.v.x * t + ball_status.a.x * 0.5 * 0.01;
        ball.y += ball_status.v.y * t + ball_status.a.y * 0.5 * 0.01;
        ball_status.v.x += ball_status.a.x * t;
        ball_status.v.y += ball_status.a.y * t;
    }
    if (ball_status.v.x || ball_status.v.y) {
		char tmp[512] = {0};
		sprintf(tmp, "a(%lf, %lf) v(%lf, %lf)", ball_status.a.x, ball_status.a.y, ball_status.v.x, ball_status.v.y);
		Show_Message( , NULL, tmp, 1);
	}
	if (ball.x <= 0 || ball.x >= 114 || ball.y <= 0 || ball.y >= 24) {
        if((int)ball.y >= court.height / 2 - 4 && (int)ball.y <= court.height / 2 + 4 && ball.x <= 1) {
            score.blue ++;
        }
        if((int)ball.y >= court.height / 2 - 4 && (int)ball.y <= court.height / 2 + 4 && ball.x >= 114) {
            score.red ++;
        }     
		ball.x = court.width / 2;
		ball.y = court.height / 2;
		ball_status.v.x = ball_status.v.y = 0;
		ball_status.a.x = ball_status.a.y = 0;
	}
    } else if(ball_status.carry == 1) {
        int dir[8][2] = {1, 0, -1, 0,
                        1, 1, 1, -1,
                        0, 1, 0, -1,
                        -1, 1, -1, -1};
        for(int i = 0; i < MAX; i++) {
            if(rteam[i].carry == 1) {
                px = rteam[i].loc.x;
                py = rteam[i].loc.y;
            }
            if(bteam[i].carry == 1) {
                px = bteam[i].loc.x;
                py = bteam[i].loc.y;
            }
        }
        if (abs(px - (int)ball.x) <= 3 && abs(py - (int)ball.y <= 3)) {
		    ball_status.v.x = ball_status.v.y = 0;
		    ball_status.a.x = ball_status.a.y = 0;
            ball.x = px + dir[rand() % 8][rand() % 2];
            ball.y = py + dir[rand() % 8][rand() % 2];
        }
    }
    w_gotoxy_putc(Football, (int)ball.x, (int)ball.y, 'O');
}

void ball_door(){
    for(int i = court.height / 2 - 4; i <= court.height / 2 + 4; i++){
        w_gotoxy_putc(Football_t, 1, i, 'x');
        w_gotoxy_putc(Football_t, 117, i, 'x');
    }
}

void init_score() {
    w_gotoxy_puts(Score, 1, 1, "red blue\n");
    char tmp[50];
    sprintf(tmp, "%d:%d", score.red, score.blue);
    w_gotoxy_puts(Score, 1, 2, tmp);
}


void re_drew() {
    werase(Football);
    box(Football_t, 0, 0);
    box(Football, 0, 0);
    re_drew_team(rteam);
    re_drew_team(bteam);
   // ball_door();
    init_score();
    re_draw_ball();
    wrefresh(Football_t);
}
