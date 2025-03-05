#include <stdio.h>

union Data {
    int i;
    float f;
    char str[5];
    char* a;
};

int main() {
    union Data d;
    d.i = 1;
    d.f = 1;
    printf("sizeof data = %lu\n", sizeof(union Data));
}