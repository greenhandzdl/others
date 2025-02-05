#include <iostream>

namespace stuScore{
    enum grade{
                A, B, C, D, E, F
            };//将成绩分为六个分数段，60 分以下为第 0 段(F)，60~69 为第 1 段，70~79 为第 2 段，80~89 为第 3 段，90~99 为第 4 段，100 分为第 5 段(A)。
    class Student{
        private:
            unsigned int score;
            std::string name;
            grade grade_score;
        public:
            Student(unsigned int uscor = 0, std::string uname = "null");
            //~Student();

            grade getGrade() const{
                return grade_score;
            }

            int operator+(const Student& stu) const;
            int operator+(const int& stu) const;
            friend int operator+(const int& stu, const Student& stu2);

            operator int() const{
                return score;
            }
            friend void getGrade(Student arr[], int n);
            friend std::ostream& operator<<(std::ostream& os, const Student& stu) ;
    };

    struct stuAnalysis{
        unsigned int A;
        unsigned int B;
        unsigned int C;
        unsigned int D;
        unsigned int E;
        unsigned int F;//不及格人数
        unsigned int Max;
        unsigned int Min;
        unsigned int Avg;
    };

    int averStuSco(const Student stu[],int n);
    stuAnalysis analysis(const Student stu[],int n);

    void printStu(const Student stu[],int n,stuAnalysis& stu_analysis);

}