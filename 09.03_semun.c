//
// Created by lvusyy on 6/20/17.
//

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/sem.h>


#if defined(__GNU_LIBRARY__) && !defined(_SEM_SEMUN_UNDEFINED)
/* union semun is defined by including <sys/sem.h> */
#else
/* according to X/OPEN we have to define it ourselves */
union semun {
    int val;                    /* value for SETVAL */
    struct semid_ds *buf;       /* buffer for IPC_STAT, IPC_SET */
    unsigned short int *array;  /* array for GETALL, SETALL */
    struct seminfo *__buf;      /* buffer for IPC_INFO */
};
#endif


static int set_semvalue(void);

static void del_semvalue(void);

static int semaphore_p(void);

static int semaphore_v(void);


static int sem_id;

int main(int argc, char *argv[]) {

    int i;
    int pause_time;
    char op_char = 'O';

    //配置随机数种子
    srand((unsigned int) getpid());

    //获取／创造一个 消息列队
    sem_id = semget((key_t) 3333, 1, 0666 | IPC_CREAT);

    //根据参数的个数判断
    if (argc > 1) {
        if (!set_semvalue()) {
            fprintf(stderr, "初始化semaphore出错\n");
            exit(EXIT_FAILURE);
        }
        //设置操作模式为Ｘ
        op_char = 'X';
        sleep(2);
    }

    //循环１０次，进出临界区
    for (i = 0; i < 10; i++) {
        //设置Ｐ模式出错后退出
        if (!semaphore_p()) exit(EXIT_FAILURE);
        printf("%c", op_char);
        fflush(stdout);
        pause_time = rand() % 3;
        sleep(pause_time);
        printf("%c", op_char);
        fflush(stdout);
        //设置出临界区
        if (!semaphore_v()) exit(EXIT_FAILURE);

        pause_time = rand() % 2;
        sleep(pause_time);
    }

    printf("\n%d - finished\n", getpid());

    //初始化semaphore的人清理semvalue
    if (argc > 1) {
        sleep(10);
        del_semvalue();
    }

    return EXIT_SUCCESS;
}


static int set_semvalue(void) {

    union semun sem_union;

    sem_union.val = 1;
    if (semctl(sem_id, 0, SETVAL, sem_union) == -1) return (0);
    return (1);
}


static void del_semvalue(void) {

    union semun sem_union;

    if (semctl(sem_id, 0, IPC_RMID, sem_union) == -1)
        fprintf(stderr, "移除消息列队出错．\n");
}

static int semaphore_p(void) {

    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = -1;//
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "设置semaphore_p出错\n");
        return (0);
    }
    return (1);
}


static int semaphore_v(void) {

    struct sembuf sem_b;

    sem_b.sem_num = 0;
    sem_b.sem_op = 1;//v
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        fprintf(stderr, "设置为semaphore_v出错\n");
        return (0);
    }
    return (1);

}