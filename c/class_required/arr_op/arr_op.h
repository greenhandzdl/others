#include <iostream>
#include<ctype.h>
#include<cstring>

struct USER_INPUT{
    char menu_choice;
    unsigned int arr_size;
    char arr_type;
    union{
        int *int_arr;
        float *float_arr;
        double *double_arr;
        char *char_arr;  
    }arr_ptr;
};
typedef struct USER_INPUT USER_INPUT;

#ifdef MAX(a,b)
    #undef MAX(a,b)
#endif
#ifdef MIN(a,b)
    #undef MIN(a,b)
#endif

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) > (b) ? (a) : (b))

using std::string;
using std::array;

using std::cout;
using std::endl;
using std::cin;

USER_INPUT menu(void);//打印菜单，返回用户输入
void funct(const USER_INPUT&);//根据用户输入选择相应的函数执行

static void get_arr(USER_INPUT*);//获取数组


template <typename T>
void reverse_arr(const T&);//翻转数组

template <typename T>
void copy_arr(__restrict T,const __restrict T);//拷贝数组

template <typename T>
void find_arr(const T&,const T&);//查找数组

template <typename T>
void sort_arr(const T&);//排序数组

template <typename T>
void min_max_arr(const T&);//找最值 

template <typename T>
void print_arr(const T&,const T&);//数组统计

template <typename T>
void print_arr_info(const T&);//打印数组信息


static char safety_getchar_tolower(char&);
static void is_valid_char(char&,char[]);
static void eatline(void);