#include <stdio.h>
#include <stdlib.h>

typedef struct ListNode {
    int val;
    struct ListNode *next;
} ListNode;

// 创建单链表
ListNode* create_linked_list(int arr[], int n) {
    ListNode dummy = {0, NULL};
    ListNode *current = &dummy;
    for (int i = 0; i < n; i++) {
        current->next = (ListNode*)malloc(sizeof(ListNode));
        current->next->val = arr[i];
        current->next->next = NULL;
        current = current->next;
    }
    return dummy.next;
}

// 将链表转换为数组
void linked_list_to_array(ListNode *head, int result[], int *size) {
    int idx = 0;
    while (head) {
        result[idx++] = head->val;
        head = head->next;
    }
    *size = idx;
}

// 插入节点
ListNode* insert_node(ListNode *head, int k, int d) {
    ListNode *dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->next = head;
    ListNode *current = dummy;

    // 表头插入
    if (k == 0) {
        ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
        new_node->val = d;
        new_node->next = dummy->next;
        dummy->next = new_node;
        head = dummy->next;
        free(dummy);
        return head;
    }

    // 找到第 k-1 个节点
    for (int i = 0; i < k && current->next; i++) {
        current = current->next;
    }

    // 检查是否越界
    if (current->next || k == 0) {
        ListNode *new_node = (ListNode*)malloc(sizeof(ListNode));
        new_node->val = d;
        new_node->next = current->next;
        current->next = new_node;
    }

    head = dummy->next;
    free(dummy);
    return head;
}

// 删除节点
ListNode* delete_node(ListNode *head, int k) {
    if (k == 0) return head; // 忽略删除第0个节点的操作

    ListNode *dummy = (ListNode*)malloc(sizeof(ListNode));
    dummy->next = head;
    ListNode *current = dummy;

    // 找到第 k-1 个节点
    for (int i = 0; i < k - 1 && current->next; i++) {
        current = current->next;
    }

    // 删除第 k 个节点
    if (current->next) {
        ListNode *temp = current->next;
        current->next = temp->next;
        free(temp);
    }

    head = dummy->next;
    free(dummy);
    return head;
}

int main() {
    int n, m;
    scanf("%d", &n);

    // 读取链表初始数据
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }

    // 创建链表
    ListNode *head = create_linked_list(arr, n);

    // 读取操作数量
    scanf("%d", &m);
    for (int i = 0; i < m; i++) {
        int op, k, d;
        scanf("%d", &op);
        if (op == 0) { // 插入操作
            scanf("%d %d", &k, &d);
            head = insert_node(head, k, d);
        } else if (op == 1) { // 删除操作
            scanf("%d", &k);
            head = delete_node(head, k);
        }
    }

    // 输出结果
    int result[100000], size = 0;
    linked_list_to_array(head, result, &size);
    for (int i = 0; i < size; i++) {
        printf("%d ", result[i]);
    }
    printf("\n");

    return 0;
}