/*************************************************************************
	> File Name: datatype.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月06日 星期六 20时24分07秒
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H
struct LogRequest{
    char name[20];
    int team;//0 RED 1 BLUE
    char msg[512];
};

struct LogResponse{
    int type;//0 success 1 failed
    char msg[512];
};

struct Point{
    int x, y;
};

struct User{
    int team; //0  1
    char name[20];//name
    int flag; //未响应的次数
    struct sockaddr_in addr;
    struct Point loc;//position
};

struct Map{
    int width;
    int height;
    struct Point start;  // Starting Point 
    int gate_width;  // Goal size
    int gate_height;
};

struct Ctrl { 
    //control
    int carry;
    int kick;
};

struct TransMsg{
    int dirx;
    int diry;
    struct Ctrl ctrl;
};

#endif
