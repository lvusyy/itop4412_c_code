//
// Created by lvusyy on 6/25/17.
//

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int socktfd;
    int len;
    struct sockaddr_un address;
    int result;
    int strbuflen = 128;
    char ch[strbuflen];

    if (argc >= 2)
        strcpy(ch, argv[1]);

    socktfd = socket(AF_UNIX, SOCK_STREAM, 0);

    address.sun_family = AF_UNIX;
    strcpy(address.sun_path, "server_socket");
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