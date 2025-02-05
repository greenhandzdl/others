assume cs:code

data segment
    db 'Welcome to masm!', 0 
data ends

code segment
start: mov dh,8
    mov dl,3
    mov cl,2

    mov ax,data 
    mov ds,ax
    mov si,0

    call show_str

    mov ax, 4c00h 
    int 21h

    show_str:
        ;名称:show_str
        ;功能:在指定的位置，用指定的颜色，显示一个用O结束的字符串。
        ;参数:(dh)=行号(取值范围0~24)，(dl)=列号(取值范围O~79)， (cl)=颜色，ds:si指向字符串的首地址
        ;返回:无
        ;应用举例:在屏幕的8 行3 列，用绿色显示data 段中的字符串。

        ;计算下行号（段位置）
        mov al,0Ah
        mul dh
        mov ah,0B8h

        mov es,ax

        ;计算列号偏移位置
		mov bl,dl
        dec bl
        mov bh,0
        add bx,bx

        ;准备颜色
        mov ah,cl

        continue:
            ;读取数据并且判断
            mov cl,ds:[si]
            mov ch,0
            jcxz break

            mov al,ds:[si]
			mov es:[bx][si],ax
			inc bx
            inc si
            jmp continue

        break:
            ret
        
code ends

end start