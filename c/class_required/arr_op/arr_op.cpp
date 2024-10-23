// 数组的相关算法：数组反转、复制、查找、排序、找最值、数组统计。
// 打印菜单，显示功能

#include "arr_op.h"

USER_INPUT menu(void){
    USER_INPUT user_input = {0};
    
    char temp[2];
    int count (0);
    
    cout << "******************************************************" << endl;
    cout << "* r.数组反转                                         *" << endl;
    cout << "* c.数组复制                                         *" << endl;
    cout << "* f.查找数组元素                                     *" << endl;
    cout << "* s.数组排序                                         *" << endl;
    cout << "* m.数组最大值、最小值                               *" << endl;
    cout << "* a.数组统计                                         *" << endl;
    cout << "* e.退出                                             *" << endl;
    cout << "* 输入你的选择:                                         *" << endl;
    is_valid_char(user_input.menu_choice,"rcfsmae");


    cout << "******************************************************" << endl;
    cout << "******************************************************" << endl;
    cout << "* i.int类型                                         *" << endl;
    cout << "* f.float类型                                       *" << endl;
    cout << "* d.double类型                                       *" << endl;
    cout << "请输入数组类型:" << endl;
    is_valid_char(user_input.arr_type,"ifd");


    cout << "******************************************************" << endl;
    cout << "******************************************************" << endl;
    cout << "请输入数组大小:" << endl;
    while(!(cin >> user_input.arr_size)){
        cout << "输入发生错误，正在尝试解决" << endl;
        cout << "如果多次出现该错误，请退出程序" << endl;
        eatline();
    } 
    eatline();
    
    get_arr(&user_input);
    
    return user_input;
}

static void get_arr(USER_INPUT* user_input){
    switch (user_input->arr_type){
        case 'i':
            if( ( user_input->arr_ptr.int_arr = new int[user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
                }
            break;
       case 'f':
            if( (user_input->arr_ptr.float_arr = new float[user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            if( (user_input->arr_ptr.double_arr = new double[user_input->arr_size]) == NULL ){
                cout << "内存申请失败,程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        default:
            cout << "输入错误，程序退出" << endl;
            exit(EXIT_FAILURE);
    }
}

static char safety_getchar_tolower(char& ch){
    while(!cin.get(ch)){
        cout << "输入发生错误，正在尝试解决" << endl;
        cout << "如果多次出现该错误，请退出程序" << endl;
        eatline();
    }
    eatline();
    ch = tolower(ch);
    return ch;
}
static void is_valid_char(char& input,char ch[]){
    int count (0);
    char temp[2] = {'\0'};
    do{
        if(count++)
            cout << "输入错误，请重新输入:" << endl;
        safety_getchar_tolower(input);
        temp[0] = input;
    }while(strpbrk(temp,ch));
}
static void eatline(void){
    cin.clear();
    cin.sync();
}
