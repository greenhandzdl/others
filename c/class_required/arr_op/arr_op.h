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
static void funct(USER_INPUT&);//根据用户输入选择相应的函数执行

static void init_arr(USER_INPUT*);//初始化数组（已完成）
static void input_arr(USER_INPUT*);//输入数组元素（已完成，供init_arr()使用）（TODO）
static void *get_current_pointer(const USER_INPUT*) ;//获取当前指针（已完成）

static void print_arr_info(const USER_INPUT*);//打印数组信息（已完成）
void delete_USER_INPUT(USER_INPUT*);//删除数组(在对arr初始化时检查是否已经释放)
                            //TODO:再次执行时，可能对数组类型更改，先释放再初始一块区域赋值


static void reverse_arr(USER_INPUT*);//翻转数组（已完成）

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