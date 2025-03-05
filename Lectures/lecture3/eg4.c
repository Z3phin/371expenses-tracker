#include <stdio.h>

void pass_by_val(int *arg) {
    *arg = 7;
}

int* return_pointer() {
    int arg_2 = 42;
    return &arg_2;
    
}

int main() {
    int h2g2 = return_pointer();
    printf("The answer is %d\n", h2g2);

    // int new_val = *return_pointer(&h2g2);
    // printf("The answer is now %d\n", h2g2);
    // printf("The answer is now %d\n", new_val);

    return 0;
}