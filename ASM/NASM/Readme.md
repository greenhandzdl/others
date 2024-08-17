# 特色功能（建议先MASM）：
** 宏：
```
        %macro write_string 2
        mov eax, 4
        mov ebx, 1
        mov ecx, %1
        mov edx, %2
        int 80h
        %endmacro

        write_string msg1, len1;调用
```