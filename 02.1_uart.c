//
// Created by OthinkY
// urat 操作 (挺折腾的...) 写
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
#include <termios.h>

//           tcflag_t c_iflag;      /* input modes */
//           tcflag_t c_oflag;      /* output modes */
//           tcflag_t c_cflag;      /* control modes */
//           tcflag_t c_lflag;      /* local modes */
//           cc_t     c_cc[NCCS];   /* special characters */



int set_opt(int fd,int nSpeed,int nBit, char nEvent ,int nStop);

int main(int argn, char *argv[]){
    char *str_tty3="/dev/ttySAC3";
    int fd=0;
    if((fd=open(str_tty3,O_RDWR))<0){
        printf("端口打开失败\n");
        exit(1);
    }
    if (set_opt(fd,115200,8,'N',1)<0){
        printf("配置串口信息失败!\n");
        exit(1);
    }

    int a =0;
    for(a;a<10;a++)
    {
            if(write(fd,"你好串口.你二大爷好!,再见\n", strlen("你好串口.是二大爷好!,再见\n"))<0)
                printf("写入出错!\n");
            sleep(1);
            //read(fd,buff,bufflen);
    }
    printf("close tty3\n");
    close(fd);
    return 0;
}

int set_opt(int fd,int nSpeed,int nBit, char nEvent ,int nStop){
    struct termios newtio,oldtio;
    bzero(&oldtio, sizeof(oldtio));
    if (tcgetattr(fd,&oldtio)!=0){
        perror("获取波特率信息失败!\n");
        return  -1;
    }
    bzero(&newtio, sizeof(newtio));
//    memset(&newtio,0, sizeof(newtio));
    newtio.c_cflag |= CLOCAL|CREAD;
    newtio.c_cflag &= ~CSIZE;

    switch (nBit)
    {
        case 7:
            newtio.c_cflag|=CS7;
            break;
        case 8:
            newtio.c_cflag|=CS8;
            break;
    }

    switch (nEvent)
    {
        case 'O':
            newtio.c_cflag|=PARENB;
            newtio.c_cflag|=PARODD;
            newtio.c_iflag|=(INPCK|ISTRIP);
            break;
        case 'E':
            newtio.c_cflag|=(INPCK|ISTRIP);
            newtio.c_cflag|=PARENB;
            newtio.c_cflag&=~PARODD;
            break;
        case 'N':
            newtio.c_cflag&=~PARENB;
            break;
    }

    switch (nSpeed)
    {
        case 2400:
            cfsetispeed(&newtio,B2400);
            cfsetospeed(&newtio,B2400);
            break;
         case 4800:
            cfsetispeed(&newtio,B4800);
            cfsetospeed(&newtio,B4800);
            break;
         case 9600:
            cfsetispeed(&newtio,B9600);
            cfsetospeed(&newtio,B9600);
            break;
         case 115200:
            cfsetispeed(&newtio,B115200);
            cfsetospeed(&newtio,B115200);
            break;
        default:
            cfsetispeed(&newtio,B9600);
            cfsetospeed(&newtio,B9600);
            break;
    }

    if (nStop==1)
        newtio.c_cflag &= ~CSTOPB;
    else if (nStop==2)
        newtio.c_cflag|=CSTOPB;
        newtio.c_cc[VTIME]=0;
        newtio.c_cc[VMIN]=0;
        tcflush(fd,TCIFLUSH);

    if((tcsetattr(fd,TCSANOW,&newtio))!=0 )
    {
        perror("com口配置失败\n");
        return -1;
    }
    return 0;
}
