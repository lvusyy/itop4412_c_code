//
// Created by lvusyy on 6/25/17.
//


//inet 链接方式　ｃｌｉｅｎｔ

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(int argc, char *argv[]) {
    int socktfd;
    int len;
    struct sockaddr_in address;
    int result;
    int strbuflen = 128;
    char ch[strbuflen];

    strncpy(ch, "hello sockect ... test!!!!\n", sizeof("hello sockect ... test!!!!\n"));

    if (argc >= 2)
        strcpy(ch, argv[1]);

    socktfd = socket(AF_INET, SOCK_STREAM, 0);

    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9999;
    address.sin_family = AF_INET;
    len = sizeof(address);


    result = connect(socktfd, (struct sockaddr *) &address, len);
    if (result == -1) {
        perror("opps:client1");
        exit(1);
    }

    write(socktfd, ch, strbuflen);
    read(socktfd, ch, strbuflen);
    printf("string form server=%s\n", ch);
    close(socktfd);

    return 0;
}