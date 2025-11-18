#ifndef SPLITTER_H
#define SPLITTER_H

#include <stddef.h>

// 分割结果结构体
typedef struct {
    char** segments;    // 分割后的字符串数组
    size_t count;       // 分割后的片段数量
} SplitResult;

/**
 * @brief 创建字符串分割器（类似Haskell的createSplitter）
 * @param delimiter 分隔符字符串
 * @return SplitResult 包含分割结果和片段数量的结构体
 * 
 * 这个函数会从标准输入读取一行，然后按指定分隔符进行分割
 * 使用完毕后需要调用free_splitter释放内存
 */
SplitResult create_splitter(const char* delimiter, const char* prompt);

/**
 * @brief 释放分割器分配的内存
 * @param result 由create_splitter返回的分割结果
 */
void free_splitter(SplitResult result);

/**
 * @brief 打印分割结果（用于调试）
 * @param result 分割结果
 */
void print_split_result(const SplitResult result);

#endif // SPLITTER_H