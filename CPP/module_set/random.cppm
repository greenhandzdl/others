/////// A.cpp （'A' 的主模块接口单元）
module;
 
// 按照 POSIX 标准，定义 _POSIX_C_SOURCE 会向标准标头中添加函数。
#define _POSIX_C_SOURCE 200809L
#include <stdlib.h>

export module rand_time;
 
import <ctime>;
 
// 仅用于演示（差的随机源）。应改为使用 C++ <random>。
export double weak_random()
{
    std::timespec ts;
    std::timespec_get(&ts, TIME_UTC); // 来自 <ctime>
 
    // 按照 POSIX 标准从 <stdlib.h> 提供。
    srand48(ts.tv_nsec);
 
    // drand48() 返回 0 与 1 之间的一个随机数
    return drand48();
}