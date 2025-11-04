#include<stdio.h>
#include<stdlib.h>

typedef int DataType;
struct List
{
    int Max;
    int n;
    DataType* elem;
};
typedef struct List* SeqList;

SeqList SetNullList_Seq(int m)/*创建空顺序表*/
{
    SeqList slist = (SeqList)malloc(sizeof(struct List)); /*申请结构体List空间*/
    if (slist != NULL)
    {
        slist->elem = (DataType*)malloc(sizeof(DataType) * m);
        /*申请顺序表空间，大小为m个DataType空间*/
        if (slist->elem) {
            slist->Max = m;/*顺序表的最大值*/
            slist->n = 0; /*顺序表长度赋值为0*/
            return(slist);
        }
        else free(slist);
    }
    printf("out of space!!\n");
    return NULL;
}

int IsNullList_seq(SeqList slist)/*判断顺序表是否为空*/
{
    return(slist->n == 0);
}

int InsertPre_seq(SeqList slist, int p, DataType x)
/*在线性表slist的p位置之前插入x*/
{
    int q;
    if (slist->n >= slist->Max) { /*顺序表满溢出*/
        printf("overflow");
        return(0);
    }
    if (p<0 || p>slist->n) {  /*不存在下标为p的元素*/
        printf("not exist!\n");
        return(0);
    }
    for (q = slist->n - 1; q >= p; q--)/*插入位置以及之后的元素后移*/
        slist->elem[q + 1] = slist->elem[q];
    slist->elem[p] = x;  /*插入元素x*/
    slist->n = slist->n + 1;  /*顺序表长度加1*/
    return(1);
}

void print(SeqList slist)
{
    int i;
    for (i = 0; i < slist->n; i++)
        printf("%d ", slist->elem[i]);
}
int DelIndex_seq(SeqList slist, int p) //删除下标为p的元素
{
    int q;
    if (p < 0 || p >= slist->n) {//不存在下标为p的元素
        printf("Not exist\n");
        return 0;
    }
    for (q = p; q < slist->n - 1; q++) { //p位置之后的元素向前移动
        slist->elem[q] = slist->elem[q + 1];
    }
    slist->n = slist->n - 1; //顺序表长度减1
    return 1;
}

int binsearch(SeqList slist, int key, int* pos) {
    int index = 1;//比较次数
    int mid;
    int low = 0;
    int high = slist->n - 1;
    while (low <= high)
    {
        mid = (low + high) / 2;
        if (slist->elem[mid] == key) {
            *pos = mid;
            //输出查找成功比较的次数，和元素所在的位置
            printf("%d,%d", index, mid);
            return 1;
        }
        else if (slist->elem[mid] > key)
            high = mid - 1;
        else     low = mid + 1;
        index++;
    }
    *pos = low;
    //输出查找失败比较的次数和元素可以插入的位置
    printf("%d,%d", index - 1, *pos);
    return -1;
}

int main()
{
    SeqList alist;
    int  len, i, x;
    int  key, pos;
    //输入最大元素个数
    alist = SetNullList_Seq(20);
    //输入实际存储元素的个数
    if (alist != NULL) {
        scanf("%d", &len);
    }
    //输入具体元素
    for (i = 0; i < len; i++) {
        scanf("%d", &x);
        InsertPre_seq(alist, i, x);
    }
    //输入要查找的元素
    scanf("%d", &key);
    binsearch(alist, key, &pos);
    return 0;
}

/*
zsh 正确的运行示例：

# 方式1：heredoc（推荐）
run ./f1.app << 'EOF'
10
1 2 3 4 5 6 7 8 9 10
10
EOF

# 方式2：管道
printf "10\n1 2 3 4 5 6 7 8 9 10\n10\n" | ./f1.app

# 方式3：输入重定向
cat > input.txt << 'EOF'
10
1 2 3 4 5 6 7 8 9 10
10
EOF
./f1.app < input.txt
*/