/* Determine whether arguments can be added without overflow */
int uadd_ok(unsigned x, unsigned y);

int main(){
    return uadd_ok(1,1);//测试数据
}

int uadd_ok(unsigned x, unsigned y){
    //当x+y产生溢出时返回0，结果正常则返回1
    unsigned int result = x + y;
    if(result<=x|result<=y)
        return 0;
    else return 1;
}