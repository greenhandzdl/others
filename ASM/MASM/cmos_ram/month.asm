assume cs:code
code segment
    start:
        mov al,8
        out 70h,al
        in al,71h
        mov ah,al;处理高位
        mov cl,4
        shr ah,cl
        and al,00001111b;保留低位
        add ah,30h
        add al,30h

        mov bx,0b800h
        mov es,bx
        mov byte ptr es:[160*12+40*2],ah ;显示月份的十位数码
        mov byte ptr es:[160*12+40*2+2],al ;接着显示月份的个位数码
        
        mov ax,4c00h
        int 21h
code ends

end start