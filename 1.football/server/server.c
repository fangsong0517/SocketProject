/*************************************************************************
	> File Name: server.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月02日 星期二 18时14分47秒
 ************************************************************************/
#include "../common/head.h"
#include "../common/heart_beat.h"
#include "../common/sub_reactor.h"
#include "../common/thread_poll.h"
#include "../common/udp_epoll.h"
#include "../common/udp_server.h"
#include "../common/game.h"
#include "../common/server_exit.h"
#include "../common/server_re_drew.h"
char *conf = "./server.conf";

struct User *rteam;
struct User *bteam;
int data_port;
int port = 0;
int repollfd, bepollfd;

// struct Map court;
struct Bpoint ball;
struct BallStatus ball_status;
struct Score score;
int main(int argc, char **argv) {
    int opt, listener, epoll_fd;
    pthread_t draw_t, red_t, blue_t, heart_t;
    while ((opt = getopt(argc, argv, "p:")) != -1) {
        switch (opt) {
            case 'p':
                port = atoi(optarg);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
                exit(1);
        }
    }
    argc -= (optind - 1);
    argv += (optind - 1);

    if (argc > 1) {
        fprintf(stderr, "Usage: %s [-p port]\n", argv[0]);
        exit(1);
    }

    if (!port) port = atoi(get_value(conf, "PORT"));
    data_port = atoi(get_value(conf, "DATAPORT"));

    court.width = atoi(get_value(conf, "COLS"));
    court.height = atoi(get_value(conf, "LINES"));
    court.start.x = 3;
    court.start.y = 1;

    rteam = (struct User *)calloc(MAX, sizeof(struct User));
    bteam = (struct User *)calloc(MAX, sizeof(struct User));

    ball.x = court.width / 2;
    ball.y = court.height / 2;

    if ((listener = socket_create_udp(port)) < 0) {
        perror("socket_create_udp");
        exit(1);
    }

    DBG(GREEN "INFO" NONE " : Server start on Port %d\n", port);
#ifndef _D
    pthread_create(&draw_t, NULL, draw, NULL);
#endif
    epoll_fd = epoll_create(MAX * 2);
    repollfd = epoll_create(MAX);
    bepollfd = epoll_create(MAX);

    if (epoll_fd < 0 || repollfd < 0 || bepollfd < 0) {
        perror("epoll_create");
        exit(1);
    }

    struct task_queue redQueue;
    struct task_queue blueQueue;

    task_queue_init(&redQueue, MAX, repollfd);
    task_queue_init(&blueQueue, MAX, bepollfd);

    pthread_create(&red_t, NULL, sub_reactor, (void *)&redQueue);
    pthread_create(&blue_t, NULL, sub_reactor, (void *)&blueQueue);
    pthread_create(&heart_t, NULL, heart_beat, NULL);

    signal(SIGINT, server_exit);
    struct epoll_event ev, events[MAX * 2];
    ev.events = EPOLLIN;
    ev.data.fd = listener;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listener, &ev);
    struct sockaddr_in client;
    socklen_t len = sizeof(client);
    
    signal(14, re_drew);

    struct itimerval itimer;
    itimer.it_interval.tv_sec = 0;
    itimer.it_interval.tv_usec = 50000;
    itimer.it_value.tv_sec = 5;
    itimer.it_value.tv_usec = 0;
    setitimer(ITIMER_REAL, &itimer, NULL);

    Show_Message( , , "Waiting for Login.", 1);
    while (1) {
        DBG(YELLOW "Main Thread" NONE " : Before epoll_wait\n");
        int nfds = epoll_wait(epoll_fd, events, MAX * 2, -1);
        DBG(YELLOW "Main Thread" NONE " : After epoll_wait\n");

        for (int i = 0; i < nfds; ++i) {
            struct User user;
            char buff[512] = {0};
            DBG(YELLOW "EPOLL" NONE " : Doing with %dth fd\n", i);
            if (events[i].data.fd == listener) {
                int new_fd = udp_accept(epoll_fd, listener, &user);
                if (new_fd > 0) {
                    sprintf(buff, "%s Login the Game.", user.name);
                    DBG(YELLOW "Main Thread" NONE
                               " : Add %s to %s sub_reactor.\n",
                        user.name, (user.team ? "BLUE" : "RED"));
                    add_to_sub_reactor(&user);//用户加到相应的反应堆里
                    Show_Message(, ,buff, 1);
                }
            } else {
                recv(events[i].data.fd, buff, sizeof(buff), 0);
                printf(PINK "RECV" NONE " : %s\n", buff);
            }
            // char info[1024] = {0};
            // w_gotoxy_puts(Message, 1, 2, info);
        }
    }
    return 0;
}
