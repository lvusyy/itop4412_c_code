//
// Created by OthinkY
// ADC 读取
//

#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <stdlib.h>

int main(int argn, char *argv[]){
    int fd=0;
    char str_adc[]="/dev/adc";

    if(0>(fd=open(str_adc,O_NDELAY|O_RDWR|O_NOCTTY))){
        printf("打开ADC设备出错");
        exit(1);
    }

    char buffer[512];

    memset(buffer,0, sizeof(buffer));
    printf("输入任何字符后回车可查看当前ADC数值\n exit退出!\n");
    while (scanf("%s",&buffer[300])>=0){

        if (strcmp(&buffer[300],"exit")==0){
            printf("现在退出程序...\n");
            close(fd);
            exit(0);
        }
        int rlen=read(fd,buffer,10);
        sleep(0.05);
        if (rlen>0){
            printf("当前ADC数值:%d \n",(int)(atoi(buffer)*1000/4095));
        } else{
            printf("读取ADC失败!\n");
        }
    }

    close(fd);
    return  0;
}