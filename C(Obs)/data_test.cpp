#include <stdio.h>

typedef unsigned char *byte_pointer;

void show_bytes (byte_pointer start, size_t len) {
    size_t i;
    for (i = 0; i < len; i++) 
        printf(" %.2x", start [i]) ;
    printf ("\n") ;
}

int main(){
    int x = 32768;
    float y = x;
    for(int i = 0; i < 8; i++){
        printf("Int:%zu",sizeof(x));
        show_bytes((byte_pointer)&x, i + 1);
        puts("");
        printf("Float:%zu",sizeof(y));
        show_bytes((byte_pointer)&y, i + 1);
        puts("");
    }

}
/*
Int:4 00
Float:4 00

Int:4 00 80
Float:4 00 00

Int:4 00 80 00
Float:4 00 00 00

Int:4 00 80 00 00
Float:4 00 00 00 47

Int:   00000000 01000000 00000000 00000000
Float: 00000000 00000000 00000000 00100111

*/