### 学生成绩统计

#### 需求描述
随机产生一个班（全班不少于 30 人）学生某门课的成绩，分别实现下列功能：
1. 统计不及格人数并打印不及格学生名单。
2. 统计成绩在全班平均分及平均分之上的学生人数，并打印这些学生的名单。
3. 统计各分数段的学生人数及所占的百分比。

#### 分数段划分
- 60 分以下为第 0 段
- 60~69 为第 1 段
- 70~79 为第 2 段
- 80~89 为第 3 段
- 90~99 为第 4 段
- 100 分为第 5 段

#### 编程要求
1. 较好的用户输入输出提示信息。
2. 使用子函数来实现上述各个功能。
3. 最好不要使用全局变量。

#### 提示
1. 用 `num[i]` 存放第 i+1 个学生的学号，用 `score[i]` 存放第 i+1 个学生的成绩。设置计数器 `count`，当 `score[i] < 60` 分时，计数器 `count` 计数一次，并打印 `num[i]` 和 `score[i]`。
2. 先计算全班平均分 `aver`，当第 i 个学生的成绩 `score[i] >= aver` 时，打印 `num[i]` 和 `score[i]`。
3. 各分数段的学生人数保存在数组 `stu` 中，用 `stu[i]` 存放第 i 段的学生人数。对于每个学生的成绩，先计算出该成绩所对应的分数段，然后将相应的分数段的人数加 1，即 `stu[i]++`。

#### 参考函数原型
1. **从键盘输入一个班学生某门课的成绩及其学号**
   ```c
   int ReadScore(long num[], float score[]);
   ```
   - 参数：长整型数组 `num`，存放学生学号；实型数组 `score`，存放学生成绩。
   - 返回值：学生总数。

2. **统计不及格人数并打印不及格学生名单**
   ```c
   int GetFail(long num[], float score[], int n);
   ```
   - 参数：长整型数组 `num`，存放学生学号；实型数组 `score`，存放学生成绩；整型变量 `n`，存放学生总数。
   - 返回值：不及格人数。

3. **计算全班平均分**
   ```c
   float GetAver(float score[], int n);
   ```
   - 参数：实型数组 `score`，存放学生成绩；整型变量 `n`，存放学生总数。
   - 返回值：平均分。

4. **统计成绩在全班平均分及平均分之上的学生人数并打印名单**
   ```c
   int GetAboveAver(long num[], float score[], int n, float aver);
   ```
   - 参数：长整型数组 `num`，存放学生学号；实型数组 `score`，存放学生成绩；整型变量 `n`，存放学生总数；浮点型变量 `aver`，存放全班平均分。
   - 返回值：成绩在全班平均分及平均分之上的学生人数。

5. **统计各分数段的学生人数及所占的百分比**
   ```c
   void GetScoreDistribution(float score[], int n, int stu[], float percent[]);
   ```
   - 参数：实型数组 `score`，存放学生成绩；整型变量 `n`，存放学生总数；整型数组 `stu`，存放各分数段的学生人数；浮点型数组 `percent`，存放各分数段的学生人数所占的百分比。

### 示例代码
```c
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STUDENTS 50
#define NUM_SEGMENTS 6

// 从键盘输入一个班学生某门课的成绩及其学号
int ReadScore(long num[], float score[]) {
    int n;
    printf("请输入学生人数（不少于30人）: ");
    scanf("%d", &n);
    if (n < 30) {
        printf("学生人数必须不少于30人！\n");
        return 0;
    }
    for (int i = 0; i < n; i++) {
        printf("请输入第 %d 个学生的学号和成绩: ", i + 1);
        scanf("%ld %f", &num[i], &score[i]);
    }
    return n;
}

// 统计不及格人数并打印不及格学生名单
int GetFail(long num[], float score[], int n) {
    int count = 0;
    printf("不及格学生名单:\n");
    for (int i = 0; i < n; i++) {
        if (score[i] < 60) {
            printf("学号: %ld, 成绩: %.2f\n", num[i], score[i]);
            count++;
        }
    }
    return count;
}

// 计算全班平均分
float GetAver(float score[], int n) {
    float sum = 0;
    for (int i = 0; i < n; i++) {
        sum += score[i];
    }
    return sum / n;
}

// 统计成绩在全班平均分及平均分之上的学生人数并打印名单
int GetAboveAver(long num[], float score[], int n, float aver) {
    int count = 0;
    printf("成绩在全班平均分及平均分之上的学生名单:\n");
    for (int i = 0; i < n; i++) {
        if (score[i] >= aver) {
            printf("学号: %ld, 成绩: %.2f\n", num[i], score[i]);
            count++;
        }
    }
    return count;
}

// 统计各分数段的学生人数及所占的百分比
void GetScoreDistribution(float score[], int n, int stu[], float percent[]) {
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        stu[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        if (score[i] < 60) {
            stu[0]++;
        } else if (score[i] < 70) {
            stu[1]++;
        } else if (score[i] < 80) {
            stu[2]++;
        } else if (score[i] < 90) {
            stu[3]++;
        } else if (score[i] < 100) {
            stu[4]++;
        } else {
            stu[5]++;
        }
    }
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        percent[i] = (float)stu[i] / n * 100;
    }
}

int main() {
    long num[MAX_STUDENTS];
    float score[MAX_STUDENTS];
    int n = ReadScore(num, score);
    if (n == 0) {
        return 1;
    }

    int fail_count = GetFail(num, score, n);
    printf("不及格人数: %d\n", fail_count);

    float aver = GetAver(score, n);
    printf("全班平均分: %.2f\n", aver);

    int above_aver_count = GetAboveAver(num, score, n, aver);
    printf("成绩在全班平均分及平均分之上的学生人数: %d\n", above_aver_count);

    int stu[NUM_SEGMENTS];
    float percent[NUM_SEGMENTS];
    GetScoreDistribution(score, n, stu, percent);
    printf("各分数段的学生人数及所占的百分比:\n");
    for (int i = 0; i < NUM_SEGMENTS; i++) {
        printf("第 %d 段: %d 人, 占 %.2f%%\n", i, stu[i], percent[i]);
    }

    return 0;
}
```

### 说明
- 代码中使用了 `ReadScore` 函数从键盘读取学生学号和成绩。
- `GetFail` 函数统计不及格人数并打印不及格学生名单。
- `GetAver` 函数计算全班平均分。
- `GetAboveAver` 函数统计成绩在全班平均分及平均分之上的学生人数并打印名单。
- `GetScoreDistribution` 函数统计各分数段的学生人数及所占的百分比。