//
// Created by lvusyy on 6/25/17.
//

//ｉｎｅｔ　链接方式　　ｓｅｒｖｅｒ

#include <sys/types.h>
#include <sys/socket.h>
//#include <string.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main(void) {
    int strbuflen = 128;
    int server_socketfd, client_socketfd;
    int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;

    server_socketfd = socket(AF_INET, SOCK_STREAM, 0);

    //ip port
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("0.0.0.0");
    server_address.sin_port = 9999;
    server_len = sizeof(server_address);
    bind(server_socketfd, (struct sockaddr *) &server_address, server_len);

    //liste
    char ch[strbuflen];
    listen(server_socketfd, 5);
    while (1) {

        printf("server waiting\n\n");
        client_len = sizeof(client_address);
        printf("******************\n");
        client_socketfd = accept(server_socketfd, (struct sockaddr *) &client_address, &client_len);
        printf("new Client:%s:%d\n", inet_ntoa(client_address.sin_addr), (int) client_address.sin_port);
        read(client_socketfd, ch, strbuflen);
        printf("receive %s\n", ch);
        write(client_socketfd, ch, strbuflen);
        printf("close client :%s:%d\n", inet_ntoa(client_address.sin_addr), (int) client_address.sin_port);
        close(client_socketfd);
        printf("******************\n\n\n");
        if (strcmp(ch, "end") == 0) {
            break;
        }
    }

    close(server_socketfd);
    return 0;
}
