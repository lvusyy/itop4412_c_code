//lvusyy@gmail.com
//itop 4412 练习代码
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

#define LED_NUM 2
#define LED_C_bit 2

//利用ioctl 控制开发板小灯亮灭
//参数1:小灯编号 参数2:开关状态
int main( int argc ,char *argv[]){
    int fd,led_num,led_c_bit;
    char *leds="/dev/leds";

    led_num=LED_NUM;
    led_c_bit=LED_C_bit;
    printf("参数1:小灯编号 参数2:开关状态\n");
    if(atoi(argv[2])>=led_c_bit){
        printf("开关状态必须是0或1\n");
        exit(1);
    }
    if(atoi(argv[1])>= led_num){
        printf("小灯编号只支持0或1 \n");
        exit(1);
    }

    if((fd=open(leds,O_NDELAY|O_RDWR|O_NOCTTY))<0){
        printf("open %s failed\n",leds);
    }
    else{
        ioctl(fd,atoi(argv[2]),atoi(argv[1]));

        char *str_stat="打开";
        if (atoi(argv[2])<=0){
            str_stat="关闭";
        }
        printf("*** %s号小灯 %s\n",argv[1],str_stat);
    }
    close(fd);
    return 0;
}
