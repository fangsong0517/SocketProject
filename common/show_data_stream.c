/*************************************************************************
	> File Name: show_data_stream.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月30日 星期二 23时20分17秒
 ************************************************************************/

#include "head.h"
extern char data_stream[20];
extern WINDOW *Help;
extern struct Map court;
//type 'l'(login) 'c'(carry) 'k'(kick) 's'(stop) 'n'normal 'e'(exit)

void show_data_stream(char type) {
    for(int i = 18; i > 1; i--) {
        data_stream[i] = data_stream[i - 1];
    }
    data_stream[1] = type;
    for(int i = 1; i < 19; i++) {
        switch(data_stream[i]) {
            case 'l': {
                wattron(Help, COLOR_PAIR(7));
            }break;
            case 'c': {
                wattron(Help, COLOR_PAIR(8));
            }break;
            case 'k': {
                wattron(Help, COLOR_PAIR(9));
            }break;
            case 's': {
                wattron(Help, COLOR_PAIR(10));
            }break;
            case 'n': {
                wattron(Help, COLOR_PAIR(11));
            }break;
            case 'e': {
                wattron(Help, COLOR_PAIR(12));
            }break;
        }
        mvwprintw(Help, court.height, i, " ");
        wrefresh(Help);
    }
    return;
}
