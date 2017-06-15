//
// Created by OthinkY on 6/15/2017.
//


//把之前生成的文件写入到fifo管道中.


#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <limits.h>
#include <string.h>


int main(void){
    const char pathname[]="myfifoname";
    const int mode_t=O_WRONLY;
    const char datafilename[]="date.txt";//mmp data.txt 写错.找了半小时...大爷的.
    int pipe_fd=-1;
    int date_fd=-1;
    char buffer[PIPE_BUF+1];
    int bytes_send=0;

    unlink(pathname);
    if(access(pathname,F_OK)==-1&&(mkfifo(pathname,0777)!=0)){
        printf("创建fifo出错,也许已经存在\n");
    } else
    {
        //打开fifo和要写入的文件
        pipe_fd=open(pathname,mode_t);
        date_fd=open(datafilename,O_RDONLY);
        if((pipe_fd==-1)||(date_fd==-1)) {
            printf("fifo或data文件打开出错\n pipe_fd:%d,date_fd:%d",pipe_fd,date_fd);
            close(pipe_fd);//可能其中一个打开成功了
            close(date_fd);//所以退出之前全部关闭
            exit(EXIT_FAILURE);
        } else
        {
            int bytes_read=0;
            bytes_read=read(date_fd,buffer,PIPE_BUF);
//            printf("DEBUG:bytes_read : %d\n",bytes_read);
            buffer[bytes_read]='\0';//保证数据的有效性质截断无效数据
            while (bytes_read>0){
                int res=0;
                if(res=write(pipe_fd,buffer,bytes_read)==-1){
                    fprintf(stderr,"写pipe出错.");
                    exit(EXIT_FAILURE);
                }
                bytes_send+=res;
                bytes_read=read(date_fd,buffer,PIPE_BUF);
//                printf("DEBUG:bytes_read : %d\n",bytes_read);
                buffer[bytes_read]='\0';
            }
            //清理已经打开的文件
            close(pipe_fd);
            close(date_fd);
        }

    }
    printf(
            "all done! 一共写入了:%d字节\n",bytes_send
    );
    return 0;
}