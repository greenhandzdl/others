// 待相关算法：数组反转、复制、查找、排序、找最值、数组统计。
// 已经完成：打印菜单，显示功能。

#include "arr_op.h"

USER_INPUT menu(void){
    USER_INPUT user_input = {0};
    
    int count (0);
    
    cout << "******************************************************" << endl;
    cout << "* r.数组反转                                         *" << endl;
    cout << "* c.数组复制                                         *" << endl;
    cout << "* f.查找数组元素                                     *" << endl;
    cout << "* s.数组排序                                         *" << endl;
    cout << "* m.数组最大值、最小值                               *" << endl;
    cout << "* a.数组统计                                         *" << endl;
    cout << "* n.无操作)                                           *" << endl;
    cout << "* 输入你的选择功能（ctrl c退出）:                                         *" << endl;
    is_valid_char(user_input.menu_choice,"rcfsmaen");


    cout 
        << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    cout << "* i.int类型                                         *" << endl;
    cout << "* f.float类型                                       *" << endl;
    cout << "* d.double类型                                       *" << endl;
    cout << "* c.char类型                                *" << endl;
    cout << "请输入数组类型:" << endl;
    is_valid_char(user_input.arr_type,"ifdc");


    cout
        << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    cout << "请输入数组大小:" << endl;
    while(!(cin >> user_input.arr_size)){
        cout << "输入发生错误，正在尝试解决" << endl;
        cout << "如果多次出现该错误，请退出程序" << endl;
        eatline(); 
    } 
    eatline();
    cout << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    
    init_arr(&user_input);

    funct(user_input);
    
    return user_input;
}

static void funct(USER_INPUT& user_input){
    cout << "当前你的数组是:" << endl;
    print_arr_info(&user_input);
    switch (user_input.menu_choice){
        case 'r':
            reverse_arr(&user_input);
            break;
        case 'c':
            //copy_arr(dest,user_input.arr_ptr);
            break;
        case 'f':
            //find_arr(user_input.arr_ptr,"用户输入的元素");
            break;
        case 's':
            //sort_arr(user_input.arr_ptr);
            break;
        case 'm':
            //max_min_arr(user_input.arr_ptr);
            break;
        case 'a':
            //arr_statistics(user_input.arr_ptr);
            break;
        default:
            cout << "无操作" << endl;
            break;
    }
    cout << "现在你的数组是:" << endl;
    print_arr_info(&user_input);
}

static void init_arr(friendly_user_input_type user_input){
    if(get_current_pointer(user_input))
        delete_arr(user_input);
    
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
        case 'c':
            if( (user_input->arr_ptr.char_arr = new char[user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        default:
            cout << "输入错误，程序退出" << endl;
            exit(EXIT_FAILURE);
    }
    input_reset_arr(user_input);
}
//这个函数用于整个的输入
//TODO:写一个函数原型用于某个位置元素修改吧？
static void input_reset_arr(friendly_user_input_type user_input){
    cout << "请输入数组元素:" << endl;
    for(int i = 0; i < user_input->arr_size; i++){
        switch (user_input->arr_type){
            case 'i':
                if(cin >> user_input->arr_ptr.int_arr[i]);
                else{
                    cout << "输入已出现问题，所以后面输入元素已被重置，请重新输入元素"
                        << (i+1)
                        << "后的元素" << endl;
                    --i;
                    eatline();
                }
                break;
            case 'f':
                if(cin >> user_input->arr_ptr.float_arr[i]);
                else{
                    cout << "输入已出现问题，所以后面输入元素已被重置，请重新输入元素"
                        << (i+1)
                        << "后的元素" << endl;
                    --i;
                    eatline();
                }
                break;
            case 'd':
                if(cin >> user_input->arr_ptr.double_arr[i]);
                else{
                    cout << "输入已出现问题，所以后面输入元素已被重置，请重新输入元素"
                        << (i+1)
                        << "后的元素" << endl;
                    --i;
                    eatline();
                }
                break;
            case 'c':
                cin >> user_input->arr_ptr.char_arr[i];
                break;
            default:
                cout << "输入错误，程序退出"<< endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
    eatline();//清理下换行符或者超出数组边界什么的，上面会忽视这些空白字符
}
//好像没什么用(当模版吧)
static void *get_current_pointer(const friendly_user_input_type user_input){
    switch (user_input->arr_type){
    case 'i':
        return user_input->arr_ptr.int_arr;
        break;
    case 'f':
        return user_input->arr_ptr.float_arr;
        break;
    case 'd':
        return user_input->arr_ptr.double_arr;
        break;
    case 'c':
        return user_input->arr_ptr.char_arr;
        break;
    default:
        cout << "类型错误，程序退出" << endl;
        exit(EXIT_FAILURE);
    }
}
static void print_arr_info(const friendly_user_input_type user_input){
    cout << "数组类型:";
    switch (user_input->arr_type){
        case 'i':
            cout << "int" << endl;
            break;
        case 'f':
            cout << "float" << endl;
            break;
        case 'd':
            cout << "double" << endl;
            break;
        case 'c':
            cout << "char" << endl;
            break;
        
        default:
            cout << "类型错误，程序退出" << endl;
            exit(EXIT_FAILURE);
    }
    cout
        <<"数组大小:" << user_input->arr_size << endl
        << "数组元素:" << endl;
    //由于new出来的数组会被自动初始化，所以char不用担心'\0'，但是对于非char类型数组仍可能会出现末尾一堆0（TODO：在输入的时候动态调整size，可以缩小）
    //对于缓存区中向变量输入int这些类型时，如果恰改是输入了其他字符，cin将一直忽视（读取失败），后面将为0.
    for(int i = 0; i < user_input->arr_size; i++){
        switch (user_input->arr_type){
            case 'i':
                cout << user_input->arr_ptr.int_arr[i] << " ";
                break;
            case 'f':
                cout << user_input->arr_ptr.float_arr[i] << " ";
                break;
            case 'd':
                cout << user_input->arr_ptr.double_arr[i] << " ";
                break;
            case 'c':
                cout << user_input->arr_ptr.char_arr[i] << " ";
                break;
            default:
                cout << "类型错误，程序退出" << endl;
                exit(EXIT_FAILURE);
                break;
        }
    }
    cout << endl
    << "******************************************************" << endl
    << "******************************************************" << endl;
}
static void delete_arr(friendly_user_input_type user_input) {
    void *ptr = get_current_pointer(user_input);
    if (ptr) {
        switch (user_input->arr_type) {
        case 'i':
            delete [] static_cast<int*>(ptr);
            break;
        case 'f':
            delete [] static_cast<float*>(ptr);
            break;
        case 'd':
            delete [] static_cast<double*>(ptr);
            break;
        case 'c':
            delete [] static_cast<char*>(ptr);
            break;
        default:
            std::cout << "类型错误，程序退出" << std::endl;
            std::exit(EXIT_FAILURE);
        }
    }
}

//虽然我想用前和后来交换，但之前写过这个作业，就偷偷懒吧
static void reverse_arr(friendly_user_input_type user_input) {
    void *ptr = get_current_pointer(user_input);
    if (ptr) {
        switch (user_input->arr_type) {
            case 'i': {
                int* int_ptr = static_cast<int*>(ptr);
                std::reverse(int_ptr, int_ptr + user_input->arr_size);
                break;
            }
            case 'f': {
                float* float_ptr = static_cast<float*>(ptr);
                std::reverse(float_ptr, float_ptr + user_input->arr_size);
                break;
            }
            case 'd': {
                double* double_ptr = static_cast<double*>(ptr);
                std::reverse(double_ptr, double_ptr + user_input->arr_size);
                break;
            }
            case 'c': {
                char* char_ptr = static_cast<char*>(ptr);
                std::reverse(char_ptr, char_ptr + user_input->arr_size);
                break;
            }
            default:
                std::cout << "类型错误，程序退出" << std::endl;
                std::exit(EXIT_FAILURE);
        }
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
static void is_valid_char(char& input,const char* ch){
    unsigned int count (0);
    char temp[2] = {'\0'};
    do{
        if(count++)
            cout << "输入错误，请重新输入:" << endl;
        safety_getchar_tolower(input);
        temp[0] = input;
    }while(strpbrk(temp,ch) == nullptr);
}
static void eatline() {
    std::cin.clear();  // 清除错误标志
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');  // 忽略直到换行符
}