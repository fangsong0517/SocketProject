/*************************************************************************
	> File Name: game.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月02日 星期二 18时35分30秒
 ************************************************************************/

#include "head.h"
#include "game.h"

extern struct Map court;
extern WINDOW *Football, *Message, *Help, *Score, *Write;
int message_num = 0;
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
    WINDOW *Message_t=create_newwin(court.width, 7, court.start.x, court.start.y + court.height);
    Message = subwin(Message_t, 5, court.width - 2, court.start.y + court.height + 1, court.start.x);
    scrollok(Message, 1);
    Help=create_newwin(20, court.height, court.start.x + court.width, court.start.y);
    Score=create_newwin(20,  7, court.start.x + court.width, court.start.y + court.height);
    Write=create_newwin(court.width + 20, 5, court.start.x, court.start.y + court.height + 7);
}

void *draw(void *arg) {
    initfootball();
    while(1) {
        sleep(10);
    }
}


/*在哪个窗口显示信息*/
/*user谁*/
/*msg信息*/
void show_message(WINDOW *win, struct User *user, char *msg, int type) {
    //时间
    time_t time_now = time(NULL);
    struct tm* tm= localtime(&time_now);
    char timestr[20] = {0};
    char username[80] = {0};
    sprintf(timestr, "%02d:%02d:%02d ", tm->tm_hour, tm->tm_min, tm->tm_sec);
    
    if (type) {
        //系统信息
        wattron(win, COLOR_PAIR(4));
        strcpy(username, "Server Info : ");
    } else {
        if(user->team) 
            wattron(win, COLOR_PAIR(6));
        else 
            wattron(win, COLOR_PAIR(2));
        sprintf(username, "%s : ", user->name);
    }
    //打印信息
    if(message_num < 4) {
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    } else {
        message_num = 4;
        scroll(win);//滚动
        w_gotoxy_puts(win, 10, message_num, username);
        wattron(win, COLOR_PAIR(3));
        w_gotoxy_puts(win, 10 + strlen(username), message_num, msg);
        wattron(win, COLOR_PAIR(5));
        w_gotoxy_puts(win, 1, message_num, timestr);
        message_num++;
    }

    wrefresh(win);
}
