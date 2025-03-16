// -----------------------------------------------------
// CSC371 Advanced Object-Oriented Programming (2024/25)
//
// (c) Martin Porcheron
//     Thomas Reitmaier
//     thomas.reitmaier@swansea.ac.uk
// -----------------------------------------------------

#include <iostream>
#include "Shape.h"

int main(int argc , char *argv[]) {
    Shape *x = new Rectangle (0, 1, 1, 0); // x0, y0, x1, y1
    
    std::cout << x->to_string() << std::endl;
    x->centre_at(-2.5, 2.5);
    
    std::cout << x->to_string() << std::endl;
    
    delete x;

    std::string signee1;
    std::string signee2;

    std::cout << "Signee1 Name: " << std::endl;

    std::cin >> signee1;

    std::cout << "Signee2 Name: " << std::endl;

    std::cin >> signee2;

    std::cout << "This is a contract stating that " << signee1 << " is "
              << " wholly responsible for the mortal life of "
              << signee2 << "\n after a period of fasting that should be broken "
              << "when " << signee1 << " reminds " << signee2 << " to eat food"
              << " at 6:54pm on March 16th 2025.\n\n" 
              << "Fasting, where no food or drink shall be consumed by both\n" 
              << signee1 << " and " << signee2 
              << ", shall take place from 4:54am to 6:54pm on March 16th 2025"
              << std::endl;

    


    return 0;


}
