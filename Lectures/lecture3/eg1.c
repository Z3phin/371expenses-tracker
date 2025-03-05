#include <stdio.h>

int main() {
    int var = 42;
    int *ptr_to_var = &var;
    int **ptr_to_ptr_to_var = &ptr_to_var;

    printf("The value %d is at %p\n", var, &var);
    printf("The value %d is at %p\n", *ptr_to_var, ptr_to_var);

    printf("The pointer that points to %p is at %p\n", ptr_to_var, ptr_to_ptr_to_var);
    printf("var by dereferencing %d\n", **ptr_to_ptr_to_var);
    
    
}