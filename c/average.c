#include<stdio.h>
#include<stdlib.h>

static double num1,num2,num3;//可以考虑数组来增加扩展性
static unsigned int i = 1;//用于统计
static unsigned int tot = 0;//注意i和tot相关值可以用来修改平均

//TODO:分离函数来求取平均值？
int main(int argc,char *argv[]){
	extern double num1,num2,num3;
	extern unsigned int i;
	extern unsigned int tot;
	if(argc == 1){
		//一个比较老的版本，没有考虑那么多
		puts("请分别输入三个数字，来获取其平均值（输入Q退出程序）");
		while(scanf("%lf%lf%lf",&num1,&num2,&num3)==3){
			tot += num1 + num2 + num3;
			printf("%-12s %-12s %-12s %-12s %-12s\n","第一个数","第二个数","第三个数","子平均数","总平均数");
			printf("%-10.2lf%-10.2lf%-10.2lf%-10.2lf%-10u\n",num1,num2,num3,(num1+num2+num3)/3,tot/(i+2));
			i+=3;
			puts("请分别输入三个数字，来获取其平均值（输入Q退出程序）");
		}
	}else if((argc - 1)%3){
		puts("输入错误，请输入三个值来获取平均数。");
		exit(1);
	}else{
		printf("%-12s %-12s %-12s %-12s %-12s\n","第一个数","第二个数","第三个数","子平均数","总平均数");
		do{
			num1 = strtod(argv[i],NULL),num2 = strtod(argv[i+1],NULL),num3 = strtod(argv[i+2],NULL);
			tot += num1 + num2 + num3; 
			printf("%-10.2lf%-10.2lf%-10.2lf%-10.2lf%-10u\n",num1,num2,num3,(num1+num2+num3)/3,tot/(i+2));
			i+=3;
		}while(argc-i);
	}
	puts("正常退出。");
	return 0;
}