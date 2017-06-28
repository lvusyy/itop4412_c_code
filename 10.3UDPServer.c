//
// Created by lvusyy on 6/28/17.
//



#include <sys/socket.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

struct sockaddr_in sockaddrmy;
struct sockaddr_in sockaddrin;

int sockinlen = sizeof(struct sockaddr_in);

int main() {
    int socketFD;
    socketFD = socket(PF_INET, SOCK_DGRAM, 0);

    if (socketFD == -1) {
        fprintf(stdout, "create sockect failed ");
        exit(EXIT_FAILURE);
    }
    bzero(&sockaddrmy, sizeof(sockaddrmy));
    sockaddrmy.sin_port = htons(3333);
    sockaddrmy.sin_family = AF_INET;
//    sockaddrmy.sin_addr.s_addr=inet_addr("0.0.0.0");
    sockaddrmy.sin_addr.s_addr = inet_addr("127.0.0.1");
    if (bind(socketFD, (struct sockaddr *) &sockaddrmy, sizeof(sockaddrmy)) == -1) {
        fprintf(stderr, "bind has failed %d\n", errno);
        close(socketFD);//maybe not needed
        exit(EXIT_FAILURE);
    }


    while (1) {


        char buf[256];
        bzero(buf, 255);
        buf[255] = '\0';
        if (recvfrom(socketFD, buf, 255, 0, (struct sockaddr *) &sockaddrin, &sockinlen) == -1) {
            int errNO1 = errno;
            fprintf(stderr, "recvfrom failed %d\n", errNO1);
            if (errNO1 == 88) {
                sleep(1);
                continue;
            } else {
                exit(EXIT_FAILURE);
            }
        }
        printf("recive from %s:%d Data:%s\n", inet_ntoa(sockaddrin.sin_addr), sockaddrin.sin_port, buf);

        if (strcmp(buf, "end") > 0) {
            close(socketFD);
            printf("fond end head ...so exit\n");
            break;
        }

        sleep(1);
        strcpy(buf, "hello ...udp....");
        if (sendto(socketFD, buf, strlen(buf), 0, (struct sockaddr *) &sockaddrin, &sockinlen) == -1) {
            fprintf(stderr, "sendto Client %s:%d failed\t %d \n", inet_ntoa(sockaddrin.sin_addr), sockaddrin.sin_port,
                    errno);
//            exit(EXIT_FAILURE);
        }
    }

    return 0;
}