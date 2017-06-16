//
// Created by OthinkY on 5/24/2017.
//

#include<sys/stat.h>
#include<unistd.h>
#include <errno.h>
#include <stdio.h>
//struct stat
//{
//    dev_t st_dev; /*device*/
//    ino_t st_ino; /*inode*/
//    mode_t st_mode; /*protection*/
//    nlink_t st_nlink; /*number of hard links */
//    uid_t st_uid; /*user ID of owner*/
//    gid_t st_gid; /*group ID of owner*/
//    dev_t st_rdev; /*device type */
//    off_t st_size; /*total size, in bytes*/
//    unsigned long st_blksize; /*blocksize for filesystem I/O */
//    unsigned long st_blocks; /*number of blocks allocated*/
//    time_t st_atime; /* time of lastaccess*/
//    time_t st_mtime; /* time of last modification */
//    time_t st_ctime; /* time of last change */
//};


int main(int argn, char *argv[]) {
    struct stat mstat;
    if (0 != stat("/etc/passwd", &mstat)) {
        switch (errno) {
            case ENOENT:
                printf("参数file_name指定的文件不存在\n");
                break;
            case ENOTDIR :
                printf("路径中的目录存在但却非真正的目录\n");
                break;
            case ELOOP  :
                printf("欲打开的文件有过多符号连接问题，上限为16符号连接\n");
                break;
            case EFAULT :
                printf("参数buf为无效指针，指向无法存在的内存空间\n");
                break;
//            case EACCESS :
//                printf("存取文件时被拒绝\n");
//                break;
            case ENOMEM   :
                printf("核心内存不足\n");
                break;
            case ENAMETOOLONG  :
                printf("参数file_name的路径名称太长\n");
                break;
            default:
                break;

        }
    } else printf("文件inode:%d st_size:%d\n", mstat.st_ino, mstat.st_size);
    return 0;
}