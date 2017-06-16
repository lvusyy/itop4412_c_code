//
// Created by OthinkY
//
// 结构体 位宽
//共用体 (同时只能 同时只能保证结构体内一个属性正常使用)

#include <stdio.h>
#include <string.h>

int main(int n, char *arrs[]) {
    struct bw {
        //指定位宽 二进制的宽度 是3个 也就是说 存储的二进制宽度3 也就是:0b111  10进制就是7
        unsigned int widthValidated:3;
        // 存储的二进制宽度5 也就是:0b11111  10进制就是31
        unsigned int hightValidated:5;
    };

    struct bw xx;
    //printf结果
    xx.widthValidated = 7;    //widthValidated 7
    xx.hightValidated = 32;   //widthValidated 0

    printf("widthValidated %d\n", xx.widthValidated);
    printf("widthValidated %d\n", xx.hightValidated);

    //*****************************************************************
    //共同体
    // 这个结构体内,同时只能保证结构体内一个属性正常使用. 如果给person.age赋值之后 其它属性的值不能保证
    union uperson {
        int age;
        float weight;
        char name[50];
    } person;

    person.age = 5;
    printf("age:%d\n", person.age);
    person.weight = 5.22;
    printf("weight:%f\n", person.weight);
    strcpy(person.name, "花花虎");
    printf("name:%s\n", person.name);
    //
    //age:5
    //weight:5.220000
    //name:花花虎
    //
    person.age = 5;
    person.weight = 5.2;
    strcpy(person.name, "小苗苗");
    printf("age:%d,weight:%f,name:%s\n", person.age, person.weight, person.name);
    //age:-393236251,weight:-5428492281570934657122304.000000,name:小苗苗

    return 0;
}