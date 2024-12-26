#!/bin/bash
gcc t1.c -o t1.out && ./t1.out < t1.dat
gcc t2.c -o t2.out && ./t2.out < t2.dat
gcc t3.c -o t3.out && ./t3.out < ./t3.dat