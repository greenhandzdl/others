#include<stdio.h>
#include <stdlib.h>
#include <time.h>

//4位老师
#ifndef N
#define N 4
#endif

struct Member{
    int id;
    char name[20];
};
typedef struct Member Member;

void randomSeq(Member *, int);
int compare(const void *, const void *);
void printMember(Member *, int);

int main(void){
    srand((unsigned int)time(NULL));

    Member arr[N]={
        {.name="Liu"},
        {.name="Yang"},
        {.name="Zhang"},
        {.name="Wang"}
    };

    randomSeq(arr, N);
    qsort(arr, N, sizeof(Member), compare);

    printMember(arr, N);

    return 0;
}

void randomSeq(Member *arr, int n){
    for(int i=0; i<n; i++){
        arr[i].id=rand();
    }
}
int compare(const void *a, const void *b){
    return ((Member *)a)->id - ((Member *)b)->id;
}
void printMember(Member *arr,int n){
    for(int i=0; i<n; i++){
        printf("第%d位 %s老师参与会议\n", i+1 ,arr[i].name);
    }
}

// gcc main.c -o main.out &&./main.out