//
// Created by OthinkY on 5/24/2017.
//
//权限相关


#include<sys/types.h>
#include<sys/stat.h>
#include <stdio.h>

/*
 * 定义函数
int chmod(const char * path,mode_t mode);
函数说明
chmod()会依参数mode 权限来更改参数path 指定文件的权限。
参数
mode 有下列数种组合
S_ISUID 04000 文件的（set user-id on execution）位
S_ISGID 02000 文件的（set group-id on execution）位
S_ISVTX 01000 文件的sticky位
S_IRUSR（S_IREAD） 00400 文件所有者具可读取权限
S_IWUSR（S_IWRITE）00200 文件所有者具可写入权限
S_IXUSR（S_IEXEC） 00100 文件所有者具可执行权限
S_IRGRP 00040 用户组具可读取权限
S_IWGRP 00020 用户组具可写入权限
S_IXGRP 00010 用户组具可执行权限
S_IROTH 00004 其他用户具可读取权限
S_IWOTH 00002 其他用户具可写入权限
S_IXOTH 00001 其他用户具可执行权限
 */


int main(int a, char *avs[]) {

    if (0 != chmod("/etc/passwd", 0644))
        printf("设置权限失败!\n");

//int fchmod(int fildes,mode_t mode);
//函数说明
//fchmod()会依参数mode权限来更改参数fildes所指文件的权限。参数fildes为已打开文件的文件描述词。参数mode请参考chmod（）。
}