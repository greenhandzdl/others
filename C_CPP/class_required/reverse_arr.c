#include<stdio.h>
#include <errno.h>
#include<ctype.h>
#include<stdlib.h>
#ifndef ARR_SIZE
#define ARR_SIZE 80
#endif

int inputToArr(char*,int);
void reverseArr(char*,int);
void swap(char* first, char* second);
int s_gets(char*,int,FILE*);//返回字符串最后地址
inline static void eatline(void);
static inline void arrIsEmptyErr(void);

int main(void){
    char arr[ARR_SIZE];
    int status = 0;
    ioloop:
        status = inputToArr(arr,ARR_SIZE);
        reverseArr(arr,status);
    goto ioloop;
    puts(arr);
    return 0;
}

int inputToArr(char* arr,int n){
    puts("Please enter a string(elements < 80),I will reverse it for you(leave blank for quit):");
    return s_gets(arr,n-1,stdin);
}
void reverseArr(char* arr,int n){
    if(n){
        if(n+1){
            //n的位置就说'\0'的位置
            for(int start = 0,end = n-1;start<=end;start++,end--){
                swap(&arr[start],&arr[end]);
            }
            
        }
        else{
            //首先定位'0'位置
            int i = 0;
            for(i=0;arr[i]!='\0';i++);
            for(int start = 0,end = i-1;start<=end;start++,end--){
                swap(&arr[start],&arr[end]);
            }
        }
    }else{
        atexit(arrIsEmptyErr);
        exit(EXIT_FAILURE);
    }
}

void swap(char* first, char* second) {
    if(*first != *second){
        *first ^= *second;
        *second ^= *first;
        *first ^= *second;
    }
}

int s_gets(char* arr,int n,FILE* p){
    //gets_s(arr,ARR_SIZE-1); C11 Support
    fgets(arr,n-1,p);
    for(int i=0;i<n;i++){
        if(arr[i]=='\n'){
            arr[i]='\0';
            return i;
        }
    }
    fprintf(stderr,"超出数组大小了，所以发生截断。");
    arr[n-1]='\0';
    eatline();
    return -1;//代表后面都被截断了
}
inline static void eatline(void){
    while(getchar()!='\n');
}
static inline void arrIsEmptyErr(void){
    fprintf(stderr,"数组为空，没有数据怎么处理？？");
}