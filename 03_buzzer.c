//
// Created by lvusyy
// 测试开发板蜂鸣器
//

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define  BUZZER_STATUS_C 2

int main(int argc, char *argv[]) {
    char *buzzer_ctl = "/dev/buzzer_ctl";
    int fd, ret, buzzer_c;

    buzzer_c = BUZZER_STATUS_C;

    printf("*****开始*****\n");

    if (atoi(argv[1]) >= buzzer_c) {
        printf("蜂鸣器只支持 开(1)或关(0) 两种状态\n");
        exit(1);
    }

    if ((fd = open(buzzer_ctl, O_NDELAY | O_RDWR | O_NOCTTY)) < 0) {
        printf("蜂鸣器打开失败!");
        exit(1);
    }

    //第二个参数不使用,传递任何值都可以. 但是必须传递
    ret = ioctl(fd, atoi(argv[1]), 0);
    close(fd);

    return 0;
}