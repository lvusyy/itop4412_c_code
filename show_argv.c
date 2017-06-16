//
// Created by OthinkY on 5/26/2017.
//
#include <stdio.h>

int main(int argn, char *argv[]) {
    if (argn > 1)
        printf("传递过来的参数是:%s\n", argv[1]);
    return 0;
}