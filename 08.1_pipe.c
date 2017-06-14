//
// Created by OthinkY on 6/15/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void){
    int filedes[2]={0,0};
    //pipe建立管道之后 会把读取的句柄放到filedes[0]中,写入的放入[1]中.
    if(-1==pipe(filedes)){
        printf("建立管道出错.\n");
    } else if (fork()>0){
        //父进程
        char s[]="你好,子进程\n";
        write(filedes[1],s, sizeof(s));
    } else
    {
        //子进程
        char buff[80];
        read(filedes[0],buff, sizeof(buff));
        printf("接收到父进程发来的信息:%s\n",buff);
    }

    //这里也会被上面的子进程执行的哦....
    printf("****** popen ****** %d\n",getpid());
    FILE *fp;
    char buffer[80];
    //popen 成功返回文件句柄 参数1 可执行文件 2操作类型 r 读取,w写入
    fp=popen("cat /etc/passwd","r");
    if(fp==NULL){
        printf("popen fail\n");
    } else{
        fgets(buffer, sizeof(buffer),fp);
        printf("%s %d\n", buffer,getpid());
        pclose(fp);
    }

    return 0;
}