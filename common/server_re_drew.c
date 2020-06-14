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

void re_drew() {
    werase(Football);
    box(Football, 0, 0);
    re_drew_team(rteam);
    re_drew_team(bteam);
}
