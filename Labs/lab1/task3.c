#include <stdlib.h>
#include <stdio.h>
#include "fibonacci.h"

const int DEFAULT_FIBONACCI_NUM = 10;

int main(int argc, char* argv[]) {
    int num;
    if (argc < 2) {
        num = DEFAULT_FIBONACCI_NUM;
    } else {
        num = atoi(argv[1]);
    }
    int result = fibonacci(num);
    printf("Fibonacci of %d = %d\n", num, result);
    return 0; 
}
