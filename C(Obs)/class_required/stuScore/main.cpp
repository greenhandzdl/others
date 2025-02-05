#include "stuScore.h"
#include <iostream>

using namespace std;
using namespace stuScore;

int main(void){
    const int n = 40;
    Student stu[n];
    getGrade(stu,n);
    stuAnalysis stu_analysis = analysis(stu,n);
    printStu(stu,n,stu_analysis);
    return 0;
}

// g++ main.cpp stuScore.cpp -o stuScore.out && ./stuScore.out < test