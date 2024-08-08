;由于开启单步后 执行每条指令都会引发中断，也就是说单步执行每条指令都会触发断点
;单步执行会引发中断，这会在当前栈内压入 cs和ip以用于中断返回
;所以直接p过吧，不能单步调试，代码上没有问题
assume cs:code

stack segment
    db 16 dup (0)
stack ends

code segment
    start:
        mov ax,stack
        mov ss,ax
        mov sp,16;自己加的栈

        mov ax,4240H
        mov dx,000FH
        mov cx,0AH
        call divdw
        
        mov ax, 4c00h 
        int 21h

        divdw:
            ;名称:divdw
            ;功能:进行不会产生溢出的除法运算，被除数为dword型，除数为word型，结果为dword型。
            ;参数:(ax)=dword型数据的低16位
            ;   (dx)=dword型数据的高16位
            ;   (cx)=除数
            ;返回:(dx)=结果的高16位，(ax)=结果的低16位
            ;   (cx)=余数

            push ax;低位等会算，(sp)-2
            mov ax,dx
            mov dx,0
            div cx;此时ax是商，dx是余数

            push ax;保存商
            mov ax,dx
            add sp,2
            pop ax
            div cx

            mov cx,dx
            sub sp,4
            pop dx
            add sp,2

            ret
code ends

end start