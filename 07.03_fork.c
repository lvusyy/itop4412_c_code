//
// Created by OthinkY on 6/15/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

#include <unistd.h>

int main(int argn, char *argv[]) {
    int count = 1;
    int child;
    child = fork();//进程从这里开始复制并一个子进程出来了
    //如果是子进程 child的值 内核会返回0
    //如果是父进程 child的值 内核会返回子进程的pid
    if (child < 0) {
        printf("fork子进程失败\n");
    } else if (child == 0) {
        printf("这是子进程,count is:%d (%p). pid is:%d ppid is:%d\n", ++count, &child, getpid(), getppid());
    } else {
        printf("这里是父进程,count is:%d (%p). pid is:%d ppid is:%d\n", ++count, &child, getpid(), getppid());
    }
    //EXIT_SUCCESS 被定义为常量0
    return EXIT_SUCCESS;
}
