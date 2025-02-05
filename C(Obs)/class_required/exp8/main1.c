// 输入若干学生的信息（学号、姓名、成绩），当输入学号为0时结束，用单向链表组织这些学生信息后，再按序输出。
// gcc main1.c -o main1.out && ./main1.out
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stud_node {
    int num;
    char name[20];
    int score;
    struct stud_node *next;
};

int main() {
    struct stud_node *head, *tail, *p;
    int num, score;
    char name[20];
    int size = sizeof(struct stud_node);
    head = tail = NULL;

    printf("input num,name and score:\n");
    scanf("%d", &num);

    while (num != 0) {
        p = malloc(size);//p是当前的最新指针
        if (p == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return 1;
        }
        scanf(" %s%d", name, &score);
        p->num = num;
        strcpy(p->name, name);
        p->score = score;
        p->next = NULL;

        if (head == NULL) {
            head = p;
        } else {
            tail->next = p;
        }
        tail = p;//tail之前处理的都是上一个指针

        scanf("%d", &num);
    }

    for (p = head; p != NULL; p = p->next) {
        printf("%d\t%s\t%d\n", p->num, p->name, p->score);
    }

    return 0;
}