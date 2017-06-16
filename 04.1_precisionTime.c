//
// Created by lvusyy
//


// 计算 指定函数的运行时间

#include <stdio.h>
#include <time.h>
#include<sys/time.h>

void dosomething();

int main(int v_n, char *v_values[]) {

//    int gettimeofday ( struct timeval * tv ,  struct timeval * tz )
    struct timeval tv_s, tv_e;
    struct timezone tz;

    if (-1 == gettimeofday(&tv_s, &tz)) {
        printf("获取当前时间出错. 函数:gettimeofday\n");
    }
    dosomething();
    if (-1 == gettimeofday(&tv_e, &tz)) {
        printf("获取当前时间出错. 函数:gettimeofday\n");
    }
    //tv_e.tv_usec 整的我有点郁闷了 是秒零N微秒
    printf("一共浪费了:%fs\n",
           (float) ((tv_e.tv_sec * 1000000 + tv_e.tv_usec) - (tv_s.tv_sec * 1000000 + tv_s.tv_usec)) / 1000000);

    return 0;
}


void dosomething() {
    unsigned int a = 0;
    for (a = 0; a < 65535 * 2; a++) {
        if (a == 65535 * 2 - 996) {
            printf("马上就结束了\n");
            usleep(500000);
        }
    }
}

