// 待相关算法：数组反转、复制、查找、排序、找最值、数组统计。
// 已经完成：打印菜单，显示功能。

#include "arr_op.h"

friendly_user_input_type menu(void){
    friendly_user_input_type user_input = new USER_INPUT;
    
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
    is_valid_char(user_input->menu_choice,"rcfsmaen");


    cout 
        << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    cout << "* i.int类型                                         *" << endl;
    cout << "* f.float类型                                       *" << endl;
    cout << "* d.double类型                                       *" << endl;
    cout << "* c.char类型                                *" << endl;
    cout << "请输入数组类型:" << endl;
    is_valid_char(user_input->arr_type,"ifdc");


    cout
        << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    cout << "请输入数组大小:" << endl;
    while(!(cin >> user_input->arr_size)){
        cout << "输入发生错误，正在尝试解决" << endl;
        cout << "如果多次出现该错误，请退出程序" << endl;
        eatline(); 
    } 
    eatline();
    cout << "******************************************************" << endl
        << endl
        << "******************************************************" << endl;
    
    init_arr(user_input);

    funct(user_input);
    
    return user_input;
}

static void funct(friendly_user_input_type user_input){
    cout << "当前你的数组是:" << endl;
    print_USER_INPUT_info(user_input);
    cout << endl
        << "******************************************************" << endl
        << "现在你的数组是:" << endl;
        
    switch (user_input->menu_choice){
        case 'r':
            reverse_arr(user_input);
            break;
        case 'c':
            cout << "暂时不支持菜单操作，编写代码时可参考funct()函数写法" <<endl;
            {
                //fallthrough 导致了控制流跳过了 deamon_arr 的初始化
                friendly_user_input_type deamon_arr = cop_arr(user_input);
                print_USER_INPUT_info(deamon_arr);
                delete_USER_INPUT(deamon_arr);
            }
            break;
        case 's':
            sort_arr(user_input);
            break;
        case 'm':
            min_max_arr(user_input);
            break;
        case 'f':
            [[fallthrough]];//查找数组感觉差不多
        case 'a':
            analyze_arr(user_input);
            break;
        default:
            cout << "无操作" << endl;
            break;
    }

    cout << endl
        << "******************************************************" << endl
        << "现在你的数组是:" << endl;
    print_USER_INPUT_info(user_input);
}

friendly_user_input_type cop_arr(friendly_user_input_type user_input){
    friendly_user_input_type copy_user_input = new USER_INPUT;
    *copy_user_input = *user_input; // 深拷贝 user_input 的内容
    copy_user_input->arr_ptr.int_arr = nullptr;
    copy_user_input->arr_ptr.float_arr = nullptr;
    copy_user_input->arr_ptr.double_arr = nullptr;
    copy_user_input->arr_ptr.char_arr = nullptr;
    switch (copy_user_input->arr_type){
        case 'i':
            if( ( copy_user_input->arr_ptr.int_arr = new int[copy_user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
                }
            break;
       case 'f':
            if( (copy_user_input->arr_ptr.float_arr = new float[copy_user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case 'd':
            if( (copy_user_input->arr_ptr.double_arr = new double[copy_user_input->arr_size]) == NULL ){
                cout << "内存申请失败,程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        case 'c':
            if( (copy_user_input->arr_ptr.char_arr = new char[copy_user_input->arr_size]) == NULL ){
                cout << "内存申请失败，程序退出" << endl;
                exit(EXIT_FAILURE);
            }
            break;
        default:
            cout << "输入错误，程序退出" << endl;
            exit(EXIT_FAILURE);
            break;
    }
    //复制到新的堆里来
    for(int i = 0; i < copy_user_input->arr_size; i++){
        switch (copy_user_input->arr_type){
            case 'i':
                copy_user_input->arr_ptr.int_arr[i] = user_input->arr_ptr.int_arr[i];
                break;
            case 'f':
                copy_user_input->arr_ptr.float_arr[i] = user_input->arr_ptr.float_arr[i];
               break;
            case 'd':
                copy_user_input->arr_ptr.double_arr[i] = user_input->arr_ptr.double_arr[i];
                break;
            case 'c':
                copy_user_input->arr_ptr.char_arr[i] = user_input->arr_ptr.char_arr[i];
                break;
            default:
                cout << "类型错误，程序退出" << endl;
                exit(EXIT_FAILURE);
        }
    }
    return copy_user_input;
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
static void print_arr_type(const friendly_user_input_type user_input){
    switch (user_input->arr_type) {
        case 'i':
            cout << "整型 (int)";
            break;
        case 'f':
            cout << "浮点型 (float)";
            break;
        case 'd':
            cout << "双精度浮点型 (double)";
            break;
        case 'c':
            cout << "字符型 (char)" ;
            break;
        default:
            std::cerr << "无效的数组类型" ;
            break;
    }
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
static void print_USER_INPUT_info(const friendly_user_input_type user_input){
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

void delete_USER_INPUT(friendly_user_input_type user_input){
    if(user_input){
        delete_arr(user_input);
        delete user_input;
    }
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
            cout << "类型错误，程序退出" << std::endl;
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
                cout << "类型错误，程序退出" << std::endl;
                std::exit(EXIT_FAILURE);
        }
    }
}

static void sort_arr(friendly_user_input_type user_input) {
    void *ptr = get_current_pointer(user_input);
    if (ptr) {
        switch (user_input->arr_type) {
            case 'i': {
                int* int_ptr = static_cast<int*>(ptr);
                std::sort(int_ptr, int_ptr + user_input->arr_size);
                break;
            }
            case 'f': {
                float* float_ptr = static_cast<float*>(ptr);
                std::sort(float_ptr, float_ptr + user_input->arr_size);
                break;
            }
            case 'd': {
                double* double_ptr = static_cast<double*>(ptr);
                std::sort(double_ptr, double_ptr + user_input->arr_size);
                break;
            }
            case 'c': {
                char* char_ptr = static_cast<char*>(ptr);
                std::sort(char_ptr, char_ptr + user_input->arr_size);
                break;
            }
            default:
                cout << "类型错误，程序退出" << std::endl;
                std::exit(EXIT_FAILURE);
        }
    }
}
static void min_max_arr(friendly_user_input_type user_input) {
    switch (user_input->arr_type) {
        case 'i': {
            int* int_ptr = static_cast<int*>(get_current_pointer(user_input));
            cout << "最小值为" << *min_element(int_ptr, int_ptr + user_input->arr_size) << std::endl;
            cout << "最大值为" << *max_element(int_ptr, int_ptr + user_input->arr_size) << std::endl;
            break;
        }
        case 'f': {
            float* float_ptr = static_cast<float*>(get_current_pointer(user_input));
            cout << "最小值为" << *min_element(float_ptr, float_ptr + user_input->arr_size) << std::endl;
            cout << "最大值为"<< *max_element(float_ptr, float_ptr + user_input->arr_size) << std::endl;
            break;
        }
        case 'd': {
            double* double_ptr = static_cast<double*>(get_current_pointer(user_input));
            cout << "最小值为" << *min_element(double_ptr, double_ptr + user_input->arr_size) << std::endl;
            cout << "最大值为" << *max_element(double_ptr, double_ptr + user_input->arr_size) << std::endl;
            break;
        }
        case 'c': {
            char* char_ptr = static_cast<char*>(get_current_pointer(user_input));
            cout << "最小值为" << *min_element(char_ptr, char_ptr + user_input->arr_size) << std::endl;
            cout << "最大值为" << *max_element(char_ptr, char_ptr + user_input->arr_size) << std::endl;
            break;
        }
    }
}
static int analyze_arr(friendly_user_input_type user_input){
    cout << endl
    << "******************************************************" << endl
    << "******************************************************" << endl
    //通过user_input->arr_type来创建相应类型变量供cin使用
    << "这个数组是" ;
    print_arr_type(user_input);
    cout << "类型" << endl;
    cout << "请输入要查找元素（0为不存在）：";
    unsigned int tmp (0),count (0);
    switch(user_input->arr_type){
        case 'i':
            int ifind_ele;
            if(cin >> ifind_ele);
            else{
                cout << "查找元素错误" <<endl;
                eatline();
            }
            while(tmp < user_input->arr_size){
                if(user_input->arr_ptr.int_arr[tmp++] == ifind_ele){
                    count++;
                    cout << "元素" << ifind_ele << "在数组中第" << tmp << "个位置" << endl;
                }
            }
            if(count)
                cout << "元素" << ifind_ele << "在数组中一共出现了" << count << "次" << endl;
            else
                cout << "元素" << ifind_ele << "在数组中不存在" << endl;
        break;
        case 'f':
            float ffind_ele;
            if(cin >> ffind_ele);
            else{
                cout << "查找元素错误" <<endl;
                eatline();
            }
            while(tmp < user_input->arr_size){
                if(user_input->arr_ptr.float_arr[tmp++] == ffind_ele){
                    count++;
                    cout << "元素" << ffind_ele << "在数组中第" << tmp << "个位置" << endl;
                }
            }
            if(count)
                cout << "元素" << ffind_ele << "在数组中一共出现了" << count << "次" << endl;
            else
                cout << "元素" << ffind_ele << "在数组中不存在" << endl;
            break;
        case 'd':   
                double dfind_ele;
                if(cin >> dfind_ele);
                else{
                    cout << "查找元素错误" <<endl;
                    eatline();
                }
                while(tmp < user_input->arr_size){
                    if(user_input->arr_ptr.double_arr[tmp++] == dfind_ele){
                        count++;
                        cout << "元素" << dfind_ele << "在数组中第" << tmp << "个位置" << endl;
                    }
                }  
                if(count)
                    cout << "元素" << dfind_ele << "在数组中一共出现了" << count << "次" << endl;
                else
                    cout << "元素" << dfind_ele << "在数组中不存在" << endl;
        break;
        case 'c':
            char cfind_ele;
            if(cin >> cfind_ele);
            else{
                cout << "查找元素错误" <<endl;
                eatline();
            }
            while(tmp < user_input->arr_size){
                if(user_input->arr_ptr.char_arr[tmp++] == cfind_ele){
                    count++;
                    cout << "元素" << cfind_ele << "在数组中第" << tmp << "个位置" << endl;
                }
            } 
            if(count)
                cout << "元素" << cfind_ele << "在数组中一共出现了" << count << "次" << endl;
            else
                cout << "元素" << cfind_ele << "在数组中不存在" << endl;
            break;
            default:
                cout << "类型错误，程序退出" << endl;
                exit(EXIT_FAILURE);
            break;    
    }
    cout 
    << "******************************************************" << endl
    << "******************************************************" << endl;
    return count;
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