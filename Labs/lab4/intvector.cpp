#include "intvector.hpp"
#include <iostream>
#include <cstring>
#include <string>

Intvector::Intvector(const unsigned int length)
    : length(length), pos(0) {
        this->data = new int[length]();
}

Intvector::~Intvector() {
    delete [] this->data;
}


void Intvector::push(const int value) {
    if (this->pos >= this->length) {
        this->resize(this->length * 2);
    }    
    this->data[pos++] = value; 
}

int Intvector::pop() {
    if (this->pos <= 0) {
        std::cerr << "ERROR: Cannot pop item from vector." << std::endl;
        return -1;
    }

    return this->data[--(this->pos)];
}

void Intvector::resize(const unsigned int new_length) {
    std::cout<< "Intvector is resizing to size " << new_length << std::endl;
    int *new_data = new int[new_length]();

    memcpy(new_data, this->data, this->length * sizeof(int));

    this->length = new_length; 
    delete [] this->data;
    this->data = new_data;
}

std::ostream& operator<<(std::ostream &os, const Intvector &iv) {
    os << "[ ";
    for (int i = 0; i < iv.pos; i++) {
        os << iv.data[i] << " ";
    }
    os << "] (used capacity = " << iv.pos
       << ", spare = " << iv.length - iv.pos
       << ", total = " << iv.length << ")";

    return os;

}

Intvector& operator+(Intvector& lhs, Intvector& rhs) {
    for (int i = 0; i < rhs.pos; i++) {
        lhs.push(rhs.data[i]);
    }

    return lhs;
}
