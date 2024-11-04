// g++ max_aver_min.cpp -o max_aver_min.out && ./max_aver_min.out
//随即产生N 个正整数（10 <	Ν	≤20 ）存入数组 a 中，输出 a 中的最大值，最小值及求出其平均值（保留两位小数）。

#include<iostream>
#include<ctime> //for seed


const unsigned int N = 20;
static int a[N];


static unsigned int seeds;
inline void srand(void);
int rand(void);

void arr_init(void);
void arr_print(void);

int main(void){
    arr_init();
    arr_print();
}

inline void srand(void){
    extern unsigned int  seeds;
    seeds += (int)time(nullptr);//从time_t到int类型强转换
}
int rand(void){
    extern unsigned int seeds;
    static unsigned int rand_num (0);
    srand();
    
    rand_num +=  seeds*INT_MAX;
    
    return rand_num % 100;//返回0～100的随机数
}

void arr_init(void){
    for(int i=0;i<N;++i)
        a[i] = rand();
}
void arr_print(void){
    //顺带着定义一下求最大和最小吧
    int aver (0),tot(0);
    int max(0),min(0);
    for(int i=0;i<N;++i){
        std::cout << "第" << i+1 << "位元素是：" << a[i] <<std::endl;
        if(a[i]>a[max])
            max=i;
        if(a[i]<a[min])
            min=i;
        tot+=a[i];
    }
    std::cout << "最大数是第" << max+1 << "位元素，值为：" << a[max] << std::endl
              << "最小数是第" << min+1 << "位元素，值为：" << a[min] << std::endl
              << "总和为：" << tot << std::endl
              << "平均数为：" << (double)tot/N << std::endl;
}