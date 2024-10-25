//g++ main.cpp arr_op.cpp -o arr_op.out && ./arr_op.out
#include "arr_op.h"

int main(void){
    friendly_user_input_type user_input_1 = menu();
    //对申请的堆进行释放（手动
    delete_USER_INPUT(user_input_1);
    return 0;
}