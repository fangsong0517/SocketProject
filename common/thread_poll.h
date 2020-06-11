/*************************************************************************
	> File Name: thread_poll.h
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月09日 星期二 18时13分55秒
 ************************************************************************/

#ifndef _THREAD_POLL_H
#define _THREAD_POLL_H
#include "head.h"
#define MAXTASK 100 //最多任务
#define MAXTHREAD 10 //放10个线程
struct task_queue{
    int sum;//多少个
    int epollfd;//对应的从反应堆
    struct User **team;//队
    int head;
    int tail;
    pthread_mutex_t mutex;//互斥锁
    pthread_cond_t cond;
};

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd);//初始化
void task_queue_push(struct task_queue *taskQueue, struct User *user);//入队
struct User *task_queue_pop(struct task_queue *taskQueue);//弹出一个用户
void *thread_run(void *arg);//做什么用的，回调函数
#endif
