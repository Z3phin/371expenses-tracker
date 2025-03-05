#include <stdio.h>

int globalVar;

int anotherGlobalVar = 42;


void someFunction(void) {
    globalVar = 7;

    int localVar;
    localVar = 1; 

    int anotherLocalVar = 7;
    //HERE
}

int main(void) {
    return 0;
}


