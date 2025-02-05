#!/bin/bash
nasm -f elf32 main.asm 
ld -m elf_i386 -s -o main main.o
