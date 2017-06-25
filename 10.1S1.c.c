//
// Created by lvusyy on 6/25/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdio.h>

int main(void) {
    int strbuflen = 128;
    int server_socketfd, client_socketfd;
    int server_len, client_len;
    struct sockaddr_un server_address;
    struct sockaddr_un client_address;

    //remove old socket link file

    unlink("server_socket");
    server_socketfd = socket(AF_UNIX, SOCK_STREAM, 0);

    //named sockect

    server_address.sun_family = AF_UNIX;
    strcpy(server_address.sun_path, "server_socket");
    server_len = sizeof(server_address);
    bind(server_socketfd, (struct sockaddr *) &server_address, server_len);

    //liste
    char ch[strbuflen];
    listen(server_socketfd, 5);
    while (1) {

        printf("server waiting\n");
        client_len = sizeof(client_address);
        client_socketfd = accept(server_socketfd, (struct sockaddr *) &client_address, &client_len);
        read(client_socketfd, ch, strbuflen);
        printf("recive %s\n", ch);
        write(client_socketfd, ch, strbuflen);
        close(client_socketfd);
        if (strncmp(ch, "end", 3) > 0) {
            break;
        }
    }

    return 0;
}
