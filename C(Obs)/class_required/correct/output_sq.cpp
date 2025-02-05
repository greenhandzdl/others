// g++ output_sq.cpp -o output_sq.out && ./output_sq.out
#include<iostream>

int main(void){
    using std::cout;
    using std::endl;
    
    int i,j,k;
    for(i=1;i<=6;i++){ 
        for(k=1;k<=20-i;k++)
            cout<<' ';
        for(j=1;j<=4*i-3;j++)
            cout<<'*';
        cout<<endl;
        }
}
