//对于指向 指针数组 的指针是这么用
int *(arr[3])={ &a, &b, &e };
int** p=arr;
//可以这么使用
*p[0];//区别是指向的可能并不是连续地址

//同样，一个指向 数组 的指针
int (*arr) [3] = ARR;
int** p = arr;
//可以这么使用
*p[0];