/*************************************************************************
	> File Name: common.c
	> Author:fangsong
	> Mail: 
	> Created Time: 2020年03月28日 星期六 20时22分45秒
 ************************************************************************/

#include "head.h"

void make_nonblock_ioctl(int fd) {
    unsigned long ul = 1;
    ioctl(fd, FIONBIO, &ul);
}

void make_block_ioctl(int fd) {
    unsigned long ul = 0;
    ioctl(fd, FIONBIO, &ul);
}

/*int ioctl( int fd, int request, ... void *arg  );
 * 本函数影响由fd参数引用的一个打开的文件。
 *FIONBIO:  根据ioctl的第三个参数指向一个0或非0值分别清除或设置本套接口的非阻塞标志。
 *本请求和O_NONBLOCK文件状态标志等效，而该标志通过fcntl的F_SETFL命令清除或设置。
 *
* */

/*
void make_nonblock(int fd) {
    fcntl(fd, F_SETFL, O_NONBLOCK);
}

void make_block(int fd) {
    fcntl(fd, F_SETFL, ~O_NONBLOCK);
}
*/

/* int fcntl(int fd, int cmd, long arg); 
 * fd：文件描述词。 
 * cmd：操作命令。 
 * arg：供命令使用的参数。 
 * 功能描述：根据文件描述词来操作文件的特性。 
 *F_SETSIG：设置标识输入输出可进行的信号。 

 * */
 void make_nonblock(int fd) {
     int flags;
     if(flags = fcntl(fd, F_GETFL, 0) < 0) {
         perror("fcntl");
     }
     flags |= O_NONBLOCK;
     if(fcntl(fd, F_SETFL, flags) < 0) {
         perror("fcntl");
     }
 }

 void make_block(int fd) {
     int flags;
     if(flags = fcntl(fd, F_GETFL, 0) < 0) {
         perror("fcntl");
     }
     flags &= ~O_NONBLOCK;
     if(fcntl(fd, F_SETFL, flags) < 0) {
         perror("fcntl");
     }
 }


