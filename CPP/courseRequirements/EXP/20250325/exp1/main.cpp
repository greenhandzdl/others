/*
学生数据有编号、姓名、班级和成绩.
教师数据有编号、姓名、职称和部门。
要求将编号、姓名输入和显示设计成一个类person,并作为学生数据操作类student和教师类数据操作类teacher的基类。
*/
#include<iostream>
#include<cstdio>
//ADT:
class Person{
    public:
        Person(const Person&) = delete;
        Person& operator=(Person&) = delete;

    protected:
        using iNUM = int;
        using STRING = std::string;
        Person(iNUM _id,STRING _name)
        :ID(_id),NAME(_name)
        {}
        virtual ~Person() = default;
        // forward declare 除非像下面那个继承写的那么糟糕。
        decltype(auto) getID() const noexcept{
            return this->ID;
        }
        decltype(auto) getNAME() const noexcept{
            return this->NAME;
        }
    public:
        virtual void printData(void) const{
            printf("编号：%-4d，姓名：%-15s \n",
                getID(),
                getNAME().c_str() //getNAMEC()
            );
        }
    private:
        const iNUM ID {0};
        const STRING NAME  {"NULL"};
};

class Student :virtual public Person{
    public:
        using Person::iNUM,Person::STRING;
        using fNUM = double;
        Student(iNUM _id,STRING _name,iNUM _class,fNUM _grades)
        :Person(_id , _name),
        CLASS(_class),GRADES(_grades)
        {}
        void printData(void) const override{
            Person::printData();
            printf("班级：%d，成绩：%f\n",
                iGetCLASS(),
                fGetGRADES()
            );
        }
    protected:
        int iGetCLASS() const noexcept{
            return this->CLASS;
        }
        double fGetGRADES() const noexcept{
            return this->GRADES;
        }
    private:
        const iNUM CLASS = 0;
        const fNUM GRADES = 0;
};
class Teacher:virtual public Person{
    public:
        using Person::iNUM,Person::STRING;
        Teacher(iNUM _id,STRING _name,STRING _job_title,STRING _department)
        :Person(_id,_name),
        JOB_TITLE(_job_title),DEPARTMENT(_department)
        {};
        void printData(void) const override{
            Person::printData();
            printf("职称：%s 部门：%s \n",
                JOB_TITLE.c_str(),
                DEPARTMENT.c_str()
            );
        }
    protected:
        //感觉有些没必要写getter和setter

    private:
        const STRING JOB_TITLE = "NULL";
        const STRING DEPARTMENT = "NULL";
};


int main(void){
    Student student {20,"李华",4,87.2};
    Teacher teacher1 {20,"张三", "X","Y"};
    Teacher teacher2 {20,"李三", "X","Y"};

    Person * (arr [3]);
    arr[0] = &student;
    arr[1] = &teacher1;
    arr[2] = &teacher2;

    for(auto x : arr)
        x->printData();
}