/*
2．调试程序
	改正下列程序中的错误。将字符串s连接到t的后面。如输入Birthday 和 Happy 。则程序输出Happy Birthday。
    Birthday 
    Happy
*/
#include <stdio.h>
#define MAX 80
void mystrc(char *s,char *t);

int main(void){
	char s[MAX],t[MAX];

	gets(s);
    gets(t);

	mystrc(s,t);
	puts(t);
	return 0;
}

void mystrc(char *s,char *t){

    puts(s);
    puts(t);
	while(*t != '\0')
        ++t;
	while(*t = *s)
        ++t,++s;
}

// gcc  main2.c -o main2.out && ./main2.out