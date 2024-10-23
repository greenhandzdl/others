//g++ main.cpp arr_op.cpp arr_op.h -o arr_op.out  && ./arr_op.out
#include "arr_op.h"

int main(void){
    USER_INPUT user_input = menu();
    cout.put(user_input.arr_ptr);
    free(user_input.arr_ptr);
}