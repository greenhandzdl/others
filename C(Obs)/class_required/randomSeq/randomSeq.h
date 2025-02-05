#ifndef RANDOMSEQ_H
#define RANDOMSEQ_H

    #include<iostream>//使用cin cout等
    #include<ctime>//获取当前时间
    #include<cstdlib>//使用rand()等函数

    class Member{
        private:
            int id;
            std::string memberName;
            void print(void){
                std::cout<<memberName<<" "<<id<<std::endl;//调试用的
            }


        public:
            Member(const std::string& = "None");//default constructor用于随机生成某个数来确定他的排序顺序

            std::string name(void){
                return memberName;//inline function，返回名字
            }
            bool operator>(const Member&) const;//用于排序，返回一个对象id最大的指针
            bool operator<(const Member&) const;//用于排序，返回一个对象id最小的指针
            bool operator==(const Member&) const;
            bool operator!=(const Member&) const;

            friend std::ostream& operator<<(std::ostream&, const Member&);

            ~Member()//default constructor用于销毁该类并且输出
            {
                std::cout<<"Member "<<memberName<<" is destroyed."<<std::endl;
            }
    };

#endif