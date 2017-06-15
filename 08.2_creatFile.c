//
// Created by OthinkY on 6/15/2017.
//

//创建大量数据文件.

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

void mk2bigfile(FILE *fd, const char strTemple[]);

int main(void){
const char strTemple[]="测试生成大量文件内容.";
unsigned int count=65535*2-1;
    const char filepath[]="date.txt";
    FILE *fd;
    if((fd=fopen(filepath,"a+"))==NULL){
        printf("打开文件错误,错误码:%d\n",errno);
    } else {
        while (count--) {
            mk2bigfile(fd, strTemple);
        }
        fclose(fd);
        printf("文件生成完成.文件名:%s\n",filepath);
    }

}

void mk2bigfile(FILE *fd, const char strTemple[]){
    unsigned int i=0;
    for(i=0;i<=strlen(strTemple)-1;i++){
        fputc(strTemple[i],fd);
    }
}