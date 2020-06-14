/*************************************************************************
	> File Name: datatype.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月06日 星期六 20时24分07秒
 ************************************************************************/

#ifndef _DATATYPE_H
#define _DATATYPE_H
#define MAXMSG 1024
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
    int fd; //存储用户的连接
    int online;
    int flag; //未响应的次数
   // struct sockaddr_in addr;
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
    int dirx;
    int diry;
};

#define FT_TEST 0x01 //服务端心跳信息
#define FT_WALL 0x02 //服务端以字符串方式广播游戏情况
#define FT_MSG 0x04 //客户端发送的信息，服务端转发的信息
#define FT_ACK 0x08 //客户端对心跳ACK确认
#define FT_FIN 0x10 //客户端，服务端下线前，对彼此的告知
#define FT_CTL 0x20 //客户端发送的控制信息
#define FT_GAME 0x40 //服务端向客户端广播的游戏实时图画json发送
#define FT_SCORE 0x80 //服务端对客户端广播的游戏比分变化,json发送(包括进球人)
#define FT_GAMEOVER 0x100 //游戏结束

struct FootBallMsg {
    //登陆后的信息交互
    int type;
    int size;
    int team;
    char name[20];
    struct Ctrl ctl;
    char msg[MAXMSG];
};

#endif
