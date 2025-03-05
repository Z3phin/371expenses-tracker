#include <stdio.h>
#include <stdlib.h>

struct MyStruct {
    int a;
    int b;
    float *ptr;
};

int main()
{
    struct MyStruct x;

    x.a = 5;
    x.b = 42;
    x.ptr = (float*) malloc(3*sizeof(float));

    printf("x.a = %d\n", x.a);
    printf("x.b = %d\n", x.b);
    printf("x.ptr = %p\n", x.ptr);

    free(x.ptr);
    x.ptr = NULL;

}
