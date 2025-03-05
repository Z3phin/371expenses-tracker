#include "eg1.h"

int main() {
    // Value at pointer is a default constructed instance of A
    A *ptr = new A;
    ptr->doSomething();
    delete ptr;

    A *ptr2 = new A();
    ptr2->doSomething();
    delete ptr2;

    // value at pointer is a instace of A with value 42

    A *ptr3 = new A(42);
    delete ptr3;

    //  pointer to 10 default constructed instances of A
    A *ptr4 = new A[10]();
    int i;
    for (i = 0; i < 10; i++) {
        ptr4[i].setValue(i);
    }
    delete [] ptr4;
}