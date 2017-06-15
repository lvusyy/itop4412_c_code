//
// Created by OthinkY on 6/15/2017.
//


//把之前写入到管道中的数据写入到新的文件中..


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
    const int mode_t=O_RDONLY;
    int pipe_fd=-1;
    int date_fd=-1;

    char* buffer=(char*)malloc(PIPE_BUF+1);
    memset((void*)buffer,0, PIPE_BUF+1);

    pipe_fd=open(pathname,mode_t);
    date_fd=open("fiforeadfile.txt",O_WRONLY|O_CREAT,0644);
    if((pipe_fd==-1)||(date_fd==-1)){
        printf("打开文件时候出错 fifo或写出的文件\n");
        close(date_fd);//清理可能成功打开文件表述符
        close(pipe_fd);
        free(buffer);
        exit(EXIT_FAILURE);
    }
    int res=0;
    int bytes_w=0;
    do{
        //从管道读入数据到buffer
        res=read(pipe_fd,buffer,PIPE_BUF);
        bytes_w=write(date_fd,buffer,res);
        if((res<0)||(bytes_w<0)){
            printf("读取pipe或写入文件时候出错\n");
            free(buffer);
            close(date_fd);
            close(pipe_fd);
            exit(EXIT_FAILURE);
        }

    }
    while(res>0);

    free(buffer);
    close(date_fd);
    close(pipe_fd);
    printf("从pipe中读入的数据已经写入到:%s中\n","fiforeadfile.txt");
    return 0;
}