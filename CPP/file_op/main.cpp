#include<iostream>
#include<fstream>
#include<iomanip>
#include<memory> // For auto_ptr library
#include<limits>   

enum MenuOptions{
    EXIT = 1,
    MAKE_FILE,
    READ_FILE,
    WRITE_FILE,
};

/*
* 教训：
* 1.clog和cerr仅仅应该用于调试目的。
* 2.函数返回错误码是设计正常逻辑而不是错误处理。
* 3.当程序发生错误时，应该输出到debug文件，而不是输出到屏幕。
*/
/**
 * @brief 显示菜单并获取用户选择
 * 
 * 该函数显示一个菜单，并尝试从用户那里获取一个有效的菜单选项。它使用枚举类型MenuOptions来表示菜单选项。
 * 函数通过引用参数choice返回用户的选择。如果用户输入无效或输入非整数值，函数将抛出std::ios_base::failure异常。
 * 
 * @param choice 引用参数，用于返回用户选择的菜单选项
 * @return true 如果用户输入有效且未抛出异常，则返回true
 * @return false 如果用户输入无效，则返回false
 * @throws std::ios_base::failure 如果用户输入非整数值，则抛出异常
 */
// c17 bool menu(enum MenuOptions& choice) throw(std::ios_base::failure)
bool menu(enum MenuOptions& choice){
    using namespace std;

    cin.exceptions(std::ios::failbit);

    cout << internal
        << setw(12) << "Menu" << endl
        << left
        << setfill('=')
        << setw(24) << "====" << endl
        << setfill(' ')
        << setw(12) << "1.Exit" 
        << setw(12) << "2.Make File" << endl
        << setw(12) << "3.Read File" 
        << setw(12) << "4.Write File" << endl
        << setfill('*')
        << setw(12) << "Choice: "
        << "\b\b\b\b"
        << setfill(' ') << right;

    int userInput;
    try{
        cin >> userInput;
        if(userInput < 1 || userInput > 4){
            clog << "输入错误，返回" << endl;
            return false;
        } 
        choice = static_cast<enum MenuOptions>(userInput);
        return true;
    }catch(std::ios::failure& e){
        std::cerr << e.what() << std::endl;
        std::clog << "检测输入不是int类型" << std::endl;
        throw;
    }
    return false;
}
/**
 * 获取用户输入的文件名
 * 
 * @param filename 引用参数，用于存储用户输入的文件名
 * @return bool 表示是否成功读取到文件名
 * 
 * 此函数负责提示用户输入文件名，并将输入的文件名存储在传入的字符串引用中
 * 如果输入成功，则返回true；如果输入失败（例如输入流遇到错误），则返回false
 */
bool filename_get(std::string &filename){
    using namespace std;
    cout << "请输入文件名：";
    if(cin >> filename)
        return true;
    return false;
}
/**
 * 尝试创建一个指定名称的文件。
 * 
 * 该函数接受一个字符串参数作为文件名，尝试创建一个具有该名称的空文件。
 * 如果文件成功创建，函数返回true；如果文件打开失败，则输出错误信息并返回false。
 * 
 * @param filename 指定要创建的文件的名称。
 * @return 返回true表示文件成功创建，返回false表示文件创建失败。
 */
bool file_make(std::string &filename){
    using namespace std;
    ofstream file(filename.c_str(), ios_base::out|ios_base::trunc);
    if(!file.is_open()){
        cerr << "文件打开失败" << endl;
        return false;
    }
    file << "" << flush;
    file.close();
    file.clear();
    return true;
}
/**
 * 读取文件内容并输出到标准输出
 * 
 * @param filename 文件名引用，用于指定要读取的文件
 * @return bool 表示文件读取是否成功的布尔值
 */
bool file_read(std::string &filename){
    using namespace std;
    ifstream file(filename.c_str(), ios_base::in);
    if(!file.is_open()){
        cerr << "文件打开失败" << endl;
        return false;
    }
    copy(istreambuf_iterator<char>(file), istreambuf_iterator<char>(), ostreambuf_iterator<char>(cout));
    file.close();
    file.clear();
    return true;
}
/**
 * 将用户输入的数据追加到指定的文件中
 * 
 * @param filename 要写入的文件的名称
 * @return 文件是否成功打开并写入数据
 * 
 * 该函数尝试打开一个文件以追加写入用户从标准输入输入的数据
 * 如果文件打开失败，将输出错误信息并返回false
 * 如果文件成功打开，将从标准输入读取数据直到遇到EOF（Ctrl+D），然后将这些数据写入文件中
 * 写入完成后，确保文件正确关闭，并清除cin的EOF状态，使cin可以继续用于下一次输入
 */
bool file_write(std::string &filename){
    using namespace std;
    ofstream file(filename.c_str(), ios_base::out|ios_base::app);
    if(!file.is_open()){
        cerr << "文件打开失败" << endl;
        return false;
    }
    copy(istreambuf_iterator<char>(cin), istreambuf_iterator<char>(), ostreambuf_iterator<char>(file));
    //处理cin的EOF信号(Ctrl+D)，并且恢复可用
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    file.flush();
    file.close();
    file.clear();
    return true;
}
int main(void){
    enum MenuOptions choice;
    std::string filename;
    std::cout << "欢迎使用文件操作程序" << std::endl;
    try{
        while(!menu(choice));
        filename_get(filename);
    }catch(std::ios::failure& e){
        std::cerr << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }
    switch (choice){
        case MAKE_FILE:
            std::cout << "创建文件" << std::endl;
            file_make(filename);
            break;
        case READ_FILE:
            std::cout << "读取文件" << std::endl;
            file_read(filename);
            break;
        case WRITE_FILE:
            std::cout << "写入文件" << std::endl;
            std::cout << "Unix使用Ctrl+D结束输入，Windows使用Ctrl+Z结束输入"<<std::endl;
            file_write(filename);
            break;
        //flow control
        case EXIT:
        default:
            std::cout << "退出程序" << std::endl;
            exit(EXIT_SUCCESS);
            break;
    }
}