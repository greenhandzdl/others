#include <stdio.h>

typedef enum {
    A = 0,
    B,
    C,
    D
} PEO;

// 根据假设的做好事的人判断真话的数量
int countTrueStatements(PEO who) {
    int true_count = 0;
    // A说：不是我。
    if (who!= A) {
        true_count++;
    }
    // B说：是C。
    if (who == C) {
        true_count++;
    }
    // C说：是D。
    if (who == D) {
        true_count++;
    }
    // D说：他胡说。（不是D）
    if (who!= D) {
        true_count++;
    }
    return true_count;
}

int main(void) {
    for (PEO who = A; who <= D; who++) {
        if (countTrueStatements(who) == 3) {
            printf("是第%c位同学做的好事\n", who == A? 'A' : who == B? 'B' : who == C? 'C' : 'D');
            break;
        }
    }
    return 0;
}