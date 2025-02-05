//给定 4 个砝码，质量分别为 4, 4, 5, 9 克。
//每次只能选择相邻的两堆砝码合并成新的一堆，并将新的一堆砝码的总质量记为该次合并的得分。
//求将这 4 堆砝码合并成一堆的最大得分。
#include <iostream>
#include <ctime>
#include <cstdlib>

const int N = 4; // 4个砝码

void weightInit(int weight[], int size) {
    srand((unsigned)time(NULL));
    for (int i = 0; i < size; i++) {
        weight[i] = rand() % 10 + 1;
    }
}

void printWeight(const int weight[], const int size) {
    std::cout << "weight: ";
    for (int i = 0; i < size; i++) {
        std::cout << "i:" << weight[i] << " ";
    }
    std::cout << std::endl;
}


int soluteWeight(const int weight[], int size) {
    int sum = 0;
    if(size <= 1){
        return weight[0];
    }
    for(int i = 0; i < size - 1; i++){
        sum += weight[i];
    }
    int L = soluteWeight(weight, size - 1);
    int R = soluteWeight(weight + 1, size - 1);
    return (L > R) ? sum + L : sum + R;
}

int main(void) {
    int weight[N];
    int ans = 0;
    weightInit(weight, N);
    printWeight(weight, N);
    ans = soluteWeight(weight, N);
    std::cout << "ans: " << ans << std::endl;
    return 0;
}
// g++ recursiveSolution.cpp -o recursiveSolution.out && ./recursiveSolution.out