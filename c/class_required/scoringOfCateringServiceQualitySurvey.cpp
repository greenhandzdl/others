// g++ scoringOfCateringServiceQualitySurvey.cpp -o scoringOfCateringServiceQualitySurvey.out && ./scoringOfCateringServiceQualitySurvey.out < test_score

//在商业和科学研究中，人们经常需要对数据进行分析并将结果以直方图的形式显示出来。
//例如，一个公司的主管可能需要了解一年来公司的营业状况，比较一下各月份的销售收入状况。
//如果仅给出一大堆数据，这显然太不直观了，如果能将这些数据以条形图（直方图）的形式表示，将会大大增加这些数据的直观性，也便于数据的分析与对比。
//下面以顾客对餐饮服务打分为例，练习这方面的程序编写方法。
//假设有 40 个学生被邀请来给自助餐厅的食品和服务质量打分，分数划分为 1～10 这 10 个等级（1 表示最低分，10 表示最高分），试统计调查结果，并用*打印出如下形式的统计结果直方图。

#include<iostream>

static const int Member (40);
static unsigned int ScoreLevel[Member];

static const int scale (2);//缩小倍

void input_arr(void);
void show_arr(void);

int main(void){
    input_arr();
    show_arr();
}

void input_arr(void){
    using std::cout;
    using std::cin;
    using std::endl;
    
    extern unsigned int ScoreLevel[];
    
    for(int i = 0; i < Member; i++){
        cout << "Please enter the score of the " << i + 1 << "th member: ";
        cin >> ScoreLevel[i];
        if(!cin){
            cin.clear();
            while(cin.get()!='\n');
            cout << "Invalid input!" << endl;
            --i;
        }
        if(ScoreLevel[i] < 1 || ScoreLevel[i] > 10){
            --i;
        }
        cout << endl;
    }
    cout << endl;
}
void show_arr(void){
    printf("%-.8s %-.8s %-.8s\n","Grade","Count","Hisogram");
    for(int i = 0; i < Member; ++i){
        printf("%-5d %-5d ",i + 1,ScoreLevel[i]);
        for(int j = 0; j < ScoreLevel[i]/scale; ++j){
            printf("*");
        }
        printf("\n");
    }
}