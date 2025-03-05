#include "eg5.h"

lecture::A::A() {
    A::setValue(0);
}

void lecture::A::doSomething() const {
    /* ... */
}

int main() {
    lecture::A stack1 = lecture::A();
    stack1.doSomething();

    return 0;
}