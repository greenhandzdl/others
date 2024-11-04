int tdivz(signed int x,unsigned int k);
//用于除以2的指数k

int main(void){
    return tdivz(-4,1);
}

int tdivz(signed int x,unsigned int k){
    return (x < 0 ? x + k - 1 : x) >> k;
}