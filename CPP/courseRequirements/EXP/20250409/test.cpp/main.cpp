#include<iostream>
#include<limits>

// won't work
// echo  "3\n123 \n\n0" | run ./main.app > log
// echo  "3\n123 \n0" | run ./main.app > log
// works
// run ./main.app > log < test.txt
// echo -e  "3\n123 \n\n0" | run ./main.app > log
int main(void){
    int choice;
    int BookID;
    do {
        std::cout << "请选择您要执行的操作:" << std::endl;
        std::cin >> choice;
        std::cout << choice << std::endl;
        switch(choice) {
            case 0:
                std::cout << "程序已退出" << std::endl;
                break;

            case 3:
                std::cout << "请输入要查找的图书书号: ";
                std::cin >> BookID;
                break;
        }
        
        if(choice != 0) {
            std::cout << "\n按Enter键继续...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::cout << std::string(50, '\n');
        }
        if(std::cin.eof())
            break;
    } while(choice != 0);
    return 0;
}