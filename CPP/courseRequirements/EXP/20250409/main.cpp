
/*
1、输入N（10<N<20）本图书的信息：
书号（6个字符）、书名（12个字符）、作者（8个字符）、单价（2位小数）；
将所有数据写入文件ST1.DAT中；
2、从ST1.DAT文件中读取图书数据，将价钱高于30元的图书信息输出；
3、输入书号，在ST1.DAT文件中查找该图书，找到以后输出该图书的所有数据，如果文件中没有输入的书号，给相应的提示信息。
*/
#include "file_def.h"
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cstring>
#include <limits>
#include <csignal>
using namespace FILE_DEF;
namespace{
    inline void ActionCreateFile(const char* fileName){
        std::ofstream outFile(fileName, std::ios::out|std::ios::app); // 使用 std::ios::out 模式尝试打开文件
        if(!outFile.is_open()){
            std::cerr << "无法创建文件: " << fileName << std::endl;
            return;
        }
        outFile.close();
    }
    inline void ActionWriteFile(const Book& book,
        const char* fileName){
            std::ofstream outFile(fileName,std::ios::out|std::ios::app);
            if(!outFile.is_open())
                return;
            outFile << book << std::endl;
            outFile.close();
        }
    inline void ActionReadFile(const char* fileName){
            Book tempBook;
            std::ifstream inFile(fileName,std::ios::in);
            if(!inFile.is_open()){
                std::cerr << "无法打开文件: " << fileName << std::endl;
                return;
            }
            std::cout << "所有图书信息：" << std::endl;
            std::cout << std::setw(6) << std::left << "书号" 
                      << std::setw(12) << std::left << "书名" 
                      << std::setw(8) << std::left << "作者" 
                      << "单价" << std::endl;
            while(inFile >> tempBook)
                std::cout << tempBook << std::endl;
            inFile.close();
        }
    inline void ActionReadExpensiveBooks(const char* fileName, double priceThreshold){
            Book tempBook;
            std::ifstream inFile(fileName,std::ios::in);
            if(!inFile.is_open()){
                std::cerr << "无法打开文件: " << fileName << std::endl;
                return;
            }
            std::cout << "价格高于" << priceThreshold << "元的图书信息：" << std::endl;
            std::cout << std::setw(6) << std::left << "书号" 
                      << std::setw(12) << std::left << "书名" 
                      << std::setw(8) << std::left << "作者" 
                      << "单价" << std::endl;
            bool found = false;
            while(inFile >> tempBook){
                if(tempBook.BookPrice > priceThreshold){
                    std::cout << tempBook << std::endl;
                    found = true;
                }
            }
            if(!found){
                std::cout << "没有找到价格高于" << priceThreshold << "元的图书" << std::endl;
            }
            inFile.close();
        }
    inline bool ActionFindBookByID(const char* fileName, const char* bookID){
            Book tempBook;
            std::ifstream inFile(fileName,std::ios::in);
            if(!inFile.is_open()){
                std::cerr << "无法打开文件: " << fileName << std::endl;
                return false;
            }
            while(inFile >> tempBook){
                if(strcmp(tempBook.BookID, bookID) == 0){
                    std::cout << "找到图书：" << std::endl;
                    std::cout << std::setw(6) << std::left << "书号" 
                              << std::setw(12) << std::left << "书名" 
                              << std::setw(8) << std::left << "作者" 
                              << "单价" << std::endl;
                    std::cout << tempBook << std::endl;
                    inFile.close();
                    return true;
                }
            }
            inFile.close();
            return false;
        }
    inline void Menu(void){
        std::cout << "1、输入N（10<N<20）本图书的信息\n"
                    << "2、从ST1.DAT文件中读取图书数据，将价钱高于30元的图书信息输出\n"
                    << "3、输入书号，在ST1.DAT文件中查找该图书\n"
                    << "0、退出程序\n"
                    << "请选择操作(0-3): ";
    }
}
void signalHandler(int signum) {
    std::cout << "Interrupt signal (" << signum << ") received.\n";
    exit(signum);
}

int main(){
    std::signal(SIGINT, signalHandler);
    std::signal(SIGTERM, signalHandler);
    ActionCreateFile(DESTINATION);
    int choice;
    char bookID[BOOK_ID + 1]; 
    do {
        Menu();
        std::cin >> choice;
        
        switch(choice) {
            case 0:
                std::cout << "程序已退出" << std::endl;
                break;
                
            case 1: {
                int n;
                std::cout << "请输入要录入的图书数量(10<N<20): ";
                std::cin >> n;
                
                if(n <= 10 || n >= 20) {
                    std::cout << "图书数量必须在10到20之间！" << std::endl;
                    break;
                }
                
                std::cout << "请按以下格式输入" << n << "本图书信息：" << std::endl;
                std::cout << "书号(6字符) 书名(12字符) 作者(8字符) 单价" << std::endl;
                
                Book tempBook;
                for(int i = 0; i < n; i++) {
                    std::cout << "第" << (i+1) << "本图书: ";
                    std::cin >> tempBook;
                    ActionWriteFile(tempBook, DESTINATION);
                }
                std::cout << n << "本图书信息已保存到" << DESTINATION << "文件中" << std::endl;
                break;
            }
                
            case 2:
                ActionReadExpensiveBooks(DESTINATION, 30.0);
                break;
                
            case 3:
                std::cout << "请输入要查找的图书书号: ";
                std::cin >> bookID;
                if(!ActionFindBookByID(DESTINATION, bookID)) {
                    std::cout << "未找到书号为" << bookID << "的图书" << std::endl;
                }
                break;
                
            default:
                std::cout << "无效的选择，请重新输入" << std::endl;
        }
        
        if(choice != 0) {
            std::cout << "\n按Enter键继续...";
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cin.get();
            std::cout << std::string(50, '\n');
        }
        
    } while(choice != 0);
    
    return 0;
}