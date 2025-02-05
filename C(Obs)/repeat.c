#include <stdio.h>

//用于打印后面参数的输出
int main(int argc,char *argv[]){
    if(argv[1]){
        for(unsigned int i = 1;argv[i] != NULL;i++)
            puts(argv[i]);
        return 0;
    }
    else
        printf("请检查下输入，一定要确保后面存在要输出的参数。\n");
        exit 0;
}