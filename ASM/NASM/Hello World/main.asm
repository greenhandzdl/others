section .text
    global _start ;must be declared for linker (ld)
                    ;感觉是masm的end start，用于标注

_start: ;tells linker entry point
    mov edx,len ;message length
    mov ecx,msg ;message to write
    mov ebx,1 ;file descriptor (stdout)

    ;调用中断，不熟悉（功能号）
    mov eax,4 ;system call number (sys_write)
    int 0x80 ;call kernel

    mov eax,1 ;system call number (sys_exit)
    int 0x80 ;call kernel
    
section .data
    msg db 'Hello, world!', 0xa ;our dear string
    len equ $ - msg ;length of our dear string
                    ;equ常量赋值 $当前地址