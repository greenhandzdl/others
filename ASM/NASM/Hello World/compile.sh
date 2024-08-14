#! /bin/bash
#好像跑不动，这个适用x64的（？）
rm main.o

nasm -f macho main.asm 
gcc main.o -o main
./main