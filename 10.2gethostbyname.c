//
// Created by lvusyy on 6/26/17.
//
// 根据主机名称返回ＩＰ地址

#include <netdb.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main(int argn, char *argv[]) {

    struct hostent *hostinfo;
    char host[256];
    if (argn > 1) {

        strcpy(host, argv[1]);
    } else {
        strcpy(host, "localhost");
    }

    //find host address
    hostinfo = gethostbyname(host);
    if (!hostinfo) {
        fprintf(stderr, "no host:%s\n", host);
        exit(1);
    }
    char **addrs;
    addrs = hostinfo->h_addr_list;//list ...
    printf("%s,%s\n", host, inet_ntoa(*(struct in_addr *) *addrs));

    return 0;
}