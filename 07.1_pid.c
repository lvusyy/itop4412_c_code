//
// Created by OthinkY on 5/26/2017.
//

#include <unistd.h>
#include <stdio.h>
#include<sys/time.h>
#include<sys/resource.h>
#include <stdlib.h>

void exitCallBack(int status, char *arg);

void main(void) {
    printf("Pid:%d\n", getpid());
    printf("Parent Pid:%d\n", getppid());
//    printf("%d\n",getpriority(PRIO_PROCESS,getpid()))
    //-20 20 之间,其中只有超级用户才能使用负值
    printf("修改进程的优先级:%d\n", nice(-20));

    char *str_ = "我是被传递的参数";
    on_exit((void *) exitCallBack, (void *) str_);
    //做些其他的事情在这里
    system("ping 127.0.0.1 -c 3");
    //512会传递给回调函数exitCallBack 的参数 status
    exit(512);

    printf("\n-----------------exec-----------------\n");
    sleep(1);
    //exec 执行成功是不返回的,也就是说下面的代码都不会执行了
    if (-1 == exec("./ds", "我是传递的参数", (void *) NULL))
        printf("exec 执行出错\n");

    printf("如果上面执行成功,你将不会看到我.\n");


}

void exitCallBack(int status, char *arg) {
    printf("退出的回调函数被调用\n");
    printf("exit退出代码:%d\n", status);
    printf("参数:%s\n", arg);

}

