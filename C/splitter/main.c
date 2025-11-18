#include <stdio.h>
#include "splitter.h"

int main() {
    // 测试用例1：逗号分隔
    printf("=== Test 1: Comma delimiter ===\n");
    SplitResult result1 = create_splitter(",","Enter a comma-separated string: ");
    print_split_result(result1);
    free_splitter(result1);
    
    printf("\n=== Test 2: Space delimiter ===\n");
    SplitResult result2 = create_splitter(" ","Enter a space-separated string: ");
    print_split_result(result2);
    free_splitter(result2);
    
    printf("\n=== Test 3: Multi-character delimiter ===\n");
    SplitResult result3 = create_splitter("::","Enter a string with '::' as delimiter: ");
    print_split_result(result3);
    free_splitter(result3);
    
    printf("\n=== Test 4: Empty delimiter (edge case) ===\n");
    SplitResult result4 = create_splitter("","Enter a string with empty delimiter: ");
    print_split_result(result4);
    free_splitter(result4);
    
    return 0;
}