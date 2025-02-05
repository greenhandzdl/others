#include<stdio.h>

int main(void){
    int i = 0;//可以修改i的类型
    FILE *p;
    if((p = fopen("print_stor_proof.dat","w"))==NULL){
        perror("fopen");
        return -1;
    };
    label:
    puts("请输入一个int类型数据，接下来会给出相应储存：");
    printf("int 占用%zd位\n",sizeof i);
    scanf("%d",&i);
    fwrite(&i,sizeof(int),1,p);
    if(getchar()!=EOF)
        goto label;
    fclose(p);
    return 0;
}
/*
输入:1234 2231(od -x)
输出: 04d2    0000    08b7    0000    08b7    0000
*/