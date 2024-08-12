;编程，以“ 年/月/日时:分:秒” 的格式，显示当前的日期、时间。
;秒:0 分:2 时:4 日:7 月:8 年:9
assume cs:code

data segment
    db 9,8,7,4,2,0,-1
data ends

code segment
    start:
        mov bx,data
        mov ds,bx
        mov si,0;初始化地址

        mov bx, 0b800h
        mov es,bx;显存地址(中断可能可以)

        l0:
            mov al,ds:[si]
            inc si
            call data_get
            call data_process
            call print
            cmp byte ptr ds:[si],-1
            jne l0

        mov ax,4c00h
        int 21h

    data_get:
        ;获取数据(al;要读入数据地址)
        out 70h,al
        in al,71h
        ret

    data_process:
        ;处理数据(al;传入数据，cl;占用)
        mov ah,al;先处理ah
        mov cl,4
        shr ah,cl
        and al,00001111b;处理al，把高位的ab码删掉
        or ax,0011000000110000b
        ret

    print:
        shl si,1
        shl si,1
        shl si,1
        mov byte ptr es:[160*12+40*2][si],ah
        mov byte ptr es:[160*12+40*2+2][si],al
        mov dl,'/'
        mov byte ptr es:[160*12+40*2+4][si],dl
        shr si,1
        shr si,1
        shr si,1
        ret

code ends

end start