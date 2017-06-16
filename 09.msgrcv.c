//
// Created by lvusyy on 6/16/17.
//

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>

struct msg_st {
    long int msg_type;
    char text[BUFSIZ];
};

int main(void) {
    int running = 1;
    int msgid = -1;
    struct msg_st data;
    long int msgtype = 0;//注意1


    //建立消息队列
    msgid = msgget((key_t) 889988, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);

    }

    //从队列中获取消息，知道遇到end消息为止
    while (running) {
        if (msgrcv(msgid, (void *) &data, BUFSIZ, msgtype, 0) == -1) {
            fprintf(stderr, "msgrcv failed with errno:%d\n", errno);
            exit(EXIT_FAILURE);
        }
        printf("接受消息: %s\n", data.text);
        if (strncasecmp(data.text, "end", 3) == 0) {
            running = 0;
            printf("数据已经接受完成\n");
            if (msgctl(msgid, IPC_RMID, 0) == -1) {
                fprintf(stderr, "删除消息队列出错\n");
                exit(EXIT_FAILURE);
            }
        }
        usleep(300);
    }
    exit(EXIT_SUCCESS);
}