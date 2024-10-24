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

USER_INPUT menu(void);//打印菜单，返回用户输入(已完成)
//TODO:返回friendly_user_input_type的函数，用new实现
//friendly_user_input_type menu(void);

static void funct(USER_INPUT&);//根据用户输入选择相应的函数执行
//TODO:使用friendly_user_input_types
//static void funct(friendly_user_input_type);

//一般初始化后要求用户输入数组
static void init_arr(friendly_user_input_type);//初始化数组（已完成）
static void input_reset_arr(friendly_user_input_type);//输入数组元素（已完成,危险操作：会重置数组）

static void *get_current_pointer(const friendly_user_input_type) ;//获取当前数组指针（已完成）

static void print_arr_info(const friendly_user_input_type);//打印数组信息（已完成）
void delete_USER_INPUT(friendly_user_input_type);//释放这个类型指针并且释放内存（TODO）
static void delete_arr(friendly_user_input_type);//删除数组(在对arr初始化时检查是否已经释放)
                            //TODO:再次执行时，可能对数组类型更改，先释放再初始一块区域赋值


static void reverse_arr(friendly_user_input_type);//翻转数组（已完成）

template <typename T>
static void copy_arr(__restrict T,const __restrict T);//拷贝数组

template <typename T>
static void find_arr(const T&,const T&);//查找数组

template <typename T>
static void sort_arr(const T&);//排序数组

template <typename T>
static void min_max_arr(const T&);//找最值 

template <typename T>
static void print_arr(const T&,const T&);//数组统计


static char safety_getchar_tolower(char&);//获取当个的字符输入并丢弃后面所有结果（已完成）
static void is_valid_char(char&,const char*);//与是否为有效字符比较（已完成）
static void eatline(void);//清理输入缓冲区（已完成）