/*************************************************************************
	> File Name: thread_poll.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年06月09日 星期二 18时14分03秒
 ************************************************************************/

#include "thread_poll.h"
#include "udp_epoll.h"
extern int repollfd, bepollfd;

void do_echo(struct User *user) {
    struct FootBallMsg msg;
    int size = recv(user->fd, (void *)&msg, sizeof(msg), 0);
    user->flag = 10;
    if(msg.type & FT_ACK) {
        if(user->team)//blue_team
            DBG(L_BLUE" %s "NONE"❤\n", user->name);
        else //red_team
            DBG(L_RED" %s "NONE"❤\n", user->name);            
    } else if(msg.type & (FT_WALL | FT_MSG)) {
        if(user->team)
            DBG(L_BLUE" %s :"NONE L_RED"%s\n"NONE, user->name, msg.msg);
        else 
            DBG(L_RED" %s :"NONE L_RED"%s\n"NONE, user->name, msg.msg);
        send(user->fd, (void *)&msg, sizeof(msg), 0);//把信息回过去
    } else if(msg.type & FT_FIN) {
        DBG(RED"%s logout.\n", user->name);
        user->online = 0;
        int epollfd_tmp = (user->team ? bepollfd : repollfd);
        del_event(epollfd_tmp, user->fd);
    }
}

//初始化
void task_queue_init(struct task_queue *taskQueue, int sum, int epollfd){
    taskQueue->sum = sum;
    taskQueue->epollfd = epollfd;
    taskQueue->team = calloc(sum, sizeof(void *));//申请内存sum个
    taskQueue->head = taskQueue->tail = 0;
    pthread_mutex_init(&taskQueue->mutex, NULL);//互斥锁初始化
    pthread_cond_init(&taskQueue->cond, NULL);//条件变量初始化
    return;
}

//push
//把用户user放到队列中
void task_queue_push(struct task_queue *taskQueue, struct User *user) {
    pthread_mutex_lock(&taskQueue->mutex);//先加锁
    taskQueue->team[taskQueue->tail] = user;
    DBG(L_GREEN"Thread poll :"NONE" Task Push %s\n", user->name);//谁入队
    if(++taskQueue->tail == taskQueue->sum) {//满了
        DBG(L_GREEN"Thread poll : "NONE"Task Queue End.\n");
        taskQueue->tail = 0;
    }
    pthread_cond_signal(&taskQueue->cond);//解锁前发个信号
    pthread_mutex_unlock(&taskQueue->mutex);//解锁
    return;
}

//Pop
struct User *task_queue_pop(struct task_queue *taskQueue) {
    pthread_mutex_lock(&taskQueue->mutex);//先加锁
    while(taskQueue->tail == taskQueue->head) {//是否为空
        DBG(L_GREEN"Thread poll : "NONE
            "Task Queue Empty, Waiting For Task.\n");        
        pthread_cond_wait(&taskQueue->cond, &taskQueue->mutex);//等信号
    }
    struct User *user = taskQueue->team[taskQueue->head];//拿出头

    DBG(L_GREEN"Thread poll : "NONE"Task Pop %s.\n", user->name);            

    if(++taskQueue->head == taskQueue->sum) {//++删掉头//为空的时候
        DBG(L_GREEN"Thread poll : "NONE"Task Queue End.\n");
        taskQueue->head = 0;
    }
    pthread_mutex_unlock(&taskQueue->mutex);//关闭锁
    return user;
}

void *thread_run(void *arg) {
    pthread_t tid = pthread_self();
    pthread_detach(tid);
    struct task_queue *taskQueue = (struct task_queue *)arg;
    while(1) {
        struct User *user = task_queue_pop(taskQueue);//去除user
        do_echo(user);//操作
    }
    return NULL;
}
