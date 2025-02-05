#include "config.h"
#include <stdio.h>
#include "builtins.h"
#include "shell.h"
#include "bashgetopt.h"

extern char *repeatname();
// 定义结构体，用于描述内建命令
struct builtin repeat_struct = {
    "repeat",  // command：命令名称
    repeat_builtin, // function name：对应的执行函数指针
    BUILTIN_ENABLED,  // status：命令状态，这里假设 BUILTIN_ENABLED 表示启用
    repeat_doc, // an array about help doc.：帮助文档数组
    "tty [-s]", // usage：用法说明
    0
};
// 内建命令的执行函数
repeat_builtin (list) Word_List *list;
{
    int opt,sflag;
    char *t;

    // 重置内部选项解析器
    reset_internal_getopt();
    sflag = 0;

    // 解析命令行选项
    while( (opt = interal_getopt (list,"s") )!= -1){
        switch(opt){
            case 's':
                sflag = 1;
                break;
            default:
                // 如果遇到不认识的选项，显示用法说明并返回错误码
                builtin_usage();
                return (EX_USAGE);
        }
    }
    list = loptend;
    // 遍历剩余的参数并输出（复读）
    for(int i = 0;loptend[i];i++)
        puts(loptend[i]);
    // 根据标志返回执行结果状态码
    return (sflag?EXECUTION_SUCCESS:EXECUTION_FAILURE);
}
// 帮助文档数组
char *repeat_doc[] ={
    "repeat命令是用来复读的程序\n",
    "当用户在该命令后输入参数时，他会跟着复读\n",
    "但是，为了更好学习bash的内建用法\n",
    "我尝试加入了-s选项后才开始复读的功能\n",
    "这也是你可能会看到这个消息的原因\n",
    "除此之外，他一无所用\n",
    (char *)NULL
};