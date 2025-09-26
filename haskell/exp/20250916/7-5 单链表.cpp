#include <iostream>
#include <list>
using namespace std;

int main() {
    int n;
    cin >> n;
    list<int> mylist;
    
    // 读入n个整数
    for (int i = 0; i < n; i++) {
        int num;
        cin >> num;
        mylist.push_back(num);
    }
    
    // 遍历输出
    auto it = mylist.begin();
    while (it != mylist.end()) {
        cout << *it;
        if (++it != mylist.end()) {
            cout << " ";
        }else{
            cout << std::endl;
        }
    }
    
    return 0;
}