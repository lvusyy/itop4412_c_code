//
// Created by OthinkY on 6/14/2017.
//

//
//Unix标准的复制进程的系统调用时fork（即分叉），但是Linux，BSD等操作系统并不止实现这一个，确切的说linux实现了三个，fork,vfork,clone（确切说vfork创造出来的是轻量级进程，也叫线程，是共享资源的进程）
//
//系统调用	描述
//fork	fork创造的子进程是父进程的完整副本，复制了父亲进程的资源，包括内存的内容task_struct内容
//vfork	vfork创建的子进程与父进程共享数据段,而且由vfork()创建的子进程将先于父进程运行
//clone	Linux上创建线程一般使用的是pthread库 实际上linux也给我们提供了创建线程的系统调用，就是clone
// from http://blog.csdn.net/gatieme
//
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>


int main(int vcount, char *vlues[]){
    int pid=-1;
    if((pid=vfork())==0){
        printf("这是父进程\n");
    } else
    {
        printf("这是子进程\n");
    }
    return 0;
}