// g++ make_change.cpp -o make_change.out && ./make_change.out

#include<iostream>

//将一面额为10元倍数的整钱（<=100元）换成1元、2元和5元的零钱组合（每种面值都要有）。输入要换的面额（如10元），输出所有可能的换法（如2种）。

static unsigned int change_money[3] = {1,2,5};

int main(void){
    using std::cout;
    using std::cin;
    using std::endl;
    
    unsigned int money (0);
    cout << "请输入要换的面额：";
    cin >> money;
    
    printf("%.5s %.5s %.5s\n", "1元", "2元", "5元");
    
    for(unsigned int i = 0; i <= money; i++)
        for(unsigned int j = 0; j <= money; j++)
            for(unsigned int k = 0; k <= money; k++)
                if(i*change_money[0] + j*change_money[1] + k*change_money[2] == money)
                    printf("%-3u %-3u %-3u\n", i, j, k);
    //优化可以参考贪婪算法等等（在最后打印）             
    return 0;
}