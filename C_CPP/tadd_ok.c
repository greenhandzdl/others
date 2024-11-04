//#include<stdio.h>

/* Determine whether arguments can be added without overflow */
int tadd_ok(int x, int y);

int main(){
    //printf("%d",tadd_ok(1,1));
    return tadd_ok(1,1);//测试用例
}

int tadd_ok(int x, int y){
    //用于检测有符号运算是否产生溢出，如果不会则返回1
    int result = x + y;
    if(x<0 && y<0 && result > 0)
        return 0;
    else if (x>0 && y>0 && result <0)
        return 0;
    else return 1;  
}