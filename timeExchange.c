//
// Created by OthinkY on 2017/5/24.
//
#include <stdio.h>
#include <time.h>
#include <unistd.h>

//           struct tm {
//               int tm_sec;         /* seconds */
//               int tm_min;         /* minutes */
//               int tm_hour;        /* hours */
//               int tm_mday;        /* day of the month */
//               int tm_mon;         /* month */
//               int tm_year;        /* year */
//               int tm_wday;        /* day of the week */
//               int tm_yday;        /* day in the year */
//               int tm_isdst;       /* daylight saving time */
//           };
struct tm *t;
int main(int n, char *values[]){

    long int time_p=0;

    time(&time_p);

    printf("Ctime is :%s\n",ctime(&time_p));
    //struct tm *localtime(const time_t * timep);
    //函数说明
    //localtime()将参数timep所指的time_t结构中的信息转换成真实世界所使用的时间日期表示方法，然后将结果由结构tm返回。结构tm的定义请参考gmtime()。此函数返回的时间日期已经转换成当地时区。
    t=localtime(&time_p);
    //time_t mktime(strcut tm * timeptr);
    //mktime()用来将参数timeptr所指的tm结构数据转换成从公元1970年1月1日0时0分0 秒算起至今的UTC时间所经过的秒数。
    time_t time2=mktime(t);
    printf("转换为UNIX时间戳 %010d\n",time2);
    //asctime()将参数timeptr所指的tm结构中的信息转换成真实世界所使用的时间日期表示方法，然后将结果以字符串形态返回。此函数已经由时区转换成当地时间，
    char *strctime= asctime(gmtime(&time_p));
    printf("asctime %s\n",strctime);
    return 0;

}