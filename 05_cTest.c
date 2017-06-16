//
// Created by OthinkY on 5/24/2017.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct Books {
    char title[50];
    char author[30];
    char subject[100];
    int book_id;
} book;

//只能在内部访问,
static int sum_(int a, int *b);

int main(int argn, char *argv[]) {
//    int *pb=(int*)malloc(sizeof(int));
// 	void *calloc(size_t nmemb，size_t size);
    int *pb = (int *) calloc(1, sizeof(int));
    *pb = 2017;
    printf("返回值:%d 指针b地址:%p,值:%d\n", sum_(11, pb), pb, *pb);
    free(pb);

    struct Books book1;

    strcpy(book1.title, "我的小伙伴");
    strcpy(book1.author, "lvusyy");
    book1.book_id = 1;
    strcpy(book1.subject, "记录了小伙伴的消失录");

    strcpy(book.title, "坏人,你跑啊!");
    strcpy(book.author, "lvusyy");
//    book.book_id=2;
    int i = 2;
    memcpy(&book.book_id, &i, sizeof(i));
    strcpy(book.subject, "小伙伴的成长见闻及发展");

    printf("book1.title:%s\n", book1.title);
    printf("book1.author:%s\n", book1.author);
    printf("book1.book_id:%d\n", book1.book_id);
    printf("book1.subject:%s\n", book1.subject);
    //*******************************************
    printf("*************************************\n");
    printf("book2.title:%s\n", book.title);
    printf("book2.author:%s\n", book.author);
    printf("book2.book_id:%d\n", book.book_id);
    printf("book2.subject:%s\n", book.subject);
    return 0;
}

//返回 a+b的值 其中b是指针类型,函数执行完成后指针b也会有a+b的值
static int sum_(int a, int *b) {
    int tmp = 0;
    tmp = a + *b;
//    *b+=a;

    memcpy(b, &tmp, sizeof(tmp));

    return tmp;
}