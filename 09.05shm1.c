//
// Created by lvusyy on 6/25/17.
//
//消费者

// 创建共享内存．　ｋｅｙ共享内存段命名　ｓｉｚｅ　以字节为单位　指定需要共享的内存容量　ｓｈｍｆｌｇ　包含９个ｂｉｔ为权限标志　和文件ｍｏｄｅ标志一样
//int shmget(key_t key, size＿t size, int shmflg )；
//shmat 讲共享内存链接到一个进程地址空间中．
//void *shmat tint shm—id, const void *shm_addr, Int ahmfIg);
//shmdt 讲共享内容从当前内存中分离，参数是ｓｈｍａｔ返回的内存指针．
//shmctl　shm_id 是shmget返回的共享内存表示符　command 要采取的动作　
// shmid_ds 它指向包含共亨内存模式和坊问权限的结构，

//int shmctl(int shm_id,int command ,struct shmid_ds *buf);
//shmid_ds结构

//
//struct  shmid_ds｛
//    uid_t shm_perm.uid;
//    uid_t  shm_perm.gid;
//    uid_t  shm_perm.mode;
//};

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <sys/shm.h>
#include "shm_com.h"

int main(void) {
    int running = 1;
    void *shared_memory = (void *) 0;
    struct shared_use_st *share_stuff;
    int shmid;

    srand((unsigned int) getpid());
    shmid = shmget((key_t) 1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);

    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    //访问共享内存
    shared_memory = shmat(shmid, (void *) 0, 0);
    if (shared_memory == (void *) -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }
    printf("内存附加在%X\n", (int) shared_memory);


    share_stuff = (struct shared_use_st *) shared_memory;
    share_stuff->written_by_you = 0;
    while (running) {
        if (share_stuff->written_by_you) {
            printf("你写了：%s\n", share_stuff->some_text);
            sleep(rand() % 4);
            share_stuff->written_by_you = 0;
            if (strncmp(share_stuff->some_text, "end", 3) == 0) {
                running = 0;
            }
        }
    }

    //分离内存
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    //
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl IPC_RMID faild\n");
        exit(EXIT_FAILURE);
    }
    return 0;

}