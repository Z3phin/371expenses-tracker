#include <stdio.h>

int power(int m, int n);

int main() {
    int i;

    for (i = 0; i < 10; ++i)
        printf("%d %d %d\n", i, power(2,i), power(-3, i));
    return 0; 
}

int power(int m, int n) {
    if (n < 0) {
        return 0; // NOT CORRECT BUT OK FOR NOW
    } 

    if (m == 0) {
        return 0;
    }

    int result = 1; 
    for (int i = 0; i < n; i++ ) {
        result *= m; 
    }
    return result; 
}