/*
3．学生成绩统计 
要求有5个班级的数据，每个班级至少有30名以上的同学，至少有5门以上的课程。分 别实现下列功能：【注：数据通过随机函数产生】
（1）能够实现各种查询（分别根据学生姓名 、学号、班级、课程名称等）。
（2）能够查询每个课程的最高分、最低分及相应学生姓名、班级和学号。【最高分或最低分有多个同学的，都要罗列出来】

编程要求：
1.较好的用户输入输出提示信息
2.使用子函数来实现上述各个功能 
3.尽量少用全局变量
4.建议实验指导老师先规划或写出主程序模块名称，学生具体实现功能

提示：定义一个学生成绩信息的结构体类型，然后在此基础上编程。 typedef struct {
char stu_number[20];//学号
char stu_name[20];	//姓名 int class_number;	//班级号
int cprog_score;	//C程序成int eng_score;	//英语成绩 int math_score;	//高数成绩 int phy_score;	//物理成绩 int pe_score;...	//体育成绩
} StuInfo; 关于class_number班级号属性，可以作为成员，也可以不作为成员，而用 ourgrade[class_number][n]来表示,也即用二维结构体数组，前面的属性表 示班级号，后面的属性表示第n个学生的成绩。it's up to you! 例如：ourgrade[2][10].cprog_score=90;就是将3班的第11个同学的C程序 设计成绩赋值为90.(当然，下标【0】也可以不用，这样就表示2班的第10个 同学的C程序设计成绩）

*/

// gcc -finput-charset=UTF-8 -fexec-charset=UTF-8 main3.c -o main3.out && ./main3.out
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <wchar.h>
#include <locale.h>
#include <limits.h>

#define CLASS_MEN 30

typedef struct {
    int stu_number;   // 学号
    wchar_t stu_name[20]; // 姓名
    int class_number; // 班级号
    int cprog_score;  // C程序成绩
    int eng_score;    // 英语成绩
    int math_score;   // 高数成绩
    int phy_score;    // 物理成绩
    int pe_score;     // 体育成绩
} StuInfo;

typedef enum {
    CPROG_SCORE = 1, // C程序成绩
    ENG_SCORE,       // 英语成绩
    MATH_SCORE,      // 高数成绩
    PHY_SCORE,       // 物理成绩
    PE_SCORE         // 体育成绩
} CourseScore;

typedef StuInfo ClassInfo[CLASS_MEN];

const wchar_t* getRandomChar(const wchar_t* str) {
    int len = wcslen(str);
    int index = rand() % len;
    return str + index;
}

void generateChineseName(wchar_t* name, size_t size) {
    if (size < 4) {
        fwprintf(stderr, L"目标数组太小，无法存储中文名字。\n");
        return;
    }
    static const wchar_t first_names[] = L"张王李赵孙周吴郑王冯陈褚卫蒋沈韩杨朱秦尤许何吕施张孔曹严华金魏陶姜戚谢邹喻柏水窦章云苏潘葛奚范彭郎鲁韦昌马苗凤花方俞任袁柳酆鲍史唐费廉岑薛雷贺倪汤滕殷罗毕郝邬安常乐于时傅皮卞齐康伍余元卜顾孟平黄和穆萧尹姚邵湛汪祁毛禹狄米贝明臧计伏成戴谈宋茅庞熊纪舒屈项祝董梁杜阮蓝闵席季麻强贾路娄危江童颜郭梅盛林刁钟徐邱骆高夏蔡田樊胡凌霍虞万支柯昝管卢莫经房裘缪干解应宗丁宣贲邓郁单杭洪包诸左石崔吉钮龚程嵇邢滑裴陆荣翁荀羊於惠甄魏加封赖劳秦矫卜詹牟缪阎池乔阴郁胥能苍双闻莘党翟谭贡劳逄姬申扶堵冉宰郦雍却璩桑桂濮牛寿通边扈燕冀郏浦尚农温别庄晏柴瞿阎充慕连茹习宦艾鱼容向古易慎戈廖庾终暨居衡步都耿满弘匡国文寇广禄阙东殴殳沃利蔚越夔隆师巩厍聂晁勾敖融冷訾辛阚那简饶空曾毋沙乜养鞠须丰巢关蒯相查后荆红游竺权逯盖益桓公万俟司马上官欧阳夏侯诸葛闻人东方赫连皇甫尉迟公羊澹台公冶宗政濮阳淳于仲孙太叔申屠公孙慕容鲜于宇文司徒司空亓官司寇仉督子车颛孙端木巫马公西漆雕乐正壤驷公良拓跋夹谷宰父谷粱段干百里东郭南郭呼延羊舌微生岳帅缑亢况后羿乐悦";
    static const wchar_t last_names[] = L"伟刚强勇毅俊峰峻峰灵秀英艳娇燕萍静淑惠琴心妍婉颖君兰芳华梅琳敏静佳莲娟红娥玲芬芳燕虹莉琼霞珍贞莉萍红娥玲芬芳燕虹莉琼霞珍贞";
    wchar_t firstName = getRandomChar(first_names)[0];
    wchar_t lastName = getRandomChar(last_names)[0];
    swprintf(name, size, L"%lc%lc", firstName, lastName);
}

void rand_data(StuInfo* stu, int stu_number, int class_number) {
    static int initialized = 0;
    if (!initialized) {
        srand((unsigned)time(NULL));
        initialized = 1;
    }

    stu->stu_number = stu_number;
    generateChineseName(stu->stu_name, sizeof(stu->stu_name) / sizeof(wchar_t));
    stu->class_number = class_number;

    stu->cprog_score = rand() % 100;
    stu->eng_score = rand() % 100;
    stu->math_score = rand() % 100;
    stu->phy_score = rand() % 100;
    stu->pe_score = rand() % 100;
}

void print_data(StuInfo* stu) {
    wprintf(L"学号:%d 姓名:%ls 班级:%d C程序成绩:%d 英语成绩:%d 高数成绩:%d 物理成绩:%d 体育成绩:%d\n",
           stu->stu_number, stu->stu_name, stu->class_number, stu->cprog_score, stu->eng_score, stu->math_score,
           stu->phy_score, stu->pe_score);
}

void c_print_data(ClassInfo* class_info, int class_number) {
    for (int i = 0; i < class_number; i++) {
        print_data(&(*class_info)[i]);
    }
}

ClassInfo* c_rand_data(const int class_number) {
    ClassInfo* class_info = (ClassInfo*)malloc(sizeof(ClassInfo));
    for (int i = 0; i < CLASS_MEN; i++) {
        rand_data(&(*class_info)[i], i + 1, class_number);
    }
    return class_info;
}

int menu(void) {
    wprintf(L"欢迎使用学生成绩查询系统\n");
    wprintf(L"请选择查询选项:\n");
    wprintf(L"1. 根据学生姓名查询\n");
    wprintf(L"2. 根据学号查询\n");
    wprintf(L"3. 根据班级查询\n");
    wprintf(L"4. 根据课程名称查询\n");
    wprintf(L"5. 查询每个课程的最高分及相应学生信息\n");
    wprintf(L"6. 查询每个课程的最低分及相应学生信息\n");
    wprintf(L"0. 退出系统\n");
    int choice;
    scanf("%d", &choice);
    if (choice < 1 || choice > 6) {
        wprintf(L"已退出！\n");
        exit(EXIT_SUCCESS);
    }
    return choice;
}

void print_student_info_according_to_name(ClassInfo* class_info, int class_number, const wchar_t* name) {
    for (int i = 0; i < class_number; i++) {
        if (wcscmp((*class_info)[i].stu_name, name) == 0) {
            print_data(&(*class_info)[i]);
        }
    }
}
void print_student_info_according_to_number(ClassInfo* class_info, int class_number, int number) {
    for (int i = 0; i < class_number; i++) {
        if ((*class_info)[i].stu_number == number) {
            print_data(&(*class_info)[i]);
        }
    }
}
void print_student_info_sort_max_and_min(ClassInfo* class_info, int class_number, CourseScore course) {
    int max_score = INT_MIN;
    int min_score = INT_MAX;
    int max_indices[CLASS_MEN] = {0};
    int min_indices[CLASS_MEN] = {0};
    int max_count = 0;
    int min_count = 0;

    for (int i = 0; i < class_number; i++) {
        int score = 0;
        switch (course) {
            case CPROG_SCORE:
                score = (*class_info)[i].cprog_score;
                break;
            case ENG_SCORE:
                score = (*class_info)[i].eng_score;
                break;
            case MATH_SCORE:
                score = (*class_info)[i].math_score;
                break;
            case PHY_SCORE:
                score = (*class_info)[i].phy_score;
                break;
            case PE_SCORE:
                score = (*class_info)[i].pe_score;
                break;
        }

        if (score > max_score) {
            max_score = score;
            max_count = 1;
            max_indices[0] = i;
        } else if (score == max_score) {
            max_indices[max_count++] = i;
        }

        if (score < min_score) {
            min_score = score;
            min_count = 1;
            min_indices[0] = i;
        } else if (score == min_score) {
            min_indices[min_count++] = i;
        }
    }

    wprintf(L"最高分: %d\n", max_score);
    for (int i = 0; i < max_count; i++) {
        print_data(&(*class_info)[max_indices[i]]);
    }

    wprintf(L"最低分: %d\n", min_score);
    for (int i = 0; i < min_count; i++) {
        print_data(&(*class_info)[min_indices[i]]);
    }
}

int main(void) {
    setlocale(LC_ALL, "zh_CN.UTF-8");

    ClassInfo* class[5];
    for (int i = 0; i < 5; i++) {
        class[i] = c_rand_data(i + 1);
    } // 创建5个班级

    for (int i = 0; i < 5; i++) {
        c_print_data(class[i], CLASS_MEN);
    }

    switch (menu()) {
        case 1:
            wprintf(L"请输入学生姓名：");
            wchar_t name[20];
            wscanf(L"%ls", name);
            wprintf(L"根据学生姓名查询结果：\n");
            for (int i = 0; i < 5; i++) {
                print_student_info_according_to_name(class[i], CLASS_MEN, name);
            }
            break;
        case 2:
            wprintf(L"请输入学生学号：");
            int number;
            scanf("%d", &number);
            wprintf(L"根据学号查询结果：\n");
            for (int i = 0; i < 5; i++) {
                print_student_info_according_to_number(class[i], CLASS_MEN, number);
            }
        case 3:
            wprintf(L"请输入学生班级：");
            int class_number;
            scanf("%d", &class_number);
            wprintf(L"根据班级查询结果：\n");
            c_print_data(class[class_number-1], CLASS_MEN);
            break;
        case 4:
            wprintf(L"无意义，已经舍去");
            break;
        case 5:
        case 6:
            wprintf(L"查询哪门课程的最高分及相应学生信息：\n");
            wprintf(L"1.C程序\n");
            wprintf(L"2.英语\n");
            wprintf(L"3.高数\n");
            wprintf(L"4.物理\n");
            wprintf(L"5.体育\n");
            CourseScore course;
            scanf("%d", &course);

            switch (course) {
                case CPROG_SCORE:
                    wprintf(L"C程序最高分及相应学生信息：\n");
                    for (int i = 0; i < 5; i++) {
                        print_student_info_sort_max_and_min(class[i], CLASS_MEN, CPROG_SCORE);
                    }
                    break;
                case ENG_SCORE:
                    wprintf(L"英语最高分及相应学生信息：\n");
                    for (int i = 0; i < 5; i++) {
                        print_student_info_sort_max_and_min(class[i], CLASS_MEN, ENG_SCORE);
                    }
                    break;
                case MATH_SCORE:
                    wprintf(L"高数最高分及相应学生信息：\n");
                    for (int i = 0; i < 5; i++) {
                        print_student_info_sort_max_and_min(class[i], CLASS_MEN, MATH_SCORE);
                    }
                    break;
                case PHY_SCORE:
                    wprintf(L"物理最高分及相应学生信息：\n");
                    for (int i = 0; i < 5; i++) {
                        print_student_info_sort_max_and_min(class[i], CLASS_MEN, PHY_SCORE);
                    }
                    break;
                case PE_SCORE:
                    wprintf(L"体育最高分及相应学生信息：\n");
                    for (int i = 0; i < 5; i++) {
                        print_student_info_sort_max_and_min(class[i], CLASS_MEN, PE_SCORE);
                    }
                    break;
                default:
                    wprintf(L"输入错误！");
                    break;
            }
            break;

        default:
            wprintf(L"退出系统！");
            break;

    }

    for (int i = 0; i < 5; i++) {
        free(class[i]); // 释放内存
    }
    return 0;
}