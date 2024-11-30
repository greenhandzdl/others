/*
2．简单有序链表的创建和查询修改
（1）建立一个单链表21	3	15	27	11	18，并输出该链表；
（2）输入序号n，查找序号为n的结点，并输出；
（3）输入值x，查找值为x的结点，并输出；
（4）插入结点: 输入序号n和值x。在序号为n的结点后插入x，并输出该链表；
（5）删除结点: 输入序号n，册除序号为n的结点，并输出该链表。
*/

#include <stdio.h>
#include <stdlib.h>

struct node {
    int data;
    struct node *next;
};


// 符合题目1要求，建立该链表
struct node* node_init(void) {
    const static int data[] = {21, 3, 15, 27, 11, 18};
    struct node *p = malloc(sizeof(struct node)); // 当前节点
    struct node *head = p; // 头节点
    for (int i = 0; i < sizeof(data) / sizeof(data[0]); i++) {
        p->data = data[i];
        if (i < sizeof(data) / sizeof(data[0]) - 1) {
            p->next = malloc(sizeof(struct node)); // 下一个节点
            p = p->next;
        } else {
            p->next = NULL;
        }
    }
    return head;
}

// 符合题目2要求，查找链表
struct node* node_search(struct node *head, int n) {
    struct node *p = head;
    int i = 1;
    while (p != NULL) {
        if (i == n) {
            return p;
        }
        p = p->next;
        i++;
    }
    return NULL;
}
// 符合题目3要求，查找链表元素是否存在
int node_query(struct node *head, int n){
    struct node *p = head;
    int i = 1;
    while (p != NULL) {
        if (p->data == n) {
            return i;
        }
        p = p->next;
        i++;
    }
    return 0;
}
int node_insert(struct node *head, int n,int x){
    struct node *p = head;
    int i = 1;
    while (p != NULL) {
        if (i == n) {
            struct node *q = malloc(sizeof(struct node));//没有考虑内存分配失败情况
            q->data = x;
            q->next = p->next;
            p->next = q;
            return 1;
        }
        p = p->next;
        i++;
    }
    return 0;
}
void node_print(struct node *head) {
    struct node *p = head;
    while (p != NULL) {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}
int node_delete(struct node *head, int n) {
    struct node *p = head;
    int i = 1;
    while (p != NULL) {
        if (i == n) {
            struct node *q = p->next;
            p->next = q->next;
            free(q);
            return 1;
        }
        p = p->next;
        i++;
    }
    return 0;
}


int main(void) {
    struct node *head = node_init();//操作1
    struct node *p;
    int i = 0;
    //操作2
    if ((p = node_search(head, 1))) {
        printf("查找成功 %d\n", p->data);
    } else {
        printf("查找失败\n");
    }
    //操作3
    if (i = (node_query(head, 21))) {
        printf("查找成功 %d\n", i);
    } else {
        printf("查找失败\n");
    }
    //操作4
    if(node_insert(head, 1, 1111))
        node_print(head);
    //操作5
    if(node_delete(head, 1))
        node_print(head);//越界不会被删除，所以不会被打印
    return 0;
}

// gcc main2.c -o main2.out && ./main2.out