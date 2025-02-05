#include "stuScore.h"

namespace stuScore{
    Student::Student(unsigned int uscor, std::string uname){
        score = uscor;
        name = uname;
        grade_score = (score >= 90) ? grade::A : (score >= 80) ? grade::B : (score >= 70) ? grade::C : (score >= 60) ? grade::D : grade::E;
    }
    //Student::~Student(){}
    int Student::operator+(const Student& stu) const{
        return score + stu.score;
    }
    int Student::operator+(const int& stu) const{
        return score + stu;
    }
    int operator+(const int& stu, const Student& stu2){
        return stu + stu2.score;
    }
    std::ostream& operator<<(std::ostream& os, const Student& stu) {
        os << stu.name << " " << stu.score;
        //<< " " << stu.grade_score
        return os;
    }

    void getGrade(Student arr[], int n){
        for(int i = 0; i < n; i++){
            std::cout << "Enter the name and score of student " << i + 1 << ": ";
            getUserInputErrHandle:
            if( (std::cin >> arr[i].name >> arr[i].score) && std::cin.good() && (std::cout << std::endl) );
            else{
                std::cerr << "Input failed for student " << i + 1 << std::endl;
                std::cin.clear(); // 清除错误标志
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // 忽略错误输入
                goto getUserInputErrHandle;
            }
            arr[i].grade_score = (arr[i].score >= 90) ? grade::A : (arr[i].score >= 80) ? grade::B : (arr[i].score >= 70) ? grade::C : (arr[i].score >= 60) ? grade::D : grade::E;
        }
    }

    int averStuSco(const Student stu[],int n){
        int sum = 0;
        for(int i = 0; i < n; i++){
            sum = sum + stu[i];
        }
        return sum / n;
    }
    stuAnalysis analysis(const Student stu[],int n){
        stuAnalysis result;
        result.Max = stu[0];
        result.Min = stu[0];
        result.Avg = averStuSco(stu,n);
        for(int i = 0; i < n; i++){
            if(stu[i] > result.Max){
                result.Max = stu[i];
            }
            if(stu[i] < result.Min){
                result.Min = stu[i];
            }
            switch(stu[i].getGrade()){
                case grade::A:
                    result.A++;
                    break;
                case grade::B:
                    result.B++;
                    break;
                case grade::C:
                    result.C++;
                    break;
                case grade::D:
                    result.D++;
                    break;
                case grade::E:
                    result.E++;
                    break;
                default:
                    result.F++;
            }
        }
        return result;
    }

    void printStu(const Student stu[],int n,stuAnalysis& stu_analysis){
        std::cout << "Max: " << stu_analysis.Max << std::endl;
        std::cout << "Min: " << stu_analysis.Min << std::endl;
        std::cout << "Avg: " << stu_analysis.Avg << std::endl;
        std::cout << "A(100): " << stu_analysis.A << std::endl;
        std::cout << "B(90~99): " << stu_analysis.B << std::endl;
        std::cout << "C(80~89): " << stu_analysis.C << std::endl;
        std::cout << "D(70~79): " << stu_analysis.D << std::endl;
        std::cout << "E(60~69): " << stu_analysis.E << std::endl;
        std::cout << "F(<=60): " << stu_analysis.F << std::endl;
        for(int i = 0; i < n; i++){
            std::cout << stu[i] << std::endl;
        }
    }
}