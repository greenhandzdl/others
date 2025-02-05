// gcc output_reverse.cpp -o output_reverse.out && ./output_reverse.out
//如输入3c school of guet,则输出为teug fo loohcs c3.


#include <stdio.h>
int main(){
	int i,k,temp;
	char str[80];
	printf("input a string:");
	i=0;
	while((str[i]=getchar())!='\n') 
        i++;
	str[i]=0;
	k=i-1;
	for(int i=0;i<k;++i,--k){
		temp=str[i];
		str[i]=str[k];
		str[k]=temp;
	}
	for(i=0;str[i]!=0;i++) 
        putchar(str[i]);
	return 0;
}
