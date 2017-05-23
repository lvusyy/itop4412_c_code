//
// Created by OthinkY on
// time sleep usleep 练习
//



#include <stdio.h>
#include <time.h>
#include <unistd.h>

int  main(int argn, char *argv[]){

    //休眠1秒
    sleep(1);
    //休眠1秒.=1000000微秒
    usleep(1000000);

    long int t_time;

    //返回UNIX时间戳 19700101 到现在的秒数
    // 不包括闰秒
    //UNIX时间戳的0按照ISO 8601规范为 ：1970-01-01T00:00:00Z.
    time(&t_time);
    printf("UTC Time :%12d\n",t_time);
    t_time=time(NULL);
    printf("UTC Time :%012d\n",t_time);
    return 0;

}