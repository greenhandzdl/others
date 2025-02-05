//g++ hanoi.cpp -o hanoi.out && ./hanoi.out
unsigned long long int hanoi(unsigned int,char, char, char);

unsigned long long int hanoi(unsigned int n,char source, char auxiliary, char destination){
    /*(mermaid)
    unsigflowchart TD
    A[开始] --> B{盘子数量为1？}
    B -->|是| C[返回1步]
    B -->|否| D[移动n-1个盘子从source到auxiliary]
    D --> E[移动1个盘子从source到destination]
    E --> F[移动n-1个盘子从auxiliary到destination]
    F --> G[返回总步数]ned int n;
    */
    return n==1
        ? 1
        : hanoi(n - 1, source, destination, auxiliary) 
            + hanoi(1, source, auxiliary, destination)
            + hanoi(n - 1, auxiliary, source, destination);
}