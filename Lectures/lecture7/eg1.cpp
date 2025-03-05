#include "eg1.h"
#include <iostream>
// using namespace std; // don't do this, not good practice

A::A() : value(0) { /* empy constructor body */}

A::A(int value) : value(value) {}

A::~A() {
    this->value = 0;
}

void A::setValue(int value) {
    this->value = value;
}

void A::doSomething() const {
    std::cout << this->value << "\n";
}