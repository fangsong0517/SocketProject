/*************************************************************************
	> File Name: thread_poll.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月09日 星期二 18时13分55秒
 ************************************************************************/

#ifndef _THREAD_POLL_H
#define _THREAD_POLL_H
#include "head.h"
#define MAXTASK 100
#define MAXTHREAD 10
struct task_queue{
    int sum;
    int epollfd;//对应的从反应堆
    struct User **team;
    int head;
    int tail;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);
void task_queue_push(struct task_queue *taskQueue, struct User *user);
struct User *task_queue_pop(struct task_queue *taskQueue);
void *thread_run(void *arg);
#endif
