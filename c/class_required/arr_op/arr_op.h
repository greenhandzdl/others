#include <iostream>
#include <algorithm>
#include<ctype.h>
#include<cstring>

union ARR_PTR{
    int *int_arr;
    float *float_arr;
    double *double_arr;
    char *char_arr;  
};
typedef union ARR_PTR ARR_PTR;

struct USER_INPUT{
    char menu_choice;
    unsigned int arr_size;
    char arr_type;
    ARR_PTR arr_ptr;
};
typedef struct USER_INPUT USER_INPUT;
typedef USER_INPUT* friendly_user_input_type;//一个看起来还不错的抽象，目标是为了用户更方便的使用

#ifndef MAX
    #define MAX(a, b) ((a) > (b) ? (a) : (b))
#endif

#ifndef MIN
    #define MIN(a, b) ((a) > (b) ? (a) : (b))
#endif

using std::string;
using std::array;

using std::cout;
using std::endl;
using std::cin;

//排序（虽然有选择算法什么的，但同样的还是直接调用现成的类方法吧）
using std::min_element;
using std::max_element;

using std::exit;

//注意：不能修改原用户输入（没有提供），仅能重新制作新的用户输入 
friendly_user_input_type menu(void);//打印菜单，返回用户输入(已完成)


static void funct(friendly_user_input_type);//根据用户输入选择相应的函数执行（已完成）
friendly_user_input_type cop_arr(friendly_user_input_type);//一个公开的函数调用方法，主要用于拷贝数组之类（演示）

//一般初始化后要求用户输入数组
static void init_arr(friendly_user_input_type);//初始化数组（已完成）
static void input_reset_arr(friendly_user_input_type);//输入数组元素（已完成,危险操作：会重置数组）
static void print_arr_type(const friendly_user_input_type);//打印数组类型（已完成）
static void *get_current_pointer(const friendly_user_input_type) ;//获取当前数组指针（已完成）

static void print_USER_INPUT_info(const friendly_user_input_type);//打印数组信息（已完成）
void delete_USER_INPUT(friendly_user_input_type);//释放这个类型指针并且释放内存（已完成）
static void delete_arr(friendly_user_input_type);//删除数组(在对arr初始化时检查是否已经释放)
                            //TODO:再次执行时，可能对数组类型更改，先释放再初始一块区域赋值


static void reverse_arr(friendly_user_input_type);//翻转数组（已完成）

static void sort_arr(friendly_user_input_type);//排序数组(已完成，由小到到)

static void min_max_arr(friendly_user_input_type);//数组找最值（已完成）

static int analyze_arr(friendly_user_input_type);//数组统计（已完成）



static char safety_getchar_tolower(char&);//获取当个的字符输入并丢弃后面所有结果（已完成）
static void is_valid_char(char&,const char*);//与是否为有效字符比较（已完成）
static void eatline(void);//清理输入缓冲区（已完成）