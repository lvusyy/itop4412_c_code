//
// Created by lvusyy on 6/25/17.
//
//生产者

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <sys/shm.h>

#include "shm_com.h"

int main() {

    int running = 1;
    void *shared_memroy = (void *) 0;
    struct shared_use_st *shared_stuff;
    char buffer[BUFSIZ];
    int shmid;

    shmid = shmget((key_t) 1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memroy = shmat(shmid, (void *) 0, 0);
    if (shared_memroy == (void *) -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("内存附加在：%X\n", (int) shared_memroy);
    shared_stuff = (struct shared_use_st *) shared_memroy;
    while (running) {
        while (shared_stuff->written_by_you == 1) {
            sleep(1);
            printf("waiting for client ..\n");
        }
        printf("Enter some text: ");
        fgets(buffer, BUFSIZ, stdin);

        strncpy(shared_stuff->some_text, buffer, TEXT_SZ);
        shared_stuff->written_by_you = 1;

        if (strncmp(buffer, "end", 3) == 0) {
            running = 0;
        }
    }

    if (shmdt(shared_memroy) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    return 0;

}

