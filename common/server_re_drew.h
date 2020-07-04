/*************************************************************************
	> File Name: server_re_drew.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月14日 星期日 20时29分29秒
 ************************************************************************/

#ifndef _SERVER_RE_DREW_H
#define _SERVER_RE_DREW_H
void re_drew_player(int team, char *name, struct Point *loc);
void re_drew_team(struct User *team);
void re_draw_ball();
void init_score();
void re_drew();
#endif
