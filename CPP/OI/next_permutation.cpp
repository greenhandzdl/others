#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    std::vector<int> nums = {1, 2, 3};
    // 步骤1：先排序，确保从最小的排列开始
    std::sort(nums.begin(), nums.end());

    std::cout << "All permutations:\n";
    do {
        // 步骤2：循环调用，处理当前排列
        for (int n : nums) std::cout << n << " ";
        std::cout << std::endl;
    } while (std::next_permutation(nums.begin(), nums.end()));

    return 0;
}