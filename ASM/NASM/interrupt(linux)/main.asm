;详细查看:/usr/include/asm/unistd.h
section .data ;数据段
    userMsg db '请输入一个数字：' ;提示用户输入数字
    lenUserMsg equ $-userMsg ;消息长度
    dispMsg db '您输入的数字是：' ;输出消息
    lenDispMsg equ $-dispMsg

section .bss ;未初始化数据段
    num resb 5 ;预留 5 个字节存储用户输入的数字

section .text ;代码段
    global _start ;声明入口点函数

_start:
    ;用户提示
    mov eax, 4 ;系统调用号：写
    mov ebx, 1 ;文件描述符：标准输出
    mov ecx, userMsg ;提示信息地址
    mov edx, lenUserMsg ;提示信息长度
    int 80h ;执行系统调用
    ;读取并存储用户输入
    mov eax, 3 ;系统调用号：读
    mov ebx, 2 ;文件描述符：标准输入
    mov ecx, num ;输入缓冲区地址
    mov edx, 5 ;要读取的字节数（数字最多 5 位，含符号）
    int 80h ;执行系统调用
    ;输出消息 '您输入的数字是：'
    mov eax, 4 ;系统调用号：写
    mov ebx, 1 ;文件描述符：标准输出
    mov ecx, dispMsg ;消息地址
    mov edx, lenDispMsg ;消息长度
    int 80h ;执行系统调用
    ;输出输入的数字
    mov eax, 4 ;系统调用号：写
    mov ebx, 1 ;文件描述符：标准输出
    mov ecx, num ;输入缓冲区地址
    mov edx, 5 ;要写入的字节数
    int 80h ;执行系统调用
    ;退出代码
    mov eax, 1 ;系统调用号：退出
    mov ebx, 0 ;退出状态：成功
    int 80h ;执行系统调用
