#include <iostream>
#include "intvector.hpp"

int main() {
    Intvector iv = Intvector(1);
    std::cout << iv << std::endl; 

    iv.push(1);
    std::cout << iv << std::endl; 

    iv.push(1);
    std::cout << iv << std::endl; 

    Intvector iv1 = Intvector(1);
    iv.push(2);

    iv + iv1;
    std::cout << iv << std::endl;    

}