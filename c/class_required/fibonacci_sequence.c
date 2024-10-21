//gcc fibonacci_sequence.c -o fibonacci_sequence.out && ./fibonacci_sequence.out
int fibonacci_sequence(const unsigned int);

int fibonacci_sequence(const unsigned int n){
    switch(n){
        case 1:
            return 1;
        case 2:
            return 1;
        default:
            return fibonacci_sequence(n-1) + fibonacci_sequence(n-2);
    }
}