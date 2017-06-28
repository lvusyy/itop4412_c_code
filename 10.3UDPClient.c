//
// Created by lvusyy on 6/28/17.
//

#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>

int main(int argn, char *argv[]) {

    char sendstr[256];
    if (argn > 1) {
        strcpy(sendstr, argv[1]);
    } else {
        strcpy(sendstr, "默认的发送数据\0");
    }

    sendstr[255] = '\0';
    printf("%s\n", sendstr);
    int sockfd;
    struct sockaddr_in myaddr_in;
    int myaddrlen;
    myaddrlen = sizeof(struct sockaddr_in);
    bzero((void *) &myaddr_in, sizeof(myaddr_in));

    myaddr_in.sin_port = htons(3333);
    myaddr_in.sin_addr.s_addr = inet_addr("127.0.0.1");
    myaddr_in.sin_family = AF_INET;

    if ((sockfd = socket(PF_INET, SOCK_DGRAM, 0)) == -1) {
        fprintf(stderr, "socket create failed \n");
        exit(EXIT_FAILURE);

    }

    if (-1 == sendto(sockfd, sendstr, strlen(sendstr), 0, (struct sockaddr *) &myaddr_in, sizeof(myaddr_in))) {
        fprintf(stderr, "sendto failed %d\n", errno);
        exit(EXIT_FAILURE);
    }

    if (recvfrom(sockfd, sendstr, sizeof(sendstr), 0, (struct sockaddr *) &myaddr_in, &myaddrlen) == -1) {
        fprintf(stderr, "recvfrom failed\n");
        exit(EXIT_FAILURE);
    }

    printf("recive from %s:%d\t Data:%s\n", inet_ntoa(myaddr_in.sin_addr), myaddr_in.sin_port, sendstr);
    if (strcmp(sendstr, "end") > 0) {
        return 0;
    }

    close(sockfd);
    return 0;
}