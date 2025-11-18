#include "splitter.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// 内部函数：分割字符串
static SplitResult split_string(const char* input, const char* delimiter) {
    SplitResult result = {NULL, 0};
    
    if (input == NULL || delimiter == NULL) {
        return result;
    }
    
    size_t delimiter_len = strlen(delimiter);
    
    // 特殊情况：空分隔符，返回整个字符串作为一个片段
    if (delimiter_len == 0) {
        result.count = 1;
        result.segments = (char**)malloc(sizeof(char*));
        if (result.segments != NULL) {
            result.segments[0] = strdup(input);
        }
        return result;
    }
    
    // 计算分割后的子字符串数量
    const char* pos = input;
    while ((pos = strstr(pos, delimiter)) != NULL) {
        result.count++;
        pos += delimiter_len;
    }
    result.count++; // 最后一个片段
    
    // 分配指针数组
    result.segments = (char**)malloc(result.count * sizeof(char*));
    if (result.segments == NULL) {
        result.count = 0;
        return result;
    }
    
    // 初始化所有指针为NULL，便于错误处理时清理
    for (size_t i = 0; i < result.count; i++) {
        result.segments[i] = NULL;
    }
    
    // 分割字符串
    size_t index = 0;
    const char* start = input;
    const char* end;
    
    while ((end = strstr(start, delimiter)) != NULL) {
        size_t length = end - start;
        result.segments[index] = (char*)malloc(length + 1);
        if (result.segments[index] == NULL) {
            // 内存分配失败，清理已分配的内存
            free_splitter(result);
            result.segments = NULL;
            result.count = 0;
            return result;
        }
        
        strncpy(result.segments[index], start, length);
        result.segments[index][length] = '\0';
        
        index++;
        start = end + delimiter_len;
    }
    
    // 处理最后一个片段
    size_t last_length = strlen(start);
    result.segments[index] = (char*)malloc(last_length + 1);
    if (result.segments[index] == NULL) {
        free_splitter(result);
        result.segments = NULL;
        result.count = 0;
        return result;
    }
    strcpy(result.segments[index], start);
    
    return result;
}

SplitResult create_splitter(const char* delimiter, const char* prompt) {
    SplitResult result = {NULL, 0};
    
    if (delimiter == NULL) {
        return result;
    }
    
    // 读取一行输入
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    if (prompt != NULL)
        printf("%s", prompt);
        
    read = getline(&line, &len, stdin);
    
    if (read == -1) {
        free(line);
        return result;
    }
    
    // 去除换行符
    if (read > 0 && line[read - 1] == '\n') {
        line[read - 1] = '\0';
    }
    
    // 分割字符串
    result = split_string(line, delimiter);
    
    free(line);
    return result;
}

void free_splitter(SplitResult result) {
    if (result.segments == NULL) return;
    
    for (size_t i = 0; i < result.count; i++) {
        free(result.segments[i]);
    }
    free(result.segments);
}

void print_split_result(const SplitResult result) {
    if (result.segments == NULL) {
        printf("No segments (NULL result)\n");
        return;
    }
    
    printf("Split into %zu segments:\n", result.count);
    for (size_t i = 0; i < result.count; i++) {
        printf("  [%zu] '%s'\n", i, result.segments[i]);
    }
}