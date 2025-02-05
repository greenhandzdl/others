assume cs:code,ds:data,ss:stack

data segment
	db 32 dup (' ')
	db 'W','e','l','c','o','m','e',' ','t','o',' ','m','a','s','m','!'
	db 32 dup (' ')
data ends

stack segment
	db 00000010b,00100100b,01110001b
	;对于栈而言，pop和push都是一个word而不是byte，也就是可以说用dw。
	;同时栈中的低位对于寄存器地位，高位对于寄存器高位。
	;可以这么写dw 0000001000000010b（偷懒），后面也就不需要动SP了
stack ends

code segment
	start:
		mov ax,data
		mov ds,ax
		mov ax,stack
		mov ss,ax
		mov sp,0

		mov ax,0B864H
		mov es,ax

		mov cx,3

		l0:
			mov di,cx

			pop ax
			dec sp
			mov ah,al

			mov cx,80
			mov si,0
			l1:
				mov al,ds:[si]
				;在开发效率角度而言，用另一个寄存器或许好些，如bx等等，程序简单时不用省着寄存器
				;mov bx,si
				;mov es:[bx][si],ax
				shl si,1
				mov es:[si],ax;mov es:[si*2],ax
				shr si,1
				inc si
				loop l1
			mov ax,es
			add ax,0Ah
			mov es,ax

			mov cx,di
			loop l0

		mov ax, 4c00h
		int 21h
code ends

end start