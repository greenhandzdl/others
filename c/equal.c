//测试输出 #include<stdio.h>

int equa(int32_t a,int32_t b);

int main(){
    int32_t a=1111,b=1111;
    //测试  printf("%d",equa(a,b));
    return equa(a,b);
}

int equa(int32_t a,int32_t b){
    /**
     * 作用：对比两个int是否相等，如果相等则返回1，不想等返回0
     */
    return !(a^b);
}