#ifndef INTVECTOR_H
#define INTVECTOR_H

#include <iostream>

class Intvector {
    private:
        int *data; 
        unsigned int pos;
        unsigned int length;

    public:
        Intvector(const unsigned int length);
        ~Intvector();


        void push(const int value);
        int pop();
        void resize(const unsigned int length);
        friend std::ostream& operator<<(std::ostream &os, const Intvector &iv);
        friend Intvector& operator+(Intvector& lhs, Intvector& rhs);
};

#endif