//
// Created by lvusyy on 6/16/17.
//
//
//

#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#define MAX_TEXT 512

struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};

int main(void) {

    struct msg_st data;
    char buffer[BUFSIZ];

    int running = 1;

    //建立消息队列
    int msgid = msgget((key_t) 889988, 0666 | IPC_CREAT);
    if (msgid == -1) {
        fprintf(stderr, "msgget failed with error:%d\n", errno);
        exit(EXIT_FAILURE);
    }

    //开始想消息队列中写消息，知道写入end
    while (running) {
        //从终端读入字符串
        printf("发送消息: ");
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type = 1; //
        strncpy(data.text, buffer, BUFSIZ);

        //向队列发送数据
        if (msgsnd(msgid, (void *) &data, MAX_TEXT, 0) == -1) {
            fprintf(stderr, "msgsend failed\n");
            exit(EXIT_FAILURE);
        }


        if (strncasecmp(buffer, "end", 3) == 0) {
            running = 0;
            exit(EXIT_SUCCESS);
        }
        usleep(200);
    }

    exit(EXIT_SUCCESS);
}