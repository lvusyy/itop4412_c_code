//
// Created by lvusyy on 6/17/17.
//


#include <signal.h>
#include <stdio.h>
#include <unistd.h>

void signalhandler(void) {
    printf("signalHandlerSay Hello\n");
}

int main(void) {

    //设置信号处理方式．为alarm触发　触发后回调函数　signalhandler
    signal(SIGALRM, (__sighandler_t) signalhandler);
    printf("3秒后会触发　signalhandler　函数\n");
    //设置３秒后触发alarm 信号
    alarm(3);
    int i = 0;

    do {
        printf("sleep:%d次\n", i);
        sleep(1);
        i++;
    } while (i < 6);

    return 0;
}