/*************************************************************************
	> File Name: game.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月02日 星期二 18时35分30秒
 ************************************************************************/

#ifndef _GAME_H
#define _GAME_H
#include <curses.h>
#define MAX 50


struct Map court;

WINDOW *Football, *Message, *Help, *Score, *Write;

WINDOW *create_newwin(int width, int height, int startx, int starty) {
    //Create WINDOW
    WINDOW *win;
    win = newwin(height, width, starty, startx);
    box(win, 0, 0);/*0 0是字符默认行列起始位置*/
    wrefresh(win);/*刷新窗口缓冲，显示box*/
    return win;
}

void destroy_win(WINDOW *win) {
    //Destroy WINDOW

    //delete line
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    delwin(win);
}


void gotoxy(int x, int y) {
    move(y , x);
}

void gotoxy_putc(int x, int y,char c) {
    move(y, x);
    addch(x);
    move(LINES - 1, 1);
    refresh();
}
void gotoxy_puts(int x, int y,char *c) {
    move(y, x);
    addstr(c);
    move(LINES - 1, 1);
    refresh();
}

void w_gotoxy_putc(WINDOW *win, int x, int y, char c) {
    mvwaddch(win, y, x, c);
    move(LINES - 1, 1);
    wrefresh(win);
}

void w_gotoxy_puts(WINDOW *win, int x, int y, char *s) {
    mvwprintw(win, y, x, s);
    move(LINES - 1, 1);
    wrefresh(win);
}

void initfootball() {
    initscr();
    clear();
    if(!has_colors() || start_color() == ERR) {
        endwin();
        fprintf(stderr, "终端不支持颜色！\n");
    }
    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_RED, COLOR_BLACK);
    init_pair(3, COLOR_WHITE, COLOR_BLACK);    
    init_pair(4, COLOR_YELLOW, COLOR_BLACK);
    init_pair(5, COLOR_CYAN, COLOR_BLACK);    
    init_pair(6, COLOR_BLUE, COLOR_BLACK);
    Football=create_newwin(court.width, court.height, court.start.x, court.start.y);
    Message=create_newwin(court.width, 5, court.start.x, court.start.y + court.height);
    Help=create_newwin(20, court.height, court.start.x + court.width, court.start.y);
    Score=create_newwin(20,  5, court.start.x + court.width, court.start.y + court.height);
    Write=create_newwin(court.width + 20, 5, court.start.x, court.start.y + court.height + 5);
}

void *draw(void *arg) {
    initfootball();
    while(1) {
        sleep(10);
    }
}
#endif
