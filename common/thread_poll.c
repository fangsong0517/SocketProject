/*************************************************************************
	> File Name: thread_poll.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月09日 星期二 18时14分03秒
 ************************************************************************/

#include "thread_poll.h"

void do_echo(struct User *user) {
    struct FootBallMsg msg;
    int size = recv(user->fd, (void *)&msg, sizeof(msg), 0);
    if(msg.type & FT_ACK) {
        if(user->team)
            DBG(L_BLUE" %s "NONE"❤\n", user->name);
        else 
            DBG(L_RED" %s "NONE"❤\n", user->name);            
    } else if(msg.type & (FT_WALL | FT_MSG)) {
        if(user->team)
            DBG(L_BLUE" %s :"NONE L_GREEN"%s\n"NONE, user->name, msg.msg);
        else 
            DBG(L_RED" %s :"NONE L_GREEN"%s\n"NONE, user->name, msg.msg);
        send(user->fd, (void *)&msg, sizeof(msg), 0);
    }
}

void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd){
    taskQueue->sum = sum;
    taskQueue->epollfd = epollfd;
    taskQueue->team = calloc(sum, sizeof(void *));
    taskQueue->head = taskQueue->tail = 0;
    pthread_mutex_init(&taskQueue->mutex, NULL);
    pthread_cond_init(&taskQueue->cond, NULL);
    return;
}

void task_queue_push(struct task_queue *taskQueue, struct User *user) {
    pthread_mutex_lock(&taskQueue->mutex);
    taskQueue->team[taskQueue->tail] = user;
    DBG(L_GREEN"Thread poll :"NONE" Task Push %s\n", user->name);
    if(++taskQueue->tail == taskQueue->sum) {
        DBG(L_GREEN"Thread poll : "NONE"Task Queue End.\n");
        taskQueue->tail = 0;
    }
    pthread_cond_signal(&taskQueue->cond);
    pthread_mutex_unlock(&taskQueue->mutex);
    return;
}

struct User *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);
    while(taskQueue->tail == taskQueue->head) {
        DBG(L_GREEN"Thread poll : "NONE
            "Task Queue Empty, Waiting For Task.\n");        
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);
    }
    struct User *user = taskQueue->team[taskQueue->head];

    DBG(L_GREEN"Thread poll : "NONE"Task Pop %s.\n", user->name);            

    if(++taskQueue->head == taskQueue->sum) {
        DBG(L_GREEN"Thread poll : "NONE"Task Queue End.\n");
        taskQueue->head = 0;
    }
    pthread_mutex_unlock(&taskQueue->mutex);
    return user;
}

void *thread_run(void *arg) {
    pthread_t tid = pthread_self();
    pthread_detach(tid);
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while(1) {
        struct User *user = task_queue_pop(taskQueue);
        do_echo(user);
    }
    return NULL;
}
